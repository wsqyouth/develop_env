ref: https://blog.csdn.net/qq_27715357/article/details/106734411

1. 
sudo yum install epel-release
sudo yum -y install https://rpms.remirepo.net/enterprise/remi-release-7.rpm

2. 
sudo yum -y install yum-utils
yum repolist all |grep php
sudo yum-config-manager --enable remi-php74
sudo yum install php  php-cli php-fpm php-mysqlnd php-zip php-devel php-gd php-mcrypt php-mbstring php-curl php-xml php-pear php-bcmath php-json php-redis

3.
php -v
php --modules

