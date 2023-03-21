#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

int main() {
	sem_t *semaphore;
	pid_t pid;
	int status;

	// Create a named semaphore
	semaphore = sem_open("my_semaphore", O_CREAT | O_EXCL, 0644, 1);
	if (semaphore == SEM_FAILED) {
		perror("sem_open() failed");
		exit(1);
	}

	// Fork child processes
	for (int i = 0; i < 5; i++) {
		pid = fork();
		if (pid < 0) {
			perror("fork() failed");
			exit(1);
		} else if (pid == 0) {
			// Child process
			sem_wait(semaphore); // Decrease semaphore value by 1
			printf("Child %d entered critical section.\n", i);
			sleep(2); // Sleep to simulate work inside critical section
			printf("Child %d leaving critical section.\n", i);
			sem_post(semaphore); // Increase semaphore value by 1
			exit(0);
		}
	}

	// Wait for all child processes to finish
	for (int i = 0; i < 5; i++) {
		pid = wait(&status);
		printf("Child %d exited with status %d.\n", pid, status);
	}
	while(1);
	// Close and unlink semaphore
	sem_close(semaphore);
	sem_unlink("/my_semaphore");

	return 0;
}