#include <validation.h>
#ifndef users_maker
#define users_maker
#include <stdbool.h>
#include <time.h>

enum usr_T {Bot = 1,Organization = 2, User = 3};

typedef struct gh_user* GH_USER;

int users_ex1();
int users_ex2();
GH_USER build_user(char *line);
void print_user(GH_USER u);
GH_USER build_user_free(char *line);


char* get_user_username(GH_USER user_data);
char* get_user_name(GH_USER user_data);
char get_user_gender(GH_USER user_data);
void get_user_birth_date(struct tm* data,GH_USER user_data);
void get_user_account_creation(struct tm* data,GH_USER user_data);
char* get_user_pay_method(GH_USER user_data);
char* get_user_account_status(GH_USER user_data);


#endif