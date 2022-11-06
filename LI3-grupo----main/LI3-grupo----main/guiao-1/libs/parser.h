#ifndef main_def
#define main_def

#include <glib.h>
#include <stdio.h>
#include <repos.h>
#include <users.h>
#include <commits.h>
#include <validation.h>
#include <stats.h>


	void build_tree(GTree* usr, GH_STATS s);
	void run_parser(GPtrArray *commit_arr_ptr, GHashTable *hash_repos, GH_STATS s, GTree* users_tree,GHashTable *hash_repo_with_bots);


#endif