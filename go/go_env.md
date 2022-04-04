## 目标
  在一台新环境搭建vim-go环境，主要参考geek孔令飞资料
  总结：
1. Linux 服务器申请和配置（主要是创建going账号）
2. 手动安装Git、Golang
3. 安装 protoc 和 protoc-gen-go
4. 安装 nvim 和 spaceVIM


### 一、root添加普通用户
第一步  
# useradd coopers # 创建 going 用户，通过 going 用户登录开发机进行开发
# passwd coopers # 设置密码
Changing password for user going.
New password:
Retype new password:
passwd: all authentication tokens updated successfully.

第二步，添加 sudoers
# sed -i '/^root.*ALL=(ALL).*ALL/a\coopers\tALL=(ALL) \tALL' /etc/sudoers
第三步，用新的用户名（coopers）和密码登录 Linux 服务器。这一步也可以验证普通用户是否创建成功。
通过ssh登录
/usr/local/bin/sshpass -f /Users/cooperswang/code/env/centos_159.75.38.3 ssh -p22 coopers@159.75.38.3


### 二、设置zsh相关
第一步：安装并chsh zsh
第二步: 安装oh-my-zsh及插件
sudo yum -y install autojump && sudo yum -y install autojump-zsh
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions


vim ~/.zshrc
plugins=(
        git
        history-substring-search
        autojump
        colored-man-pages
        zsh-syntax-highlighting
        zsh-autosuggestions
)
source  ~/.zshrc


### 三、设置zshrc

# User specific aliases and functions

alias rm='rm -i'
alias cp='cp -i'
alias mv='mv -i'

# User specific environment
# Basic envs
export LANG="en_US.UTF-8" # 设置系统语言为 en_US.UTF-8，避免终端出现中文乱码
export PS1='[\u@dev \W]\' # 默认的 PS1 设置会展示全部的路径，为了防止过长，这里只展示："用户名@dev 最后的目录名"
export WORKSPACE="$HOME/workspace" # 设置工作目录
export PATH=$HOME/bin:$PATH # 将 $HOME/bin 目录加入到 PATH 变量中

# Default entry folder
cd $WORKSPACE # 登录系统，默认进入 workspace 目录

# Go envs
export GOVERSION=go1.18  # Go 版本设置
export GO_INSTALL_DIR=$HOME/go # Go 安装目录
export GOROOT=$GO_INSTALL_DIR/$GOVERSION # GOROOT 设置
export GOPATH=$WORKSPACE/golang # GOPATH 设置
export PATH=$GOROOT/bin:$GOPATH/bin:$PATH # 将 Go 语言自带的和通过 go install 安装的二进制文件加入到 PATH 路径中
export GO111MODULE="on" # 开启 Go moudles 特性
export GOPROXY=https://goproxy.cn,direct # 安装 Go 模块时，代理服务器设置
export GOPRIVATE=
export GOSUMDB=off # 关闭校验 Go 依赖包的哈希值


# Configure for nvim
export EDITOR=nvim # 默认的编辑器（git 会用到）
alias vi="nvim"

### 四、设置linux环境
第一步，安装依赖。

$ sudo yum -y install make autoconf automake cmake perl-CPAN libcurl-devel libtool gcc gcc-c++ glibc-headers zlib-devel git-lfs telnet ctags lrzsz jq expat-devel openssl-devel

第二步，安装 Git。

$ cd /tmp
$ wget https://mirrors.edge.kernel.org/pub/software/scm/git/git-2.30.2.tar.gz
$ tar -xvzf git-2.30.2.tar.gz
$ cd git-2.30.2/
$ ./configure
$ make
$ sudo make install
$ git --version          # 输出 git 版本号，说明安装成功
git version 2.30.2

把 Git 的二进制目录添加到 PATH 路径中，见上文配置：
tee -a $HOME/.bashrc <<'EOF'# Configure for gitexport PATH=/usr/local/libexec/git-core:$PATHEOF

第三步，配置 Git。

$ git config --global user.name "Lingfei Kong"    # 用户名改成自己的
$ git config --global user.email "colin404@foxmail.com"    # 邮箱改成自己的
$ git config --global credential.helper store    # 设置 Git，保存用户名和密码
$ git config --global core.longpaths true # 解决 Git 中 'Filename too long' 的错误
git config --global core.quotepath off # gst字符乱码
git config --global url."https://github.com.cnpmjs.org/".insteadOf "https://github.com/" #换源
$ git lfs install --skip-repo #大文件限制

### 五、go环境
Go 编译环境安装和配置
wget https://golang.google.cn/dl/go1.18.linux-amd64.tar.gz /tmp

mkdir -p $HOME/go
tar -zxvf go1.18.linux-amd64.tar.gz -C $HOME/go
mv $HOME/go/go $HOME/go/go1.18

zshrc配置：
tee -a $HOME/.zshrc <<'EOF'
# Go envs
export GOVERSION=go1.18  # Go 版本设置
export GO_INSTALL_DIR=$HOME/go # Go 安装目录
export GOROOT=$GO_INSTALL_DIR/$GOVERSION # GOROOT 设置
export GOPATH=$WORKSPACE/golang # GOPATH 设置
export PATH=$GOROOT/bin:$GOPATH/bin:$PATH # 将 Go 语言自带的和通过 go install 安装的二进制文件加入到 PATH 路径中
export GO111MODULE="on" # 开启 Go moudles 特性
export GOPROXY=https://goproxy.cn,direct # 安装 Go 模块时，代理服务器设置
export GOPRIVATE=
export GOSUMDB=off # 关闭校验 Go 依赖包的哈希值
EOF


ProtoBuf 编译环境安装

# 第一步：安装 protobuf
cd /tmp/
git clone git@github.com:protocolbuffers/protobuf.git
cd protobuf
./autogen.sh
./configure
make
sudo make install
protoc --version # 查看 protoc 版本，成功输出版本号，说明安装成功
libprotoc 3.15.6

# 第二步：安装 protoc-gen-go
go install github.com/golang/protobuf/protoc-gen-go@latest

Go 开发 IDE 安装和配置
第一步，安装 NeoVim

$ sudo pip3 install pynvim
$ sudo yum -y install neovim

第二步，配置 $HOME/.zshrc。

tee -a $HOME/.zshrc <<'EOF'
# Configure for nvim
export EDITOR=nvim # 默认的编辑器（git 会用到）
alias vi="nvim"
EOF

第三步，检查 nvim 是否安装成功。
vi --version

第四步，离线安装 SpaceVim

$ cd /tmp
$ wget https://marmotedu-1254073058.cos.ap-beijing.myqcloud.com/tools/marmotVim.tar.gz
$ tar -xvzf marmotVim.tar.gz
$ cd marmotVim
$ ./marmotVimCtl install

SpaceVim 配置文件为：$HOME/.SpaceVim.d/init.toml 和$HOME/.SpaceVim.d/autoload/custom_init.vim，你可自行配置（配置文件中有配置说明）：
init.toml：SpaceVim 的配置文件
custom_init.vim：兼容 vimrc，用户自定义的配置文件

常用快捷键：
F2 显示变量、结构体列表
gd  ctrl ]  enter 跳转函数定义
ctrl I 跳转到堆栈上一位置
ctrl O 回上一次位置
shift K 查找doc文档
shift L 生成if err定义代码
shift M 显示声明信息
ctrl N 自动补全下一个选项
crtl P 自动补全上一个选项

第五步，Go 工具安装。

SpaceVim 会用到一些 Go 工具，比如在函数跳转时会用到 guru、godef 工具，在格式化时会用到 goimports，所以我们也需要安装这些工具。
安装方法有 2 种：Vim 底线命令安装：vi test.go，然后执行：:GoInstallBinaries 安装。拷贝工具：直接将整理好的工具文件拷贝到$GOPATH/bin 目录下

$ cd /tmp
$ wget https://marmotedu-1254073058.cos.ap-beijing.myqcloud.com/tools/gotools-for-spacevim.tgz
$ mkdir -p $GOPATH/bin
$ tar -xvzf gotools-for-spacevim.tgz -C $GOPATH/bin
