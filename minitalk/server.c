#include "minitalk.h"

void	handler(int	sig)
{
	ft_printf("handler");
}

int	main(void)
{
	int	pid;
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = handler;

	ft_printf("PID: %i\n", pid = getpid());
	if (pid < 0)
	{
		ft_printf("\nErro: Não foi possível obter o PID\n");
		return -1;
	}
	ft_printf("\nAguardando por uma mensagem...\n");
	while (1)
	{	
		if (sigaction(SIGUSR1, &sa, NULL) < 0)
			ft_printf("\nErro: Não foi possível obter o PID\n");
		else if (sigaction(SIGUSR2, &sa, NULL) < 0)
			ft_printf("\nErro: Não foi possível obter o PID\n");
		pause();
	}
}
