#include "minitalk.h"

void	handler(int	sig, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	x = 0;

	ft_printf("%s", "chegou man");

}

int	main(void)
{
	int	pid;
	struct	sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
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
