参考:
https://journey-c.github.io/how-to-use-vim-as-golang-and-cxx-development-ide/
CentOS 安装vim8 + python3
https://blog.csdn.net/lxyoucan/article/details/114274117

二、软件安装:
1. [你机器上python3的路径] whereis phthon3
2. cd vim
./configure --with-features=huge \
        --enable-multibyte \
        --enable-python3interp=yes \
        --with-python3-config-dir=/usr/bin/python3 \
        --enable-gui=gtk2 \
        --enable-cscope \
        --prefix=/usr/local/vim
make
sudo make install
3. 安装若报错:
CentOS 编译vim no terminal library found
yum install ncurses-devel.x86_64

4. 使用绝对路径不生效，使用软连接方法
1)确定当前vim位置
which vim
/usr/bin/vim
2) 将其删除，并软连接至vim8
  rm -rf /usr/bin/vim
  ln -s  /usr/local/vim/bin/vim /usr/bin/vim
第一个参数是被链接的真实位置，第二个是符号链接

三、插件安装
1) 安装插件管理软件
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim

2)安装插件
