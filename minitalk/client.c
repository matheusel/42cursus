#include "minitalk.h"

void	send(int pid, char c)
{
	int bit;
	int i;

	i = 0;
	bit = 0;
	while(bit < 8)
	{
		bit = (c >> i) & 1;
		if(bit == 1)
			kill(pid, SIGUSR1);
		else if (bit == 0)
			kill(pid, SIGUSR2);
		usleep(600);
		bit++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	int i;

	if (argc != 3)
	{
		ft_printf("\nErro: Utilize o programa da maneira correta:\n./client PID MENSAGEM.\n");
		return 0;
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	while(argv[2][i])
	{
		send(pid, argv[2][i]);
		i++;
	}
	send(pid, '\n');


}
