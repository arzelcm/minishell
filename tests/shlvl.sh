# echo "export SHLVL=-1;
# echo $SHLVL" > shlvltest
# ./minishell < shlvltest > shlvlres;
# cat shlvlres;

test "export SHLVL=-1\necho"hola""

test() {
	echo "$1" >.own_test
	./minishell < .own_test > .own_test_res;
	cat .own_test_res;
	# rm -f .own_test .own_test_res;
}
