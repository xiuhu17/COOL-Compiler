#!/bin/bash

# 设定路径
SCRIPT_DIR="../scripts"
TESTCASE_DIR="../mp3_testcases"
RESULT_DIR="../results"

# 确保 results 文件夹存在
mkdir -p $RESULT_DIR

# 获取所有的 .cl 文件数量
n=$(find $TESTCASE_DIR -name "*.cl" | wc -l)

# 计数器
total_tests=0
passed_tests=0

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
    diff -q "$base.out" "$base.outref" > /dev/null
    if [ $? -eq 0 ]; then
        # 如果文件相同
        passed_tests=$((passed_tests+1))
        echo "pass [$total_tests/$n]" >> $RESULT_DIR/result.txt
    else
        echo "fail [$total_tests/$n]" >> $RESULT_DIR/result.txt
    fi
done

# 输出总结
echo "Total Pass [$passed_tests/$n]" >> $RESULT_DIR/result.txt

# 执行 make clean 并忽略其输出
make clean > /dev/null 2>&1

# 切换回原来的目录
cd -