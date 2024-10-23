#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SERVICES 8

typedef struct {
    char name[50];
    char state[20];
} Service;

char input[50];


void showAllServices() {
    showUpServices();
    showDownServices();
    printf("\n");
    
}

void showUpServices() {
    FILE *file = fopen("services.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    Service services[MAX_SERVICES];
    int num_services = 0;

    // Read services and their states from the file
    while (fscanf(file, "%s %s", services[num_services].name, services[num_services].state) == 2) {
        num_services++;
        if (num_services >= MAX_SERVICES) {
            break;
        }
    }

    fclose(file);

    // Display services that are "up"
    printf("\nServices that are up:\n");
    for (int i = 0; i < num_services; i++) {
        if (strcmp(services[i].state, "up") == 0) {
            printf("%s \e[0;32m%s\e[0;37m\n", services[i].name,services[i].state);
        }
    }
    printf("\n");
}


void showDownServices() {
    FILE *file = fopen("services.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    Service services[MAX_SERVICES];
    int num_services = 0;

    // Read services and their states from the file
    while (fscanf(file, "%s %s", services[num_services].name, services[num_services].state) == 2) {
        num_services++;
        if (num_services >= MAX_SERVICES) {
            break;
        }
    }

    fclose(file);

    // Display services that are "down"
    printf("\nServices that are down:\n");
    for (int i = 0; i < num_services; i++) {
        if (strcmp(services[i].state, "down") == 0) {
            printf("%s \e[0;31m%s\e[0;37m\n", services[i].name,services[i].state);
        }
    }
    printf("\n");
}

void showLogs() {
    FILE *file = fopen("services_logs.txt", "r");
    if (file == NULL) {
        printf("Error opening the file %s.\n", "services_logs.txt");
        return;
    }

    printf("\nShowing logs...\n");
    char buffer[1024]; 

    // Read and print each line of the file until the end is reached
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    printf("\n");
}


void showHelp() {
    printf("\nAvailable commands:\n");
    printf("show all \n");
    printf("show up \n");
    printf("show down \n");
    printf("show logs \n");
    printf("show help\n");
    printf("clear\n");
    printf("exit\n\n");
}

void getCommand(){
	char keep[50];
	read(STDIN_FILENO, keep, 200);
	strcpy(input, keep);
}

void Banner() {
    printf("*********************************************\n");
    printf("*                                           *\n");
    printf("*           Welcome to Your CLI             *\n");
    printf("*                                           *\n");
    printf("*          Type 'show help' for help        *\n");
    printf("*                                           *\n");
    printf("*********************************************\n\n");
}
void clearScreen() {
    printf("\033[2J\033[1;1H"); 
}

int main() {
    char *arg1, *arg2, *command ;
	Banner();
	
    while (1) {
    fflush(stdout);
	printf("\e[0;32mCLI@RAVEN\e[0;37m# ");
	fflush(stdout);
        getCommand();
        
        char *ptrn = strchr(input, '\n'); 
    	if(ptrn != NULL)
    		*ptrn = '\0'; 

        command = strtok(input, " ");
        if (command == NULL) {
            continue;
        }

        arg1 = strtok(NULL, " ");
        arg2 = strtok(NULL, " ");

        if (strcmp(command, "show") == 0) {
            if (strcmp(arg1, "all") == 0 && arg2 == NULL) {
                    showAllServices();
            } else if (strcmp(arg1, "up") == 0 && arg2 == NULL) {
                showUpServices();
            } else if (strcmp(arg1, "down") == 0 && arg2 == NULL) {
                showDownServices();
            } else if (strcmp(arg1, "logs") == 0 && arg2 == NULL) {
                showLogs();
            } else if (strcmp(arg1, "help") == 0 && arg2 == NULL) {
                showHelp();
            } else {
                printf("Invalid command. Type 'show help' for available commands.\n");
            }
        }else if(strcmp(command, "clear") == 0){
        	clearScreen();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid command. Type 'show help' for available commands.\n");
        }
    }

    return 0;
}
