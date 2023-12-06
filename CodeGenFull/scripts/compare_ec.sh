#!/bin/bash

# 设定路径
SCRIPT_DIR="../scripts"
TESTCASE_DIR="../mp3_ec_testcases"
RESULT_DIR="../results"

# 确保 results 文件夹存在
mkdir -p $RESULT_DIR

# 获取所有的 .cl 文件数量
n=$(find $TESTCASE_DIR -name "*.cl" | wc -l)

# 计数器
total_tests=0
passed_tests=0

# 失败的测试文件名称列表
failed_tests=()

# 切换到 mp2_testcases 目录
cd $TESTCASE_DIR

# 遍历所有的 .cl 文件
for file in *.cl; do
    # 获取文件名（无扩展名）
    base="${file%.*}"

    # 执行生成输出文件的命令，忽略其输出
    make $base.out > /dev/null 2>&1
    make $base.outref > /dev/null 2>&1

    # 增加总测试数
    total_tests=$((total_tests+1))

    # 对比两个文件的内容
    if diff -q "$base.out" "$base.outref" > /dev/null; then
        # 如果文件相同
        passed_tests=$((passed_tests+1))
        echo "pass [$base] [$total_tests/$n]" >> $RESULT_DIR/result.txt
    else
        # 记录失败的文件名称
        failed_tests+=("$base")
        echo "fail [$base] [$total_tests/$n]" >> $RESULT_DIR/result.txt
    fi
done

# 输出总结
echo "Total Pass EC [$passed_tests/$n]" >> $RESULT_DIR/result.txt
echo "Total Fail EC [$((${#failed_tests[@]}))/$n]" >> $RESULT_DIR/result.txt

# 如果有失败的测试，列出所有失败的文件名称
if [ ${#failed_tests[@]} -ne 0 ]; then
    echo "Failed Testcases:" >> $RESULT_DIR/result.txt
    for fail in "${failed_tests[@]}"; do
        echo "$fail" >> $RESULT_DIR/result.txt
    done
fi

# 执行 make clean 并忽略其输出
make clean > /dev/null 2>&1

# 切换回原来的目录
cd -
