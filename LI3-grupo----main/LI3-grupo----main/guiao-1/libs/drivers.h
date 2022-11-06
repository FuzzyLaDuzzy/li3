#ifndef repos_maker
#define repos_maker
#include <stdbool.h>
#include <time.h>
#include <validation.h>

	typedef struct gh_repo* GH_REPO;

int repos_ex1();
int repos_ex2();
GH_REPO build_repos(char *line);
void print_repos(GH_REPO u);
GH_REPO build_repos_free(char *buffer);


int get_repo_id(GH_REPO repo_data);
int get_repo_owner_id(GH_REPO repo_data);
char* get_repo_full_name(GH_REPO repo_data);
char* get_repo_license(GH_REPO repo_data);
bool get_repo_has_wiki(GH_REPO repo_data);
char* get_repo_description(GH_REPO repo_data);
char* get_repo_language(GH_REPO repo_data);
char* get_repo_default_branch(GH_REPO repo_data);
void get_repo_created_at(struct tm* data,GH_REPO repo_data);
void get_repo_updated_at(struct tm* data,GH_REPO repo_data);
int get_repo_forks_count(GH_REPO repo_data);
int get_repo_open_issues(GH_REPO repo_data);
int get_repo_stargazers_count(GH_REPO repo_data);
int get_repo_size(GH_REPO repo_data);

#endif