/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:11:01 by soel-bou          #+#    #+#             */
/*   Updated: 2024/01/12 00:29:42 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "./printf/ft_printf.h"

void    reset(unsigned char *c, int *bits)
{
    write(1, c, 1);
    *bits = 7;
    *c = 0;
}

void    handler(int sig, siginfo_t *info, void *context)
{
    static unsigned char c;
    static int          bits;
    static int          pid;

    (void)context;
    if (pid != info->si_pid)
    {
        bits = 7;
        c = 0;
        pid = info->si_pid;
    }
    if (sig == SIGUSR1)
        c = c << 1;
    else if (sig == SIGUSR2)
        c = (c << 1) | 1;
    bits--;
    if (bits < 0)
        reset( &c, &bits);
}

int main(void)
{
    ft_printf("Server PID: %d\n", getpid());
    struct sigaction	sa;
	sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
    {
        pause();
    }
    return (0);
}