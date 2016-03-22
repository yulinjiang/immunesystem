#!/bin/bash

# Autor: yulinjiang
# date: 2015/10/29
# function: run expriment and culculate best mean std

#如果文件不存在
if [ -f temp.txt ]
then
		rm temp.txt 
fi
#创建一个文件
touch temp.txt

#执行实验过程
for i in {1..50}
do
		sh restart.sh >> temp.txt
done

sleep 1

#计算分析结果
#最好的
#cat temp.txt | awk 'BEGIN{print "Best"; min=999}{if ($1<min) min=$1 fi}END{print min}'
#均值
#cat temp.txt | awk 'BEGIN{print "Mean"}{sum+=$1}END{print sum/NR}'
#方差

