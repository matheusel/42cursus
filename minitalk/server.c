#include "minitalk.h"

void	handler()
{

}

int	main(void)
{
	int	pid;
	struct	sigaction	sa;

	ft_printf("PID: %i\n", pid = getpid());
	if (pid < 0)
	{
		ft_printf("\nErro: Não foi possível obter o PID\n");
		return -1;
	}
}
