#ifndef commit_maker
#define commit_maker


//======================Lib's===========================================

#include <validation.h>
#include <glib.h>

//==================END Lib's===========================================


typedef struct gh_commit* GH_COMMIT;



#define MAX_COMMITS 10000000
int commits_ex1();
int commits_ex2();
GH_COMMIT build_commit(char *line);
void print_commit(GH_COMMIT u);
GH_COMMIT build_commit_free(char *buffer);


int get_commit_repo_id(GH_COMMIT commit_data);
int get_commit_author_id(GH_COMMIT commit_data);
int get_commit_commiter_id(GH_COMMIT commit_data);
void get_commit_commit_at(struct tm* data, GH_COMMIT commit_data);
char* get_commit_message(GH_COMMIT commit_data);

#endif
