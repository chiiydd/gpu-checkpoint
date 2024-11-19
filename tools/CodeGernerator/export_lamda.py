import re



# 正则表达式解析
pattern = r"typedef\s+\w+\s*\(CUDAAPI\s+\*\w+\)\s*\(\s*(.*?)\s*\);"
function_pattern = r"PFN_([^_]+)(_v\d+)?(_ptds|_ptsz|)?\)\("
if_pattern = r"#if defined\(__CUDA_API_VERSION_INTERNAL\)"
endif_pattern = r"#endif"


macro_definition = None  # 记录每个宏定义及其上下文
before_function = ""  # 当前处理到的函数名

file_path ="include/cudaTypedefs.h"
output_path="cuda_hook.cpp"

code_template ="""DEF_FN(CUresult,$func_full_name$,$names_types$);
"""

cuGetProcAddress_definition="""CUresult cuGetProcAddress(const char * symbol, void **pfn, int cudaVersion, cuuint64_t flags, CUdriverProcAddressQueryResult * symbolStatus) {
    CUresult result = realCuGetProcAddress(symbol, pfn, cudaVersion, flags, symbolStatus);
    printf("Intercepted cuGetProcAddress: Requesting symbol %s (flags=%lu, version=%d): %p\\n", symbol, flags, cudaVersion, *pfn);

    if (strcmp(symbol, "cuGetProcAddress") == 0) {
        *pfn = (void*)&cuGetProcAddress;  // 拦截自身
		return CUDA_SUCCESS;
    } 

	std::string funcName=std::string(symbol)+"_"+std::to_string(cudaVersion);
	if (flags==1){
		funcName+="_ptds";
	}else if (flags==2){
		funcName+="_ptzs";
	}

	if (cuDriverFunctionTable.find(funcName)!=cuDriverFunctionTable.end()){
		*pfn=cuDriverFunctionTable[funcName].funcPtr;
	}
	else{
		printf("CUDA Driver API NOT HOOK:%s\\n",symbol);
	}

    return result;
}
"""

hook_template="""\t{"$func_full_name$",CuDriverFunction(\"$func_name$\",$version$,$flags$,reinterpret_cast<void*>(&$func_full_name$)) },
"""


# 解析文件内容
def parse_file_content(file_path):
    functions = []
    with open(file_path, 'r') as file:
        file_content = file.read()
        global before_function
        global macro_definition
    for line in file_content.splitlines():
    # 处理 #if 宏定义
        if re.match(if_pattern, line):
            macro_definition={
                "content": line,
                "before_function": before_function  # 记录宏定义前的最后一个函数
            }
            print(f"Macro definition at: {before_function}")
        if match := re.search(pattern, line):
            params = match.group(1)  # 获取参数列表
            params_list = params.split(", ")
            param_types=[]
            param_names=[]
            names_types=[]
            if len(params_list)==1 and params_list[0]=="void":
                param_types.append("void")
                names_types.append("void,")
            else:
                for param in params_list:
                    param_type, param_name = param.rsplit(" ", 1)
                    star_cout=param_name.count("*")    
                    if star_cout>0:
                        param_name=param_name.lstrip("*")
                        param_type=param_type + "*"*star_cout                    
                        
                    param_types.append(param_type)
                    param_names.append(param_name)
                    names_types.append(param_type+","+param_name)
                
            if func_match := re.search(function_pattern, line):
                func_name, version_suffix, special_suffix = func_match.groups()
                if version_suffix is None:
                    version_suffix = ""
                    print("NOT FOUND version_suffix:",func_name)
                if special_suffix is None:
                    special_suffix = ""
                    print("NOT FOUND special_suffix:",func_name)
                func_full_name=func_name+version_suffix+special_suffix
                flags="0"
                if special_suffix=="_ptds":
                    flags="1"
                elif special_suffix=="_ptsz":
                    flags="2"
                
                if version_suffix == "":
                    version="0"
                else:
                    version=version_suffix[2:]
                before_function = func_full_name  
                functions.append({
                    "func_name": func_name,
                    "func_full_name": func_full_name,
                    "param_types": param_types,
                    "param_names": param_names,
                    "names_types": names_types,
                    "version_suffix": version_suffix ,
                    "special_suffix": special_suffix ,
                    "version": version,
                    "flags": flags
                })
            else:
                print(f"Function not matched: {line}")
    return functions

def generate_headers(output_path):
    headers="""#include <cstring>
#include <cuda_original.h>
#include <cstdio>
#include "cuda_hook.h"
#include <string>
#include <unordered_map>
#include "macro_common.h"

"""
    with open(output_path, 'w') as f:
        f.write(headers)
        
def generate_definitions(output_path,functions):
    with open(output_path, 'a') as f:
        global macro_definition
        in_define=False

        for func in functions:
            if in_define:
                f.write("\t")
            f.write(code_template.replace("$func_full_name$", func["func_full_name"])
                       .replace("$names_types$", ", ".join(func["names_types"]))
            )
            if func["func_full_name"]==macro_definition["before_function"]:
                f.write(macro_definition["content"]+"\n")
                in_define=True
        f.write("#endif\n")
            
def generate_hook_functions(output_path,functions):
    with open(output_path, 'a') as f:
        global macro_definition
        f.write("std::unordered_map<std::string,CuDriverFunction> cuDriverFunctionTable {\n")
        for func in functions:
            

            f.write(hook_template.replace("$func_full_name$", func["func_full_name"])
                       .replace("$version_suffix$", func["version_suffix"])
                       .replace("$flags$", func["flags"])
                       .replace("$func_name$", func["func_name"])
                       .replace("$version$", func["version"])
            )
            if func["func_full_name"]==macro_definition["before_function"]:
                
                f.write(macro_definition["content"]+"\n")
                
                
        f.write("#endif\n\n")
        f.write("};\n\n\n")
def generate_cuGetProcAddress(output_path):
    with open(output_path, 'a') as f:
        f.write(cuGetProcAddress_definition)
        
if __name__ == "__main__":
    generate_headers(output_path)
    functions=parse_file_content(file_path)
    generate_definitions(output_path,functions)
    generate_hook_functions(output_path,functions)
    generate_cuGetProcAddress(output_path)

    print("Hook functions number: {}".format(len(functions)))
    print(f"Hook functions generated and saved to {output_path}")
    
