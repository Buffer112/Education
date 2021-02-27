#include "daemonize.h"
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>

#define LOCKFILE "/var/run/daemon.pid"

#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

FILE *f;

void err_quit(const char *msg);

void err_quit(const char *msg)
{
    syslog(LOG_INFO, msg);
}

int lockfile(int fd)
{
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;
    return(fcntl(fd, F_SETLK, &fl));
}
sigset_t mask;

int already_running(void)
{
    int fd;
    char buf[16];
    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0)
    {
        syslog(LOG_ERR, "Can not open (now super user) %s: %s",
        LOCKFILE, strerror(errno));
        exit(1);
    }

    if (lockfile(fd) < 0)
    {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return (1);
        }
        syslog(LOG_ERR, "Can not lock file на %s: %s",
                    LOCKFILE, strerror(errno));
        exit(1);
    }
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf)+1);
    return(0);
}



int main()
{
    int                 i, fd0, fd1, fd2;
    pid_t               pid;
    struct rlimit       rl;
    struct sigaction    sa;

    umask(0);

    pid = fork();
    if (pid != 0) {
        exit(0);
    }
    setsid();
    pid = fork();
    if (pid != 0) {
        exit(0);
    }
    /*
    * Назначить корневой каталог текущим рабочим каталогом,
    * чтобы впоследствии можно было отмонтировать файловую систему.
    */
    if (chdir("/") < 0)
    {
        err_quit("%s: Can not do change dir (chdir)/");
    }

    /*
    * Закрыть все открытые файловые дескрипторы.
    */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);
    /*
    * Присоединить файловые дескрипторы 0, 1 и 2 к /dev/null.
    */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    if (already_running() == 1)
    {
        printf("File is lock!\n");
        syslog(LOG_INFO, "File is lock!\n");
        return 1;
    }
    printf("pid:%d live process\n", getpid());
    while (1)
    {
        //Программа демона
        syslog(LOG_INFO, "Demon is live!");
        sleep(5);
    }
    return 0;
}