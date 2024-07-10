#!/bin/bash
# MINISHELL-TESTER
# Modified copy of https://github.com/solaldunckel/minishell-tester

RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
YELLOW="\033[1;33m"

BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

PASSED=0
WRONG=0
TOTAL=0
IS_CORRECT=0

function exec_test()
{
	IS_CORRECT=0
	$(echo "$@" > testin)
	TEST1=$(< testin ./minishell 2>1)
	ES_1=$?
	TEST2=$(< testin bash 2>1)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		((PASSED++))
		IS_CORRECT=1
	else
		((WRONG++))
		printf $CYAN"$@$RESET\n"
	fi
	if [ "$TEST1" != "$TEST2" ]; then
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n\n"
	fi
	if [ "$IS_CORRECT" == "0" ]; then
		printf "\n\n"
	fi
	((TOTAL++))
	sleep 0.1
}

function exec_test_mult()
{
	IS_CORRECT=0
	$(echo "$ARG1" > testin)
	TEST1=$(< testin ./minishell 2>1)
	ES_1=$?
	$(echo "$ARG2" > testin)
	TEST2=$(< testin bash 2>1)
	ES_2=$?
	if [ "$TEST1" == "$TEST2" ] && [ "$ES_1" == "$ES_2" ]; then
		((PASSED++))
		IS_CORRECT=1
	else
		((WRONG++))
		echo
		printf $BOLDRED"$ARG1$RESET\n"
		printf $BOLDGREEN"$ARG2$RESET\n"
		echo
	fi
	if [ "$TEST1" != "$TEST2" ]; then
		printf $BOLDRED"Your output : \n%.20s\n$BOLDRED$TEST1\n%.20s$RESET\n" "-----------------------------------------" "-----------------------------------------"
		printf $BOLDGREEN"Expected output : \n%.20s\n$BOLDGREEN$TEST2\n%.20s$RESET\n\n" "-----------------------------------------" "-----------------------------------------"
	fi
	if [ "$ES_1" != "$ES_2" ]; then
		printf $BOLDRED"Your exit status : $BOLDRED$ES_1$RESET\n"
		printf $BOLDGREEN"Expected exit status : $BOLDGREEN$ES_2$RESET\n\n"
	fi
	if [ "$IS_CORRECT" == "0" ]; then
		printf "\n\n"
	fi
	((TOTAL++))
	sleep 0.1
}

echo
bash --version
echo
printf "$BOLDMAGENTA __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
printf "|  \/  |_   _| \ | |_   _|/ ____| |  | |  ____| |    | |     \n"
printf "| \  / | | | |  \| | | | | (___ | |__| | |__  | |    | |     \n"
printf "| |\/| | | | | . \` | | |  \___ \|  __  |  __| | |    | |     \n"
printf "| |  | |_| |_| |\  |_| |_ ____) | |  | | |____| |____| |____ \n"
printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\n$RESET"
echo
echo

printf $YELLOW"ECHO\n\n$RESET"
exec_test 'echo test tout'
exec_test 'echo test      tout'
exec_test 'echo -n test tout'
exec_test 'echo -n -n -n test tout'
exec_test 'echo'
exec_test 'echo ñ'
exec_test 'echo hi'
exec_test '/bin/echo hi'
exec_test 'echo $PATH'
exec_test 'echo $NOFNAJDFKADFKADJFKJ'
exec_test 'echoecho'
exec_test 'echo -n'
exec_test 'echo -n hi'
exec_test 'echo --n hi'
exec_test 'echo -nn hi'
exec_test 'echo -n -n hi'
exec_test 'echo hi -n'
exec_test 'echo "-n -n -n" -n hi'
exec_test 'echo -nnnnnnn -n -nnnnnnnnnnnn -n -n hi'
exec_test 'echo -nn -n -nnnnnnnnnnnn -n -n -n-n hi'
exec_test 'echo -nn -n -nnnnnnnnnnnn -n -n -n-n hi -nnn -n -n'
exec_test 'echo "-nnnnnn -nnnnn" hi'
exec_test 'echo $?USER'
exec_test 'echo "$?USER"'
exec_test 'echo "$?USER" $? $?USER $USER $USER'


printf $YELLOW"CD\n\n$RESET"
exec_test 'cd ..
pwd'
exec_test 'cd /Users
pwd'
exec_test 'cd 
pwd'
# exec_test 'mkdir test_dir
# cd test_dir
# rm -rf ../test_dir
# cd .
# pwd
# cd .
# pwd
# cd ..
# pwd'


printf $YELLOW"PIPE\n\n$RESET"
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'

printf $YELLOW"EXPANSIONS\n\n$RESET"
exec_test 'echo $TEST'
exec_test 'echo "$TEST"'
exec_test "echo '$TEST'"
exec_test 'echo "$TEST$TEST$TEST"'
exec_test 'echo "$TEST$TEST=lol$TEST"'
exec_test 'echo "   $TEST lol $TEST"'
exec_test 'echo $TEST$TEST$TEST'
exec_test 'echo $TEST$TEST=lol$TEST""lol'
exec_test 'echo    $TEST lol $TEST'
exec_test 'echo test "" test "" test'
exec_test 'echo "$=TEST"'
exec_test 'echo "$"'
exec_test 'echo "$?TEST"'
exec_test 'echo $TEST $TEST'
exec_test 'echo "$T1TEST"'


printf $YELLOW"EXIT\n\n$RESET"
exec_test "exit 42"
exec_test "exit 42 53 68"
exec_test "exit 259"
exec_test "exit 9223372036854775807"
exec_test "exit -9223372036854775808"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775810"
exec_test "exit -4"
exec_test "exit wrong"
exec_test "exit wrong_command"
exec_test "gdagadgag"
exec_test "ls -Z"
exec_test "cd gdhahahad"
exec_test "ls -la | wtf"
exec_test "echo \"\""
exec_test "exit"
exec_test "exit \"\""
exec_test "exit \" \""
exec_test "exit \"  \""
exec_test "exit \"	\""
exec_test "exit 42network"
exec_test "exit +"
exec_test "exit ++"
exec_test "exit -"
exec_test "exit ---"
exec_test "exit 0"
exec_test "exit +0"
exec_test "exit ++0"
exec_test "exit -0"
exec_test "exit --0"
exec_test "exit 1"
exec_test "exit +1"
exec_test "exit ++1"
exec_test "exit -1"
exec_test "exit --1"
exec_test "exit ' 3'"
exec_test "exit '3 '"
exec_test "exit 255"
exec_test "exit -255"
exec_test "exit 256"
exec_test "exit 2147483647"
exec_test "exit 2147483648"
exec_test "exit -2147483648"
exec_test "exit -2147483649"
exec_test "exit 4294967295"
exec_test "exit 4294967296"
exec_test "exit -4294967296"
exec_test "exit -4294967297"
exec_test "exit 9223372036854775807"
exec_test "exit 9223372036854775808"
exec_test "exit -9223372036854775808"
exec_test "exit -9223372036854775809"
exec_test "exit 18446744073709551615"
exec_test "exit 18446744073709551616"
exec_test "exit -18446744073709551616"
exec_test "exit -18446744073709551617"
exec_test "exit 9999999999999999999999"
exec_test "exit 0000000000000000000000"
exec_test "exit 0000000000000000000001"
exec_test "exit 1 2 3"
exec_test "exit 1 2 3
echo should not exit"
exec_test "exit 1 not numeric bro"
exec_test "exit not numeric bro 2"
exec_test "exit 42 | cat"
exec_test "Exit 1
echo is not a builtin"
exec_test "aaa
exit 1"
exec_test "touch testingfile
chmod 000 testingfile"
exec_test "cat testingfile
exit"
exec_test "cat testingfile
exit 1"
exec_test "cat src
exit"
exec_test "cat src
exit 1"
exec_test "cafkajdkf
exit"
exec_test "calfakfkakd
exit 1"
exec_test "cat Makefile
exit"
exec_test "cat Makefile
exit 1"
exec_test "cat /bin
exit"
exec_test "cat /bin
exit 1"
exec_test "chmod 777 testingfile
rm -rf testingfile"


printf $YELLOW"ENV EXPANSIONS\n\n$RESET"
ENV_SHOW="env | sort | grep -v SHLVL | grep -v _="
EXPORT_SHOW="export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD"
exec_test 'export ='
exec_test 'export 1TEST=
' $ENV_SHOW
exec_test 'export TEST 
' $EXPORT_SHOW
exec_test 'export ""="" 
' $ENV_SHOW
exec_test 'export TES=T="" 
' $ENV_SHOW
exec_test 'export TE+S=T="" 
' $ENV_SHOW
exec_test 'export TEST=LOL 
echo $TEST
' $ENV_SHOW
exec_test 'export TEST=LOL
echo $TEST$TEST$TEST=lol$TEST'
exec_test 'export TEST=LOL
export TEST+=LOL
echo $TEST
' $ENV_SHOW
exec_test $ENV_SHOW
exec_test $EXPORT_SHOW
exec_test 'export TEST="ls       -l     - a" 
echo $TEST 
$LS
' $ENV_SHOW


printf $YELLOW"PIPE\n\n$RESET"
exec_test 'cat tests/lorem.txt | grep arcu | cat -e'
exec_test 'echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e'
exec_test 'cat /dev/random | head -c 100 | wc -c'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
exec_test 'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'


printf $YELLOW"REDIRECTIONS\n\n$RESET"
exec_test 'echo test > ls
cat ls'
exec_test 'echo test > ls >> ls >> ls 
 echo test >> ls
 cat ls'
exec_test '> lol echo test lol
 cat lol'
exec_test '>lol echo > test>lol>test>>lol>test mdr >lol test >test
 cat test'
exec_test 'cat < ls'
exec_test 'cat < ls > ls'


printf $YELLOW"SYNTAX ERROR\n\n$RESET"
exec_test '| test'
exec_test 'echo > <'
exec_test 'echo | |'
exec_test '<'


printf $YELLOW"EXPAND ARGUMENTS\n\n$RESET"
exec_test 'export x="1 a 2"
exit "$x"$x"$x"'
exec_test 'export x="a 2"
exit "$x"$x"$x"'
exec_test 'export x="1 b"
exit "$x"$x"$x"'
exec_test 'export x="1 2"
exit "$x"$x"$x"'
exec_test 'export x="12"
exit "$x"$x"$x"'
exec_test 'export x="12a"
exit "$x"$x"$x"'
exec_test 'export x="1"
exit "$x"$x"$x"'
exec_test 'export x="a b"
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x="a b"
echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x="  ab  "
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x="  ab  "
echo echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x="  a  b  "
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x="  a  b  "
echo echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x=" a    b"
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x=" a    b"
echo echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x="a  b   "
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x="a  b   "
echo echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x=" ab ab  a b  "
echo "$x"$x"$x"
cat "$x"$x"$x"'
exec_test 'export x=" ab ab  a b  "
echo echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"
cat echo ""1"x"$x $x$x"$x$x" $x$x"$x" "$x"$x"$x"'
exec_test 'export x="a b   c"
export z=""
echo "$z$x$z"$z$x$z"$z$x$z"$z
cat "$z$x$z"$z$x$z"$z$x$z"$z'
exec_test 'export x="a b   c"
export y=""
echo "$y"1"x"$x ""$y $y$y$y$y $y$y$y$y $y$y$y$y "$x$x""$x""$x""" $x$x"$x" $y"$x"$x"$x"$y
cat "$y"1"x"$x ""$y $y$y$y$y $y$y$y$y $y$y$y$y "$x$x""$x""$x""" $x$x"$x" $y"$x"$x"$x"$y'
exec_test "echo \"\" ''
cat \"\" ''"


printf $YELLOW"EXPAND REDIRECTIONS\n\n$RESET"
exec_test 'export x="test file"
echo "testing..." > $x'
exec_test 'export x="  test  file  "
echo "testing..." > $x'
exec_test 'export x="    test  file"
echo "testing..." > $x'
exec_test 'export x="test  file    "
echo "testing..." > $x'
exec_test 'export x="testfile"
echo "testing..." > $x
rm -rf testfile'
exec_test 'export x="    testfile   "
echo "testing..." > $x
rm -rf testfile'
exec_test 'export x="te"
export y="st"
export z="fi"
export zz="le"
echo "testing..." > "$x"$y"$z"$zz
rm -rf testfile'
exec_test 'export x="te"
export y="sssssst"
export z="fi"
export zz="le"
echo "testing..." > "$x"$y "$z"
rm -rf tesssssst'


function testshlvl()
{
	echo 'echo $SHLVL' > tmptest
	ARG1="export SHLVL=$@
	./minishell < tmptest | tr -s '[:blank:]'"
	ARG2="export SHLVL=$@
	bash < tmptest | tr -s '[:blank:]'"
	exec_test_mult $ARG1 $ARG2
}
testshlvl '-1'
testshlvl '-999'
testshlvl '-9'
testshlvl ''
testshlvl 'aaaa'
testshlvl '-1asdasdads'
testshlvl 'a-1'
testshlvl "1000"
testshlvl "123992138192381293819238129381293812391823192381923819238192381923819283192839123898"
testshlvl "-123992138192381293819238129381293812391823192381923819238192381923819283192839123898"
testshlvl "999"


echo
if [ "$PASSED" == "$TOTAL" ]; then
	printf "🧊🐧🧊 Pingu is here !!!!!\n\n✅ YOU MADE IT! $BOLDGREEN($TOTAL / $TOTAL) $RESET\n"
else
	printf $BOLDRED"Wrong: $WRONG$RESET$BOLDGREEN  Passed: $PASSED$RESET  Total: $TOTAL"
fi
echo
echo


rm testin lol ls test tmptest 1


exit $WRONG