/* #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    while (1) {
        system("clear");
        printf("Lab 4: System Call Demonstration\n");
        printf("1. Process Related System Calls\n");
        printf("2. File Related System Calls\n");
        printf("3. Communication System Calls\n");
        printf("4. Information Related System Calls\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Process Related System Calls
                printf("1. fork\n");
                printf("2. exit\n");
                printf("3. wait\n");

                int sub_choice;
                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing fork system call...\n");
                        pid_t child_pid = fork();
                        if (child_pid == 0) {
                            printf("This is the child process.\n");
                        } else if (child_pid > 0) {
                            printf("This is the parent process. Child Process ID: %d\n", child_pid);
                        } else {
                            printf("Fork failed.\n");
                        }
                        break;
                    case 2:
                        printf("Executing exit SysCall...\n");
                        exit(0);
                        break;
                    case 3:
                        printf("Executing wait SysCall...\n");
                        sleep(4);
                        wait(NULL);
                        printf("Child process Completed.\n");
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 2: // File Related System Calls
                printf("1. open\n");
                printf("2. read\n");
                printf("3. write\n");
                printf("4. close\n");
                printf("5. link\n");
                printf("6. unlink\n");
                printf("7. stat\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing open system call...\n");
                        int fd = open("sample.txt", O_CREAT | O_WRONLY, 0644);
                        if (fd != -1) {
                            printf("File opened for writing.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 2:
                        printf("Executing read system call...\n");
                        fd = open("sample.txt", O_RDONLY);
                        if (fd != -1) {
                            char content[100];
                            ssize_t bytesRead = read(fd, content, sizeof(content));
                            if (bytesRead > 0) {
                                content[bytesRead] = '\0';
                                printf("Content read from file: %s\n", content);
                            } else {
                                printf("Error reading file.\n");
                            }
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 3:
                        printf("Executing write system call...\n");
                        fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd != -1) {
                            write(fd, "Hello, world!", 13);
                            printf("Content written to file.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 4:
                        printf("Executing close system call...\n");
                        close(sub_choice); // Replace sub_choice with actual file descriptor
                        printf("File closed.\n");
                        break;
                    case 5:
                        printf("Executing link system call...\n");
                        link("sample.txt", "sample_link.txt");
                        printf("Hard link created.\n");
                        break;
                    case 6:
                        printf("Executing unlink system call...\n");
                        unlink("sample_link.txt");
                        printf("Hard link removed.\n");
                        break;
                    case 7:
                        printf("Executing stat system call...\n");
                        struct stat st;
                        if (stat("sample.txt", &st) == 0) {
                            printf("File Size: %lld bytes\n", (long long)st.st_size);
                            printf("File Permissions: %o\n", st.st_mode & 0777);
                        } else {
                            printf("Error getting file information.\n");
                        }
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;
        
            case 3: // Communication System Calls
                printf("1. pipe\n");
                printf("2. fifo\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing pipe system call...\n");
                        int pipe_fd[2];
                        if (pipe(pipe_fd) == 0) {
                            printf("Pipe created.\n");
                            close(pipe_fd[0]);
                            close(pipe_fd[1]);
                        } else {
                            printf("Error creating pipe.\n");
                        }
                        break;
                    case 2:
                        printf("Executing fifo system call...\n");
                        mkfifo("myfifo", 0666);
                        printf("FIFO created.\n");
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 4: // Information Related System Calls
                printf("Executing information related system call...\n");
                printf("Current User: %s\n", getenv("USER"));
                system("date");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
                break;
        }

        printf("Press Enter to continue...");
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for user to press Enter
    }

return 0;
} */



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    while (1) {
        system("clear");
        printf("Lab 4: System Call Demonstration\n");
        printf("1. Process Related System Calls\n");
        printf("2. File Related System Calls\n");
        printf("3. Communication System Calls\n");
        printf("4. Information Related System Calls\n");
        printf("5. Exit\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Process Related System Calls
                printf("1. fork\n");
                printf("2. exit\n");
                printf("3. wait\n");

                int sub_choice;
                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing fork system call...\n\n");
                        pid_t child_pid = fork();
                        if (child_pid == 0) {
                            printf("This is the child process.\n");
                        } else if (child_pid > 0) {
                            printf("This is the parent process. Child Process ID: %d\n", child_pid);
                        } else {
                            printf("Fork failed.\n");
                        }
                        break;
                    case 2:
                        printf("Executing exit SysCall...\n");
                        exit(0);
                        break;
                    case 3:
                        printf("Executing wait SysCall...\n");
                        sleep(4);
                        wait(NULL);
                        printf("Child process Completed.\n");
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 2: // File Related System Calls
                printf("1. open\n");
                printf("2. read\n");
                printf("3. write\n");
                printf("4. close\n");
                printf("5. link\n");
                printf("6. unlink\n");
                printf("7. stat\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing open system call...\n");
                        int fd = open("sample.txt", O_CREAT | O_WRONLY, 0644);
                        if (fd != -1) {
                            printf("File opened for writing.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 2:
                        printf("Executing read system call...\n");
                        fd = open("sample.txt", O_RDONLY);
                        if (fd != -1) {
                            char content[100];
                            ssize_t bytesRead = read(fd, content, sizeof(content));
                            if (bytesRead > 0) {
                                content[bytesRead] = '\0';
                                printf("Content read from file: %s\n", content);
                            } else {
                                printf("Error reading file.\n");
                            }
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 3:
                        printf("Executing write system call...\n");
                        fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        if (fd != -1) {
                            write(fd, "Hello, world!", 13);
                            printf("Content written to file.\n");
                            close(fd);
                        } else {
                            printf("Error opening file.\n");
                        }
                        break;
                    case 4:
                        printf("Executing close system call...\n");
                        close(sub_choice); // Replace sub_choice with actual file descriptor
                        printf("File closed.\n");
                        break;
                    case 5:
                        printf("Executing link system call...\n");
                        link("sample.txt", "sample_link.txt");
                        printf("Hard link created.\n");
                        break;
                    case 6:
                        printf("Executing unlink system call...\n");
                        unlink("sample_link.txt");
                        printf("Hard link removed.\n");
                        break;
                    case 7:
                        printf("Executing stat system call...\n");
                        struct stat st;
                        if (stat("sample.txt", &st) == 0) {
                            printf("File Size: %lld bytes\n", (long long)st.st_size);
                            printf("File Permissions: %o\n", st.st_mode & 0777);
                        } else {
                            printf("Error getting file information.\n");
                        }
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;
        
            case 3: // Communication System Calls
                printf("1. pipe\n");
                printf("2. fifo\n");

                printf("Enter sub-choice: ");
                scanf("%d", &sub_choice);

                switch (sub_choice) {
                    case 1:
                        printf("Executing pipe system call...\n");
                         int fd[2] ;
    // fd[0] = read;
    // fd[1] = write
    
    if (pipe(fd) == -1){
        printf("error occured!");
        return -1;
    }

    int id = fork();
    if (id == 0){//child process
        close(fd[0]);
        int x;
        printf("input a number : ");
        scanf("%d", &x);
        write(fd[1] , &x , sizeof(int));
        close(fd[1]);
    }
    else{//parent process
        close(fd[1]);
        int y;
        read(fd[0] , &y , sizeof(int));
        close(fd[0]);
        printf("got from child process %d",y);
        
    }


    return 0;
                        break;
                    case 2:
                        printf("Executing fifo system call...\n");
                        mkfifo("myfifo", 0666);
                        printf("FIFO created.\n");
                        break;
                    default:
                        printf("Invalid sub-choice\n");
                        break;
                }
                break;

            case 4: // Information Related System Calls
                printf("Executing information related system call...\n");
                printf("Current User: %s\n", getenv("USER"));
                system("date");
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice\n");
                break;
        }

        printf("Press Enter to continue...");
        getchar(); // Consume the newline character left in the input buffer
        getchar(); // Wait for user to press Enter
    }

return 0;
}