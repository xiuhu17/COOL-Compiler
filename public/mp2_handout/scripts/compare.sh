#!/bin/bash

# 设定路径
SCRIPT_DIR="../scripts"
TESTCASE_DIR="../mp2_testcases"

# 计数器
total_tests=0
passed_tests=0

# 遍历所有的 .cl 文件
for file in $TESTCASE_DIR/*.cl; do
    # 获取文件名（无扩展名）
    filename=$(basename -- "$file")
    base="${filename%.*}"

    # 执行生成输出文件的命令
    make $base.out
    make $base.outref

    # 增加总测试数
    total_tests=$((total_tests+1))

    # 对比两个文件的内容
    diff -q "$base.out" "$base.outref" > /dev/null
    if [ $? -eq 0 ]; then
        # 如果文件相同
        passed_tests=$((passed_tests+1))
        echo "pass[$passed_tests/$total_tests]"
    fi
done

# 输出总结
echo "Total Pass: [$passed_tests / $total_tests]"
