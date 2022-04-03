修改 tmp 目录所属用户为 root，用户组为 root
chown -R root:root /tmp

2、修改 tmp 目录为可写权限
chmod -R 777 /tmp



fatal: remote error: The unauthenticated git protocol on port 9418 is no longer support问题解决
第一种解决方案是使用 https://github.com 而不是 git://github.com ，问题就可以解决。
git config --global url."https://".insteadOf git://


