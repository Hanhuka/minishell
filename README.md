# Minishell

## This is a group project where me and [PedroCVera](https://github.com/PedroCVera) made a simpler version of bash in C.

Our implementation features:
  * pipes
  * env variables (variable expansion with '$')
  * command history
  * exit codes that can be accessed with '$?'
  * single ' and double " quotes handling
  * input (<) output (>) heredoc (<<) append (>>) 
  * ctrl-C crlt-D and ctrl-\ signals
  *  built-in functions: echo (with -n flag), cd (relative or absolute path), pwd, export, unset, env and exit


##Implementation Details

Text input as well as the history are handled with the readline library. 
Every command is given it's own process given that all of them should run parallel to each other 
Since For execution the number of pipes is always checked 

