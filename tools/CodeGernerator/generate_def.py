import re
import os 
input_file="include/generated_cuda_meta.h"
output_file = "output/generated_hooks.cpp"


# code_template= """
# HOOK_C_API HOOK_DECL_EXPORT CUresult {$func_name}({$args}) {{
#     HOOK_TRACE_PROFILE("{$func_name}");
#     using func_ptr = CUresult (*)({$arg_types});
#     static auto func_entry = reinterpret_cast<func_ptr>(HOOK_CUDA_SYMBOL("{$func_name}"));
#     HOOK_CHECK(func_entry);
#     CUresult res = func_entry({$arg_names});
#     RESULT_CHECK(res);
#     return res;
# }}
# """

code_template="""DEF_FN(CUresult,{$func_name},{$names_types});
"""

# code_template="""\tELSE_IF({$func_name},{$arg_types})
# """

# 正则表达式来匹配结构体定义
struct_pattern = re.compile(r"typedef struct (\w+)_params_st {\s*([^}]*)} (\w+);")

function_map=[]
# 生成hook函数代码
def generate_hook_function(struct_name, fields):
    func_name = struct_name.replace("_params", "")
    field_list = [field.strip().rstrip(";").split() for field in fields.splitlines() if field.strip()]
    
    for field in field_list:
        start_count=field[-1].count("*")
        if start_count>0:
            field[-1]=field[-1].lstrip("*")
            field[-2]=field[-2] + "*"*start_count
    # 提取字段名称和类型
    args = ", ".join([" ".join(f[:-1]) + " " + f[-1] for f in field_list])
    arg_names = ", ".join([f[-1] for f in field_list])
    arg_types = ", ".join([" ".join(f[:-1]) for f in field_list])

    names_types=",".join([" ".join(f[:-1])+","+f[-1] for f in field_list])
    # 生成hook代码
    hook_code= code_template.replace(
            "{$func_name}", func_name).replace(
            "{$args}", args).replace(
                "{$arg_names}", arg_names).replace(
                    "{$arg_types}", arg_types).replace("{$names_types}",names_types)
    return hook_code

# 解析并生成hook函数

with open(os.path.join(input_file), "r") as f:
    header_content=f.read()


with open(output_file, "w") as f:
    matches = struct_pattern.findall(header_content)
    for struct_name, fields, _ in matches:
        if struct_name in function_map:
            continue
        if any(v in struct_name for v in ["v1", "v2", "v3"]):
            continue

        function_map.append(struct_name)
        hook_code = generate_hook_function(struct_name, fields)
        
        f.write(hook_code)

print(f"Hook functions generated and saved to {output_file}")
