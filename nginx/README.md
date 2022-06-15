
目标：
1. 安装nginx转发个人网站
参考：https://www.cnblogs.com/huny/p/13702929.html
安装：
yum install -y gcc-c++pcre pcre-develzlib zlib-developenssl openssl-devel
wget http://nginx.org/download/nginx-1.18.0.tar.gz
tar zxvf nginx-1.18.0.tar.gz
cd nginx-1.18.0
./configure --prefix=/usr/local/nginx
make&&make install

启动：
cd /usr/local/nginx/sbin
./nginx

查看启动状态：
通过端口查询： lsof -i:80 #nginx默认是80端口
通过进程查询： ps -ef | grep nginx
访问网页查询： curl 127.0.0.1

常用命令：
nginx -s stop ：快速关闭Nginx，可能不保存相关信息，并迅速终止web服务。
⚫ nginx -s quit ：平稳关闭Nginx，保存相关信息，有安排的结束web服务。
⚫ nginx -s reload ：因改变了Nginx相关配置，需要重新加载配置而重载。


博客重启:
pidof goblog 查看进程id
kill -9 进程id
nohup ./goblog > wsq.log
---
这里要特别注意一下，安全组和防火墙一定要开发80端口，不让的话会被拦截。

### 让nginx进行方向代理
  我们找到nginx的配置文件，它的位置再我们安装好的nginx中conf目录下，其中nginx.conf就是nginx的配置文件。
  我们编辑这个配置文件在这里设置反向代理，在该位置添加(proxy_pass http://www.baidu.com;)，用百度来测试。
  我们还要重新启动一下nginx，我们来到启动nginx的目录下（/usr/local/nginx/sbin 目录下
  重新启动的命令是（如上图command）./nginx -s reload
   没有报错就代表成功了，这个时候我们访问一下解析后的域名或者是自己的公网IP，就可以直接跳转到百度的首页了。如果是想跳转到自己的某个端口的换就把百度换成自己的就行了，

1：把www.baidu.com 改成自己的域名加端口

proxy_pass http://www.xxx.xxx:8080;

2：把www.baidu.com 改成自己的域名加端口

proxy_pass http://xxx.xxx.xxx.xxx:8080;

以上二者都可以达到通过自己的域名或者公网IP 直接访问自己的端口了。
原文链接：https://blog.csdn.net/weixin_56775476/article/details/118492498
