/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mc-m-el- <mc-m-el-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:24:20 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/12 17:10:15 by mc-m-el-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	CMD = 2,			// Command (e.g., "echo", "ls")
	CMD_ARG = 3,		// Argument to a command
	REDIR_IN = 4,		// Input redirection "<"
	IN_ARG = 5,			// Input redirection argument
	REDIR_OUT = 6,		// Output redirection ">"
	OUT_ARG = 7,		// Output redirection argument
	REDIR_APPEND = 8,	// Append redirection ">>"
	APPEND_ARG = 9,		// Append redirection argument
	HEREDOC = 10,		// Heredoc "<<"
	HEREDOC_ARG = 11,	// Heredoc argument
	PIPE = 12			// Pipe "|" (for print errors only)
}	t_token_type;

typedef struct s_token
{
	struct s_token	*prev;// Pointer to the previous token in this segment
	char			*content; // Token's content ("echo", ">", "file")
	t_token_type	type; // Type of the token (CMD, ARG, REDIRECT, etc.)
	struct s_token	*next;// Pointer to the next token in this segment
}	t_token;

typedef struct s_cmd
{
	char	*cmd;			// The command segment ("echo hello > file")
	int		fd_in;			// File descriptor for input (stdin redirection)
	int		fd_out;			// File descriptor for output (stdout redirection)
	pid_t	pid;			// Process ID for command execution	char
	int		should_execute;	// Flag to indicate if the command should be
	t_token	*tokens_list;	// Linked list of tokens (CMD, ARG, and redirects)
}	t_cmd;

typedef struct s_token_context
{
	t_token	**tokens_list;
	t_token	**last_token;
	char	*cmd;
}	t_token_context;

typedef struct s_split_context
{
	int	start;
	int	index;
	int	quote_single;
	int	quote_double;
}	t_split_context;

typedef enum e_builtins
{
	ECHO = 2,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtins;

// environment variable node struct
typedef struct s_env_node
{
	struct s_env_node	*prev;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

// environment list struct with pointers to head and tail
typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
}	t_env_list;

// main struct to store important variables
typedef struct s_shell
{
	char		*input;			// Input from readline
	t_env_list	env_list;		// Linked list of environment variables
	t_cmd		**cmds;			// Array of command structs (pipeline)
	int			fd[2];			// File descriptors for pipe
}	t_shell;

// struct needed to variable expansion
typedef struct s_split
{
	char			*str;
	struct s_split	*next;
}	t_split;

// struct needed for arguments of handle_fork() function
typedef struct s_fork_args
{
	t_cmd	*cmd;
	char	**argv;
	char	**envp;
	int		fd[2];
}	t_fork_args;

#endif
