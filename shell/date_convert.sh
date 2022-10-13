#/bin/sh
help="?"
if [ $# != 1 ] ; then
  echo "参数为空，输入的时间格式为：2022-01-16 15:26:11"
  exit 0
elif [[ $1 = "?" ]]; then
  echo "输入的时间格式为：2022-01-16 15:26:11"
  exit 0
fi
# 日期转换时间戳转换
echo "北京时间："$1
time_str=$(date -j -f "%Y-%m-%d %H:%M:%S" "$1" +%s)
echo "时间戳：" $time_str

# 时间戳转换为日期
echo "北京时间:"$(date -r $time_str)
