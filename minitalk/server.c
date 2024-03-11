#include "minitalk.h"

void	handler(int	sig)
{
	static char	c;
	static int	i;

	if(sig == SIGUSR1)
	{
		c |= (1 << i);
	}
	else if(sig == SIGUSR2)
	{
		c |= (0 << i);
	}
	i++;
	if(i == 8)
	{
		ft_printf("%c", c);
		c = 0;
		i = 0;
	}
}

int	main()
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
