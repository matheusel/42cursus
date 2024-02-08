#include "minitalk.h"

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_printf("\nErro: Utilize o programa da maneira correta:\n./client PID MENSAGEM.\n");
		return -1;
	}

	pid = *argv[1];
}
