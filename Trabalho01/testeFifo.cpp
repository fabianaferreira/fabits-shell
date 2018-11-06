#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char const * const FIFO_PATH = "my_pipe";
char const * const FIFO_PATH2 = "my_pipe2";

int guard(int ret, char * err) {
  if (ret == -1) { perror(err); exit(1); }
  return ret;
}

void write_all(int fd, char * bytes, size_t nbyte) {
  ssize_t written = 0;
  while(written < nbyte) {
    written += guard(write(fd, bytes+written, nbyte-written), "Could not write to pipe");
  }
}

void write_str(int fd, char * chars) { write_all(fd, chars, strlen(chars)); }

int main(void) {

	char * paths[2]  = {"my_pipe", "my_pipe2"};

	for (unsigned i = 0; i < 1; i++) 
	{		
		pid_t child_pid = fork();
		if (child_pid == 0) {
			// Child
			int pipe_read_fd = guard(open(paths[i], O_RDONLY), "Could not open pipe for reading");
			char buf[10];
			for (;;) {
			  ssize_t num_read = guard(read(pipe_read_fd, buf, sizeof(buf)), "Could not read from pipe");
			  if (num_read == 0) {
			    write_str(1, "Read EOF; closing read end\n");
			    guard(close(pipe_read_fd), "Could not close pipe read end");
			    break;
			  } else {
			    write_str(1, "Read from pipe: ");
			    write_all(1, buf, num_read);
			    write_str(1, "\n");
			  }
		}
		} else {
			// Parent
			guard(mkfifo(paths[i], 0777), "Could not create pipe");
			int pipe_write_fd = guard(open(paths[i], O_WRONLY), "Could not open pipe for writing");
			write_str(pipe_write_fd, "Hello, pipe");
			guard(close(pipe_write_fd), "Could not close pipe write end");
		}
	}
  

  return 0;
}
