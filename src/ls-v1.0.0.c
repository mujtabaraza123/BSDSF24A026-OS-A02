/*
* Programming Assignment 02: lsv1.0.0
* This is the source file of version 1.0.0
* Read the write-up of the assignment to add the features to this base version
* Usage:
*       $ lsv1.0.0 
*       % lsv1.0.0  /home
*       $ lsv1.0.0  /home/kali/   /etc/
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

extern int errno;

void do_ls(const char *dir);
void do_long_listing(const char *dir);
void print_permissions(mode_t mode);

void print_permissions(mode_t mode)
{
    char p[11];

    p[0] = S_ISDIR(mode) ? 'd' :
           S_ISLNK(mode) ? 'l' : '-';

    p[1] = (mode & S_IRUSR) ? 'r' : '-';
    p[2] = (mode & S_IWUSR) ? 'w' : '-';
    p[3] = (mode & S_IXUSR) ? 'x' : '-';

    p[4] = (mode & S_IRGRP) ? 'r' : '-';
    p[5] = (mode & S_IWGRP) ? 'w' : '-';
    p[6] = (mode & S_IXGRP) ? 'x' : '-';

    p[7] = (mode & S_IROTH) ? 'r' : '-';
    p[8] = (mode & S_IWOTH) ? 'w' : '-';
    p[9] = (mode & S_IXOTH) ? 'x' : '-';

    if (mode & S_ISUID)
        p[3] = (mode & S_IXUSR) ? 's' : 'S';

    if (mode & S_ISGID)
        p[6] = (mode & S_IXGRP) ? 's' : 'S';

    if (mode & S_ISVTX)
        p[9] = (mode & S_IXOTH) ? 't' : 'T';

    p[10] = '\0';

    printf("%s", p);
}

void do_long_listing(const char *dir)
{
    DIR *dp = opendir(dir);
    struct dirent *entry;

    if (dp == NULL)
    {
        perror(dir);
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;

        char path[1024];
        struct stat file_stat;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        if (lstat(path, &file_stat) == -1)
        {
            perror(entry->d_name);
            continue;
        }

        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group *gr = getgrgid(file_stat.st_gid);
        char *time_str = ctime(&file_stat.st_mtime);

        print_permissions(file_stat.st_mode);

       printf(" %2lu %-8s %-8s %8lld ",(unsigned long)file_stat.st_nlink, pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown", (long long)file_stat.st_size);

        if (time_str != NULL)
        {
            time_str[24] = '\0';
            printf("%s ", time_str);
        }

        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}

int main(int argc, char const *argv[])
{
    int opt;
    int long_format = 0;

    while ((opt = getopt(argc, (char * const *)argv, "l")) != -1)
    {
        if (opt == 'l')
            long_format = 1;
        else
        {
            fprintf(stderr, "Usage: %s [-l] [directory]\n", argv[0]);
            return 1;
        }
    }

    if (optind < argc)
    {
        for (int i = optind; i < argc; i++)
        {
            printf("Directory listing of %s:\n", argv[i]);

            if (long_format)
                do_long_listing(argv[i]);
            else
                do_ls(argv[i]);

            puts("");
        }
    }
    else
    {
        if (long_format)
            do_long_listing(".");
        else
            do_ls(".");
    }

    return 0;
}

void do_ls(const char *dir)
{
    struct dirent *entry;
    DIR *dp = opendir(dir);
    if (dp == NULL)
    {
        fprintf(stderr, "Cannot open directory : %s\n", dir);
        return;
    }
    errno = 0;
    while ((entry = readdir(dp)) != NULL)
    {
        if (entry->d_name[0] == '.')
            continue;
        printf("%s\n", entry->d_name);
    }

    if (errno != 0)
    {
        perror("readdir failed");
    }

    closedir(dp);
}
