
#!/usr/bin/python3
# coding=utf-8

from __future__ import print_function
from __future__ import division
from __future__ import absolute_import
from __future__ import with_statement

import os
import optparse
import subprocess
from CppHeaderParser import CppHeader

def extract_not_found_content(filename):
    result = []
    if not os.path.exists(filename):
        print("remove v2's file not found: {}".format(filename))
        exit(1)
    with open(filename, 'r') as file:
        for line in file:
            if "NOT FOUND" in line:
                # 提取 "NOT FOUND" 后面的内容并去除前后的空白
                content = line.split("NOT FOUND", 1)[1].strip()
                result.append(content)
    print("find v2 func num: {}".format(len(result)))
    return result

def remove_lines_before_funcdef(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    # 找到包含目标内容的行索引
    target_line = "CUresult cuGetErrorString(CUresult error, const char **pStr);"
    start_index = None
    for i, line in enumerate(lines):
        if target_line in line:
            start_index = i
            break

    # 如果找到了目标行，保留该行及其后的所有行
    if start_index is not None:
        lines = lines[start_index:]

    # 将结果写回文件
    with open(filename, 'w') as file:
        file.writelines(lines)

def pre_process_header(header,output):
    result=subprocess.run(["gcc", "-E", header, "-o", output+"/pre_process_header.h"])
    if result.returncode != 0:
        print("pre process header failed")
        exit(1)
    return output+"/pre_process_header.h"
    
class CodeGenerate():
    def __init__(self, include_,type_, file_, output_,func_v2_list_):
        self.type = type_
        self.file = file_
        self.output = output_

        self.func_v2_list=func_v2_list_
        self.func_list = []
        self.hook_file = self.output + "/" + self.type + "_hook.cpp"
        self.hook_list = []
        self.hook_include = """
// auto generate $hook_num$ apis
"""
        if include_: 
            self.hook_include += """
#include "$type$_subset.h"
#include "hook.h"
#include "macro_common.h"
#include "trace_profile.h"
"""


        self.hook_template = """\tELSE_IF($func_name$,$param_type$)
"""
        self.hook_template_v2="""\t#undef $func_name$
        ELSE_IF_V2($func_name$,$param_type$)
"""

#         self.hook_template ="""DEF_FN(CUresult,$func_name$ $names_types$);
# """

    def parsę_header(self):
        self.header = CppHeader(self.file)
        print(
            "{} total func num: {}".format(
                self.type, len(
                    self.header.functions)))

    def generate_func(self):
        for func in self.header.functions:
            func_name = func["name"]
            if func_name in self.func_list:
                continue
            # if func_name.endswith("v2") or func_name.endswith("v3"):
            #     continue
            else:
                self.func_list.append(func_name)

            ret = func["rtnType"].replace(
                "CUDAAPI", "").replace(
                "__CUDA_DEPRECATED", "").replace(
                "DECLDIR", "").replace(
                "CUDARTAPI_CDECL", "").replace(
                "CUDARTAPI", "").replace(
                "__host__", "").replace(
                "__cudart_builtin__", "").replace(
                "CUDNNWINAPI", "").replace(
                "CUBLASWINAPI", "").replace(
                "CUBLASAPI", "").replace(
                "CUFFTAPI", "").replace(
                "NVTX_DECLSPEC", "").replace(
                "NVTX_API", "").replace(
                "CURANDAPI", "").replace(
                "CUSPARSEAPI", "").replace(
                "CUSOLVERAPI", "").replace(
                "NVJPEGAPI", "").strip(' ')

            func_param = ""
            param_type = ""
            param_name = ""
            names_types =""
            for param in func["parameters"]:
                if len(func_param) > 0:
                    func_param += ", "
                    param_type += ", "
                    param_name += ", "
                if param["array"] == 1:
                    param["type"] += "*"
                func_param += (param["type"] + " " + param["name"])
                param_type += param["type"]
                param_name += param["name"]
                names_types +="," +param["type"] + "," + param["name"] 

            if func_name.removesuffix("_v2") in self.func_v2_list:
                print(func_name)
                func_name=func_name.removesuffix("_v2")
                hook_func = self.hook_template_v2
            else:
                hook_func = self.hook_template
            self.hook_list.append(
                hook_func.replace(
                    "$ret$",
                    ret).replace(
                    "$func_name$",
                    func_name).replace(
                    "$func_param$",
                    func_param).replace(
                    "$param_type$",
                    param_type).replace(
                        "$param_name$",
                        param_name).replace(
                            "$type$",
                    self.type.upper()).replace("$names_types$", names_types))
        print("{} valid func num: {}".format(self.type, len(self.func_list)))

    def save_output(self):
        if not os.path.exists(self.output):
            os.makedirs(self.output)

        with open(self.hook_file, 'w') as fh:
            hook_include = self.hook_include.replace("$hook_num$", str(
                len(self.hook_list))).replace("$type$", self.type)
            fh.write(hook_include)
            for hook in self.hook_list:
                fh.write(hook)


def main():
    usage = "python3 export_cuda_h.py --type cuda --file include/cuda.h -o/--output output"
    parser = optparse.OptionParser(usage)
    parser.add_option(
        "--include",
        "-i",
        dest="include",
        action="store_true",
        help="generate include file lines",
        default=False,
        
    )
    parser.add_option(
        '-t',
        '--type',
        dest='type',
        type='string',
        help='header type',
        default='cuda')
    parser.add_option(
        '-f',
        '--file',
        dest='file',
        type='string',
        help='header file',
        default='include/cuda.h')
    parser.add_option(
        '-o',
        '--output',
        dest='output',
        type='string',
        help='output path',
        default='output')
    parser.add_option(
        "-r",
        "--remove-v2",
        dest="file_v2",
        type="string",
        help="remove v2 function's suffix \"_v2\" from the file",
        default=""
    )

    options, args = parser.parse_args()
    type_ = options.type
    file_ = options.file
    output_ = options.output
    include_ = options.include
    
    file_=pre_process_header(file_,output_)
    remove_lines_before_funcdef(file_)
    func_v2_list_=extract_not_found_content(options.file_v2)
    

    code_gen = CodeGenerate(include_,type_, file_, output_,func_v2_list_)
    code_gen.parsę_header()
    code_gen.generate_func()
    code_gen.save_output()


if __name__ == '__main__':
    main()
