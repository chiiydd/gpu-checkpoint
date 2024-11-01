import re
import os 
from datetime import datetime

input_file="/home/chiiydd/repository/gpu-checkpoint/include/common/cuda/cuda_original.h"
output_file = "cuda_subset.h"
# 定义文件头部模板
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
#ifndef __cuda_cuda_subset_h__
#define __cuda_cuda_subset_h__
#include <stdlib.h>
"""
    return header




struct_pattern = re.compile(
        r"(#ifdef\s\w+\ntypedef.*?;.*?#endif)|"                # 匹配带有 #ifdef 条件编译的 typedef 块
        r"(#ifndef\s\w+\n#define\s\w+\ntypedef.*?;.*?#endif)|"      # 匹配带有 #ifndef 条件编译的 typedef 块
        r"(^typedef\s+((?!\{).)*?\s+\w+;)|"  # 匹配普通的typedef语句
        r"(^typedef\s+struct\s+\w+\s*\{((?!typedef).)*\}\s\w+;)", # 匹配struct类型的typedef
        re.DOTALL | re.MULTILINE
    )



with open(os.path.join(input_file), "r") as f:
    header_content=f.read()
    

with open(output_file, "w") as f:
    f.write(generate_watermark("chiiydd", "Generated subset of cuda.h"))
    f.write(generste_headers())
    matches = struct_pattern.finditer(header_content)
    PRINT_FALG=False
    for match in matches:
        if match.group(1):
            f.write(match.group(1)+"\n")
        elif match.group(2):
            f.write(match.group(2)+"\n")
        elif match.group(3):
            f.write(match.group(3)+"\n")
        elif match.group(5):
            f.write(match.group(5)+"\n")
            print("FIND STRUCT:",match.group(5))
    


print(f"Hook functions generated and saved to {output_file}")


