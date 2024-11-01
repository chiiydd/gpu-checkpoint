import re
import os 
from datetime import datetime
input_file="include/generated_cuda_meta.h"
output_file = "generated_hooks.cpp"


def generate_watermark(author, description):
    date_str = datetime.now().strftime("%Y-%m-%d")
    header = f"""/*
 * Author: {author}
 * Date: {date_str}
 * Description: {description}
 */

"""
    return header


def generste_headers():
    header= """
#ifndef __CUDA_HOOK_H__
#define __CUDA_HOOK_H__
#include<cuda_subset.h>
#include <iostream>
#include <variant>
#include <functional>
#include <string>

using LambdaVariant = std::variant<
"""
    return header

def generate_endings():
    endings="""
    >;
    extern std::unordered_map<std::string, LambdaVariant> lambdaTable;
#endif
    """
    return endings


code_template= """\tstd::function<CUresult (*) ({$arg_types})>,
"""




# 正则表达式来匹配结构体定义
struct_pattern = re.compile(r"typedef struct (\w+)_params_st {\s*([^}]*)} (\w+);")

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

    # 生成hook代码
    hook_code= code_template.replace(
            "{$func_name}", func_name).replace(
            "{$args}", args).replace(
                "{$arg_names}", arg_names).replace(
                    "{$arg_types}", arg_types)
    return hook_code

# 解析并生成hook函数

with open(os.path.join(input_file), "r") as f:
    header_content=f.read()


with open(output_file, "w") as f:
    f.write(generate_watermark("chiiydd","auto generate cuda_hook.h"))
    f.write(generste_headers())
    matches = struct_pattern.findall(header_content)
    for struct_name, fields, _ in matches:
        hook_code = generate_hook_function(struct_name, fields)
        f.write(hook_code)
    
    f.write(generate_endings())

print(f"Hook functions generated and saved to {output_file}")
