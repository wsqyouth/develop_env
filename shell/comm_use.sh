#!/usr/bin/env bash

# 将一列数据去重后替换为一行,中间以','分隔
 cat hh.tx | sort | uniq | tr '\n' ',' | sed 's/,$/\n/'
