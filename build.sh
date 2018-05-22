#!/bin/bash

param=$1;
repository="";
remote="";

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
	echo "Which branch to push"
	read localBranch
	git push -u "${remote}" "${localBranch}"
}

do_make_and_commit(){
	make all
	mv *.o
	mv main
	git add .
	echo "Message du commit"
	read commitMessage
	git commit -m "${commitMessage}"
}

do_init(){
	echo "Set a repository url : "
	read repositoryURL
	echo "Set a remote name"
	read remoteBranch
	remote=${remoteBranch}
	repository=${repositoryURL}
	git remote add "${remoteBranch}" "${repositoryURL}"
}


if  [[ $1 = "-make_commit" ]]; then
    do_make_and_commit
elif [[ $1 = "-push" ]]; then
    do_push
elif [[ $1 = "-make" ]]; then
	do_make
elif [[ $1 = "-commit" ]]; then
	do_commit
elif [[ $1 = "-init" ]]; then
	do_init
fi
