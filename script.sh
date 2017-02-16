while [ 1 -a -n $1 ]
	do
		leaks $1
		sleep 1
	done
