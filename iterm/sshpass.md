1.   安装sshpass
wget http://sourceforge.net/projects/sshpass/files/sshpass/1.05/sshpass-1.05.tar.gz 

tar xvzf sshpass-1.05.tar.gz
./configure 
make 
sudo make install

2. 配置ssh
先用ssh命令测试下：ssh root@159.75.38.33 -p22

设置密码文件路径及密码： /Users/cooperswang/code/env/centos_159.75.38.33   2019Youth
设置命令：/usr/local/bin/sshpass -f /Users/cooperswang/code/env/centos_159.75.38.33 ssh -p22 root@159.75.38.33
该命令功能：
/usr/local/bin/sshpass是sshpass执行文件的路径，默认情况安装现在这个位置上
-f 是告诉sshpass加载文件
 /Users/ChanandlerBong/sshpass/Centos_172.16.135.128就是要加载的的密码文件

参考文章：
https://www.jianshu.com/p/ae7bf4086b0d
https://www.cnblogs.com/liqiangchn/p/14280203.html expect脚本可以使用跳板机，待探索
