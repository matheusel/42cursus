#include "minitalk.h"

void	handler(int	sig)
{
	static char	c = 0;
	static int	i = 0;

	if(sig == SIGUSR1)
	{
		sig |= (1 << i);
		ft_printf("%s", "Recebido S1");
	}
	else if(sig == SIGUSR2)
	{
		sig |= (0 << i);
		ft_printf("%s", "Recebido S1");
	}
	i++;
	if(i == 8)
	{
		ft_printf("%c", c);
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	ft_printf("\nPID: %i\n", pid = getpid());
	if (pid < 0)
	{
		ft_printf("\nErro: Não foi possível obter o PID\n");
		return 0;
	}
	ft_printf("\nAguardando mensagem...\n");
	while (1)
	{	
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		pause();
	}
	return (0);
}
