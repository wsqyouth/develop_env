#!/usr/bin/env bash

HOSTNAME="127.0.0.1" #数据库信息
PORT="3306"
USERNAME="coopers"
PASSWORD="2019Youth"
DBNAME="sql_test" #数据库名称
TABLENAME="t_target_group_0" #数据库中表的名称
#select_sql="select uid,aid from ${TABLENAME} where  uid = 21678980 and create_time = 0 and op_time = 0 and  mp_conf   like '%\\\\%'"
select_sql="select uid,aid from ${TABLENAME} where  uid = 21678980 and create_time = 0 and op_time = 0 and  mp_conf !='' "
mysql -h${HOSTNAME} -P${PORT} -u${USERNAME} -p${PASSWORD} ${DBNAME} -e "${select_sql}"
