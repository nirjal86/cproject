#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSWORDS 100
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64

typedef struct {
    char passwords[MAX_PASSWORDS][MAX_PASSWORD_LENGTH];
    int count;
} PasswordList;

void add_password(PasswordList *list, const char *password) {
    if (list->count >= MAX_PASSWORDS) {
        printf("Error: Maximum number of passwords reached.\n");
        return;
    }
    strncpy(list->passwords[list->count], password, MAX_PASSWORD_LENGTH);
    list->count++;
}

int is_unique(PasswordList *list, const char *password) {
    for (int i = 0; i < list->count; i++) {
        if (strcmp(list->passwords[i], password) == 0) {
            return 0;
        }
    }
    return 1;
}

int check_password_strength(const char *password) {
    int has_lowercase = 0;
    int has_uppercase = 0;
    int has_digit = 0;
    int has_special = 0;
    int length = strlen(password);

    if (length < MIN_PASSWORD_LENGTH) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (islower(password[i])) {
            has_lowercase = 1;
        } else if (isupper(password[i])) {
            has_uppercase = 1;
        } else if (isdigit(password[i])) {
            has_digit = 1;
        } else {
            has_special = 1;
        }
    }

    if (has_lowercase && has_uppercase && has_digit && has_special) {
        return 1;
    }

    return 0;
}

int main() {
    PasswordList list;
    list.count = 0;

    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        printf("Enter a password: ");
        fgets(password, MAX_PASSWORD_LENGTH, stdin);
        password[strcspn(password, "\n")] = '\0';

        if (!check_password_strength(password)) {
            printf("Error: Password is not strong enough.\n");
            continue;
        }

        if (!is_unique(&list, password)) {
            printf("Error: Password is not unique.\n");
            continue;
        }

        add_password(&list, password);
        printf("Password added successfully.\n");
    }

    return 0;
}