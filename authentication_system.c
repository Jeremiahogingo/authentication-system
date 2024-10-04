#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h> 
#define ENTER 13
#define TAB 9
#define BCKSPC 8

struct user {
    char fullname[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
};

void takeinput(char ch[50]) {
    fgets(ch, 50, stdin);
    ch[strlen(ch) - 1] = 0;
}

void generateUsername(char email[50], char username[50]) {
    for (int i = 0; i < strlen(email); i++) {
        if (email[i] == '@') {
            username[i] = '\0';
            break;
        } else {
            username[i] = email[i];
        }
    }
}

void takepassword(char pwd[50]) {
    int i = 0; // Initialize i
    char ch;
    while (1) {
        ch = getch();
        if (ch == ENTER || ch == TAB) {
            pwd[i] = '\0';
            break;
        } else if (ch == BCKSPC) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            pwd[i++] = ch;
            printf("* \b");
        }
    }
}

int main() {
    system("color 0b");

    FILE *fp;
    int opt;
    int userFound = 0;
    char password2[50];
    char username[50], pword[50];
    struct user user;

    printf("\n\t\t\t__________WELCOME TO AUTHENTICATION SYSTEM__________\t\t\t");
    printf("\n\t\t\t\t----------@Jerrylion----------\t\t\t\t");

    printf("\nPlease choose an operation ");
    printf("\n\t1.Sign up ");
    printf("\n\t2.Login ");
    printf("\n\t3.Exit ");
    printf("\nYour choice:\t ");
    scanf("%d", &opt);
    fgetc(stdin);

    switch (opt) {
        case 1:
            system("cls");
            printf("Enter your fullname: ");
            takeinput(user.fullname);
            printf("Enter your email: ");
            takeinput(user.email);
            printf("Enter your contact: ");
            takeinput(user.phone);
            printf("Enter your password: ");
            takepassword(user.password);
            printf("\nConfirm your password: ");
            takepassword(password2);

            if (!strcmp(user.password, password2)) {
                generateUsername(user.email, user.username);
                fp = fopen("users.dat", "a+");
                if (fp == NULL) {
                    printf("\nError opening file!");
                    return 1;
                }
                fwrite(&user, sizeof(struct user), 1, fp);

                if (fwrite != 0) {
                    printf("\nUser registration success, your username is %s", user.username);
                } else {
                    printf("\nSomething went wrong! ");
                }
                fclose(fp);
            } else {
                printf("\nPasswords do not match");
                Beep(750, 300);
            }
            break;

        case 2:
            printf("\nEnter your username: ");
            takeinput(username);
            printf("\nEnter your password: ");
            takepassword(pword);

            fp = fopen("users.dat", "r");
            if (fp == NULL) {
                printf("\nError opening file!");
                return 1;
            }
            while (fread(&user, sizeof(struct user), 1, fp)) {
                if (!strcmp(user.username, username)) {
                    if (!strcmp(user.password, pword)) {
                        system("cls");
                        printf("\n\t\t\tWelcome %s", user.username);
                        printf("\n\n|Full name: %s", user.fullname);
                        printf("\n\n|Email: %s", user.email);
                        printf("\n\n|Username: %s", user.username);
                        printf("\n\n|Contact: %s", user.phone);
                    } else {
                        printf("\n\nInvalid password or username");
                        Beep(800, 300);
                    }
                    userFound = 1;
                    break;
                }
            }
            if (!userFound) {
                printf("\nUser is not registered");
                Beep(800, 300);
            }
            fclose(fp);
            break;

        case 3:
            printf("\n\t\t\tBye Bye .............");
            break;

        default:
            printf("\nInvalid option!");
            break;
    }

    return 0;
}
