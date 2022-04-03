wget https://golang.google.cn/dl/go1.18.linux-amd64.tar.gz

tar -zxf go1.18.linux-amd64.tar.gz -C /usr/local
临时命令:
export PATH=$PATH:/usr/local/go/bin
长久添加到zshrc:
export GO111MODULE=on
export GOROOT=/usr/local/go
export GOPATH=/root/workspace
export PATH=$PATH:$GOROOT/bin:$GOPATH/bin

