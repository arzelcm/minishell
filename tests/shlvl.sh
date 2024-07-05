echo "export SHLVL=-1;
echo $SHLVL" > shlvltest
./minishell < shlvltest > shlvlres;
cat shlvlres;
