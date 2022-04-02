主要涉及cat,awk,split,wc



cat test_idc.route|   awk -F' ' '{str="1111";print str, $1,$2,$3,$4}' > warm_env.sh
