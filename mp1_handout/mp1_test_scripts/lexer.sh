#!/bin/bash

# 定义路径
LEXER1="/home/zhihaow6/Desktop/426/public/mp1_handout/src/lexer"
LEXER2="/home/zhihaow6/Desktop/426/public/mp1_handout/reference-binaries/lexer"
TEST_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/mp1_test_cases/lex_tests"

# 计算测试文件数量
NUM_TESTS=$(ls -1 "$TEST_DIR" | wc -l)
PASSED_TESTS=0

# 开始循环，针对每一个测试文件执行
for i in $(ls "$TEST_DIR"); do
    # 执行 lexer 并将输出保存到临时文件
    $LEXER1 < "$TEST_DIR/$i" > output1.txt
    $LEXER2 < "$TEST_DIR/$i" > output2.txt

    # 比较两个输出
    diff -q output1.txt output2.txt > /dev/null
    if [ $? -eq 0 ]; then
        echo "pass[$((PASSED_TESTS+1))/$NUM_TESTS]"
        PASSED_TESTS=$((PASSED_TESTS+1))
    else
        echo "fail[$((PASSED_TESTS+1))/$NUM_TESTS]"
    fi
done

# 删除临时文件
rm output1.txt output2.txt

# 输出总体结果
if [ $PASSED_TESTS -eq $NUM_TESTS ]; then
    echo "succeed"
else
    echo "fail"
fi