#!/usr/bin/env bash
# 仅仅能运行在mac机器

#step1: check input para
    if [ $# != 3 ] ; then
        echo -e "usage:"
        echo "./dpsync_retry.sh "2022-10-18 21:20" "2022-10-18 22:00" 10"
        exit
    fi
begin_time=$1
end_time=$2
step=$3*60 #分钟

begin_time_stamp=$(date -j -f "%Y-%m-%d %H:%M" "$begin_time" +%s)
end_time_stamp=$(date -j -f "%Y-%m-%d %H:%M" "$end_time" +%s)
prefixStr="curl -i http://127.0.0.1:8007/trpc.dp.dpsync.dpsync/MonitorTool  -H 'Content-Type: application/json' -d '{ \"operator\":\"MonitorRetryByCreateTime\","
#echo $begin_time_stamp
#echo $end_time_stamp
for ((index=$begin_time_stamp;index<$end_time_stamp; index+=$step))
do
    index_end=$(($index+$step))
    time_start_stamp=$(date -r $index +"%Y-%m-%d %H:%M")
    time_end_stamp=$(date -r $index_end +"%Y-%m-%d %H:%M")
    #echo $index_end
    #echo "$prefixStr $time_start_stamp $time_end_stamp"
    echo "$prefixStr  \"start_time\":\"$time_start_stamp\" , \"end_time\":\"$time_end_stamp\"  ,\"timeout_minute\": $3}  "
done
