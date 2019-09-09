if [ "`id -u` -eq 0" ]; then
	PS1='@\h:\w #'
elif [ "'id -u' -eq 1" ]; then
	PS1='\u@:\w\$'
fi