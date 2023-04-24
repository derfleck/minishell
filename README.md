# Minishell

| **name**         | **library** | **description**                                    | **return**                                                                           | **required for**                        |
| ---------------- | ----------- | -------------------------------------------------- | ------------------------------------------------------------------------------------ | --------------------------------------- |
| readline         | stdio.h     | reads a line from the terminal and returns it      | NULL if EOF, empty for empty line, returns text of line as char*, needs to be free'd | reading input from the terminal         |
| rl_clear_history |             |                                                    |                                                                                      |                                         |
| rl_on_new_line   |             |                                                    |                                                                                      |                                         |
| rl_replace_line  |             |                                                    |                                                                                      |                                         |
| rl_redisplay     |             |                                                    |                                                                                      |                                         |
| add_history      |             |                                                    |                                                                                      |                                         |
| printf           |             |                                                    |                                                                                      |                                         |
| malloc           |             |                                                    |                                                                                      |                                         |
| free             |             |                                                    |                                                                                      |                                         |
| write            |             |                                                    |                                                                                      |                                         |
| access           |             |                                                    |                                                                                      |                                         |
| open             |             |                                                    |                                                                                      |                                         |
| read             |             |                                                    |                                                                                      |                                         |
| close            |             |                                                    |                                                                                      |                                         |
| fork             |             |                                                    |                                                                                      |                                         |
| wait             |             |                                                    |                                                                                      |                                         |
| waitpid          |             |                                                    |                                                                                      |                                         |
| wait3            |             |                                                    |                                                                                      |                                         |
| wait4            |             |                                                    |                                                                                      |                                         |
| signal           |             |                                                    |                                                                                      |                                         |
| sigaction        |             |                                                    |                                                                                      |                                         |
| sigemptyset      |             |                                                    |                                                                                      |                                         |
| sigaddset        |             |                                                    |                                                                                      |                                         |
| kill             |             |                                                    |                                                                                      |                                         |
| exit             |             |                                                    |                                                                                      |                                         |
| getcwd           |             |                                                    |                                                                                      |                                         |
| chdir            |             |                                                    |                                                                                      |                                         |
| stat             |             |                                                    |                                                                                      |                                         |
| lstat            |             |                                                    |                                                                                      |                                         |
| fstat            |             |                                                    |                                                                                      |                                         |
| unlink           |             |                                                    |                                                                                      |                                         |
| execve           |             |                                                    |                                                                                      |                                         |
| dup              |             |                                                    |                                                                                      |                                         |
| dup2             |             |                                                    |                                                                                      |                                         |
| pipe             |             |                                                    |                                                                                      |                                         |
| opendir          |             |                                                    |                                                                                      |                                         |
| readdir          |             |                                                    |                                                                                      |                                         |
| closedir         |             |                                                    |                                                                                      |                                         |
| strerror         |             |                                                    |                                                                                      |                                         |
| perror           |             |                                                    |                                                                                      |                                         |
| isatty           |             |                                                    |                                                                                      |                                         |
| ttyname          |             |                                                    |                                                                                      |                                         |
| ttyslot          |             |                                                    |                                                                                      |                                         |
| ioctl            |             |                                                    |                                                                                      |                                         |
| getenv           | stdlib.h    | gets an environment variable specified as argument | if found, returns value string, NULL if there is no match                            | used to find the full path to functions |
| tcsetattr        |             |                                                    |                                                                                      |                                         |
| tcgetattr        |             |                                                    |                                                                                      |                                         |
| tgetent          |             |                                                    |                                                                                      |                                         |
| tgetflag         |             |                                                    |                                                                                      |                                         |
| tgetnum          |             |                                                    |                                                                                      |                                         |
| tgetstr          |             |                                                    |                                                                                      |                                         |
| tgoto            |             |                                                    |                                                                                      |                                         |
| tputs            |             |                                                    |                                                                                      |                                         |

## Useful links

- [BASH Manual](https://www.gnu.org/software/bash/manual/bash.html)

- [Building a simple shell](https://blog.ehoneahobed.com/building-a-simple-shell-in-c-part-1): tutorial explaining how to build a very simple shell from the ground up

- [Minishell project of other 42 students](https://github.com/zstenger93/minishell)

- [Tutorial - write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
