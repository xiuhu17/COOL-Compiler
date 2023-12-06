#!/bin/bash

# 定义路径
SRC_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/src"
REF_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/reference-binaries"
TEST_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/mp1_test_cases/parser_tests"

# 计算测试文件数量
NUM_TESTS=$(ls -1 "$TEST_DIR" | wc -l)
PASSED_TESTS=0
FAILED_TESTS=0  # 用于统计失败测试的数量

# 开始循环，针对每一个测试文件执行
for i in $(ls "$TEST_DIR"); do
    # 在src目录中执行 lexer 和 parser 的组合并将输出保存到临时文件
    cd "$SRC_DIR"
    ./lexer "$TEST_DIR/$i" | ./parser > /tmp/output1.txt 2>&1

    # 在reference-binaries目录中执行 lexer 和 parser 的组合并将输出保存到临时文件
    cd "$REF_DIR"
    /home/zhihaow6/Desktop/426/public/mp1_handout/reference-binaries/lexer "$TEST_DIR/$i" | ./parser > /tmp/output2.txt 2>&1

    # 比较两个输出
    if diff -q /tmp/output1.txt /tmp/output2.txt > /dev/null; then
        echo "pass $i[$((++PASSED_TESTS))/$NUM_TESTS]"
    else
        echo "fail $i[$((++PASSED_TESTS))/$NUM_TESTS]"
        FAILED_TESTS=$((FAILED_TESTS + 1))  # 如果测试失败，增加失败测试的数量
    fi
done

# 删除临时文件
rm /tmp/output1.txt /tmp/output2.txt

# 输出总体结果和失败的测试数量
if [ $FAILED_TESTS -eq 0 ]; then
    echo "succeed"
else
    echo "fail"
    echo "Total failed tests: $FAILED_TESTS"
fi
