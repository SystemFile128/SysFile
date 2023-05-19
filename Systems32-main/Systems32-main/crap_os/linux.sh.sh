#!/bin/bash
echo"1. Date"
echo"2. Current User"
echo"3. num of file in current directory"
echo"4. current directory"
readn
case $n in
  1) echo `date`;;
  2) echo `whoami`;;
  3) echo `ls-1|wc-l`;;
  4) echo `pwd`;;
  *) echo "Wrong Choice, Enter Again";;
esac
