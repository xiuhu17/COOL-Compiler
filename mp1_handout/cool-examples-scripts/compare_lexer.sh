#!/bin/bash

# 设定文件夹路径
EXAMPLES_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/cool-examples"
REFERENCE_BINARIES_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/reference-binaries"
SRC_DIR="/home/zhihaow6/Desktop/426/public/mp1_handout/src"

# 创建一个临时文件夹存放输出结果
TMP_DIR=$(mktemp -d -t lexer_diff-XXXXXXXXXX)

# 初始化一个变量来跟踪是否有差异
DIFF_FOUND=0

# Initialize counter variables for passed tests and total tests
PASSED_TESTS=0
TOTAL_TESTS=$(ls $EXAMPLES_DIR/*.cl | wc -l)

# 遍历所有 .cl 文件
for cl_file in $EXAMPLES_DIR/*.cl; do
  filename=$(basename -- "$cl_file")

  # 使用 reference-binaries 中的 lexer
  $REFERENCE_BINARIES_DIR/./lexer $cl_file > $TMP_DIR/reference_$filename.out
  
  # 使用 src 中的 lexer
  $SRC_DIR/./lexer $cl_file > $TMP_DIR/src_$filename.out

  # 对比两个输出文件
  diff $TMP_DIR/reference_$filename.out $TMP_DIR/src_$filename.out > $TMP_DIR/diff_$filename.txt
  
  if [ $? -eq 0 ]; then
    # 无差异
    rm $TMP_DIR/diff_$filename.txt  # 可选：删除没有差异的 diff 文件
    PASSED_TESTS=$((PASSED_TESTS + 1))
    echo "[$PASSED_TESTS/$TOTAL_TESTS] Pass!"
  else
    # 有差异
    DIFF_FOUND=1
    echo "Differences found for $filename. Check $TMP_DIR/diff_$filename.txt"
  fi
done

# 输出最终结果
if [ $DIFF_FOUND -eq 0 ]; then
  echo "Succeed!"
else
  echo "Check $TMP_DIR for output files and differences."
fi
