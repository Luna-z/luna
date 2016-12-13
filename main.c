#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "make_log.h"

#define FILE_ID_LEN (256)

#define LOG_TEST_MUDULE "test"
#define LOG_TEST_PROC "fdfs"

int main(int argc, char * argv[])
{
	pid_t pid;
	int pfd[2];
	char file_id[FILE_ID_LEN]= {0};

	if(argc < 2)
	{
		printf("usage: ./a.out filepath\n");
		exit(1);
	}
	if(pipe(pfd) < 0)
	{
		perror("pipe error");
		exit(1);
	}	

	pid = fork();
	if(pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		execlp("fdfs_upload_file","fdfs_upload_file","/etc/fdfs/client.conf",argv[1],NULL);
		perror("exec error");
	}
	else
	{	
		close(pfd[1]);
		wait(NULL);
		read(pfd[0], file_id, FILE_ID_LEN);
		LOG(LOG_TEST_MUDULE, LOG_TEST_PROC, "file_id = [%s]", file_id);
                printf("file_id = %s \n", file_id);
	}
	return 0;
}

