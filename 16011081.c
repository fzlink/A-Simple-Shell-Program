#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/wait.h> 

#define MAX_STR 200
#define MAX_ARG 10

char **conInput() {
	char c;
	int i;
	char ** inputs = malloc(MAX_ARG * sizeof(char*));
	char buffer[MAX_STR];
	char  *token;
	i = 0;
	fgets(buffer, MAX_STR, stdin);
	token = strtok(buffer, " ");
	while (token != NULL) {
		inputs[i] = malloc(MAX_STR * sizeof(char));
		strcpy(inputs[i++], token);
		token = strtok(NULL, " ");
	}
	inputs[i - 1][strlen(inputs[i - 1]) - 1] = '\0';
	return inputs;
}

int builtIn(char **inputs) {
	int i = 0;
	int flag = 0;
	char built_in_commands[4][MAX_STR] = {"cd","exit","help","ornekcommand"};

	while (i < 4 && !flag) {
		if (strcmp(inputs[0], built_in_commands[i]) == 0) flag = 1;
		i++;
	}
	i--;
	if (flag) {
		switch (i) {
		case 0:
			chdir(inputs[1]);
			break;
		case 1:
			printf("Gorusmek uzere.\n");
			exit(0);
			break;
		case 2:
			printf("Yardim istediniz.\nFazli Bozatay 16011081 Shell Programi\n");
			break;
		case 3:
			printf("Gizli Built-in ornek komutu calistirdiniz.\n");
			break;
		default:
			break;
		}
	}
	return flag;
}

void execute(char **inputs) {
	pid_t pid = fork();
	int status;
	if (pid < 0) {
		printf("Error");
	}
	else if (pid == 0) {
		if (execvp(inputs[0], inputs) < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else if (pid > 0) {
		while (wait(&status) != pid);
	}
}

int main(int argc, char **argv) {
	char **inputs;
	int is_built_in = 0;
	printf("----------------------------- Isletim Sistemleri ----------------------------\n");
	printf("--------------------------------- SHELL -------------------------------------\n");
	while (1) {
		printf("%s@Shell:~$ ", getenv("USER"));
		is_built_in = 0;
		inputs = conInput();
		is_built_in = builtIn(inputs);
		if (!is_built_in)
			execute(inputs);

	}
	return 0;
}
