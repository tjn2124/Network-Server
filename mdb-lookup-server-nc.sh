#!/bin/sh

on_ctrl_c() {
           echo "Ignoring Ctrl-C"
}

trap on_ctrl_c INT 


mkfifo mypipe-$$

cat mypipe-$$ | nc -l $1 | /home/jae/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe-$$

echo removing mypipe-$$
rm mypipe-$$

