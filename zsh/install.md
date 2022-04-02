
### 一安装zsh
1.安装zsh包
yum -y install zsh
2.切换默认shell为zsh
chsh -s /bin/zsh
3.重启服务器让修改的配置生效
这个没什么好多说的，我习惯在web端控制台直接重启。
4.安装on my zsh


* 先用 git 下载 oh-my-zsh 项目到本地：
  git clone https://gitee.com/mirrors/oh-my-zsh.git ~/.oh-my-zsh
* 将 zshrc 替换掉：cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc
* 重启终端即可看到安装成功

### 二、安装oh_my_sh及插件

git clone https://gitee.com/mirrors/oh-my-zsh.git ~/.oh-my-zsh

sudo yum -y install autojump && sudo yum -y install autojump-zsh 
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions 
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting




