#!/usr/bin/env bash

#检查特定目录代码行数
find .  -name "*"  | xargs wc -l | tail -n 1 | awk '{print $1}'
