#!/bin/bash

param=$1;

do_commit(){
	git add .
	echo "Message du commit"
	read commitMessage
	git commit -m "${commitMessage}"

}

do_make(){
	make all
}

do_push(){
	git push -u origin master
}

do_Make_cm(){
	make all
	mv *.o
	mv main
	git add .
	echo "Message du commit"
	read commitMessage
	git commit -m "${commitMessage}"
}

if  [[ $1 = "-cm" ]]; then
    do_Make_cm
elif [[ $1 = "-p" ]]; then
    do_push
elif [[ $1 = "-make" ]]; then
	do_make
elif [[ $1 = "-c" ]]; then
	do_commit
fi
