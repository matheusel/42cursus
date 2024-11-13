/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dherszen <dherszen@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:06:27 by dherszen          #+#    #+#             */
/*   Updated: 2024/11/13 12:02:10 by dherszen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_status = 0;

static void	print_ascii_1(void);
static void	print_ascii_2(void);
static void	init_shell(t_shell *shell, char **envp);
static void	run_minishell(t_shell *shell);

static void	print_ascii_1(void)
{
	printf("\033[1;34m");
	printf("\n");
	printf("   /================================================\\\n");
	printf("   || __  __  _         _       _            _  _  ||\n");
	printf("   |||  \\/  |(_) _ __  (_) ___ | |__    ___ | || | ||\n");
	printf("   ||| |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || | ||\n");
	printf("   ||| |  | || || | | || |\\__ \\| | | ||  __/| || | ||\n");
	printf("   |||_|  |_||_||_| |_||_||___/|_| |_| \\___||_||_| ||\n");
	printf("   \\================================================/\n");
	print_ascii_2();
}

static void	print_ascii_2(void)
{
	printf("\n\033[0m");
	printf("             ,----------------,              ,---------,\n");
	printf("        ,-----------------------,          ,\"        ,\"|\n");
	printf("      ,\"                      ,\"|        ,\"        ,\"  |\n");
	printf("     +-----------------------+  |      ,\"        ,\"    |\n");
	printf("     |  .-----------------.  |  |     +---------+      |\n");
	printf("     |  | Minishell       |  |  |     | -==----'|      |\n");
	printf("     |  | \033[5m42 Rio\033[0m   ©2024  |  |  |     |         \
|      |\n");
	printf("     |  |                 |  |  |/----|`---=    |      |\n");
	printf("     |  | $ _             |  |  |   ,/|==== ooo |      ;\n");
	printf("     |  |                 |  |  |  // |(((( [33]|    ,\"\n");
	printf("     |  `-----------------'  |,\" .;'| |((((     |  ,\"\n");
	printf("     +-----------------------+  ;;  | |         |,\" \n");
	printf("        /_)______________(_/  //'   | +---------+\n");
	printf("   ___________________________/___  `,\n");
	printf("  /  oooooooooooooooo  .o.  oooo /,   ,\"-----------\n");
	printf(" / ==ooooooooooooooo==.o.  ooo= //   ,`\\--{)B     ,\"\n");
	printf("/_==__==========__==_ooo__ooo=_/'   /___________,\n");
	printf("`-----------------------------'\n");
	printf("\n\033[0m");
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	print_ascii_1();
	init_shell(&shell, envp);
	while (42)
	{
		shell.input = readline("$ ");
		if (shell.input == NULL)
			break ;
		if (!ft_isspace_str(shell.input))
			add_history(shell.input);
		if (check_input_errors(shell.input) || shell.input[0] == '\0'
			|| ft_isspace_str(shell.input))
		{
			free(shell.input);
			continue ;
		}
		run_minishell(&shell);
	}
	rl_clear_history();
	cleanup_resources(NULL, NULL, shell.fd, &shell);
	return (g_status);
}

static void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env_list = (t_env_list){NULL, NULL};
	init_env(envp, &shell->env_list);
	shell->fd[0] = dup(STDIN_FILENO);
	shell->fd[1] = dup(STDOUT_FILENO);
	setup_signal_handling();
}

static void	run_minishell(t_shell *shell)
{
	parse_input(shell);
	expand_var(shell);
	if (redirect(shell) == EXIT_FAILURE)
	{
		if (g_status != 130 && g_status != 2)
			g_status = 1;
	}
	else
		execute_command(shell);
	if (shell->cmds)
		free_cmd_segments(&shell->cmds);
	free(shell->input);
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[1], STDOUT_FILENO);
}
