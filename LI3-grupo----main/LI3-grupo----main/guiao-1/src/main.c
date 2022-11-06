//======================Lib's===========================================
#include <parser.h>
#include <queries.h>
#include <stats.h>
#include <validation.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

//======================Our Lib's=======================================

//remove warning que não conseguimos retirar de outra forma (tentar perceber o porquê)
int run_queries(const char* path,GH_STATS s,GPtrArray *commit_arr_ptr, GHashTable *hash_repos_by_repo_id,GTree* users_tree,GHashTable *hash_repo_with_bots);

//=======================Tree Traversal===================================

gboolean find_all_nodes(gpointer key,gpointer value,gpointer all){
	g_ptr_array_add(all,value);
	return FALSE;
}

gboolean find_all_nodes_keys(gpointer key,gpointer value,gpointer all2){
	g_ptr_array_add(all2,key);

	return FALSE;
}

int cmpfunc (gconstpointer a, gconstpointer b){
    int int_a = GPOINTER_TO_INT (a);
    int int_b = GPOINTER_TO_INT (b);

    return int_a - int_b;
}

//=======================Main Program===================================

int main(int argc, char const *argv[]){

GTimer* all = g_timer_new();
g_timer_start(all);

/*
	GPtrArray *all = g_ptr_array_new();
	GPtrArray *all2 = g_ptr_array_new();
	g_tree_foreach(users_tree,find_all_nodes,all);
	g_tree_foreach(users_tree,find_all_nodes_keys,all2);
	for(int i = 0;(guint)i<all->len;i++){
		GH_USER u = g_ptr_array_index(all,i);
		//printf("%s->", get_user_login(u));
		 
	
		//printf("%d\n",  GPOINTER_TO_INT   (g_ptr_array_index(all2,i)));	
	}*/
	
	if(argc==1){

		printf("Falta de Argumento (Path para ficheiro queries)\n");
		return -1;

	}

	else {

		const char* path = argv[1];

		FILE *origem_queries = fopen(path,"r");
		
		if (!origem_queries){
			printf("Erro na leitura do Ficheiro!! : (%s)\n",path);
			return -1;
		}

		GH_STATS s = malloc(sizeof(GH_STATS));

		//user_tree
		GTree* users_tree = g_tree_new(cmpfunc);
    	build_tree(users_tree,s);
		
		//bot repo_hash
		GHashTable *hash_repo_with_bots = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

		//commit_list_by_data
		//GList *commit_list = NULL;
		GPtrArray *commit_arr_ptr = g_ptr_array_new();

		//hash's
    	//GHashTable *hash_table_commits_by_repo_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
		GHashTable *hash_table_repos_by_repo_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);


		//main parser
		run_parser(commit_arr_ptr,hash_table_repos_by_repo_id,s,users_tree,hash_repo_with_bots);


    	//main queries
		if (validate_querie_file(path)) run_queries(path,s,commit_arr_ptr,hash_table_repos_by_repo_id,users_tree,hash_repo_with_bots);
		
		else {

			printf("Ficheiro de Queries não válido\n");
			printf("Não serão gerados quaisquer resultados!\n");
			return -1;

		}


	free(s);
	g_tree_destroy (users_tree);
	g_hash_table_destroy (hash_repo_with_bots);
	g_ptr_array_free(commit_arr_ptr,TRUE);
	g_hash_table_destroy (hash_table_repos_by_repo_id);


	}


	g_timer_stop(all);
	printf("Tempo decorrido desde o inicio do Programa: %f\n", g_timer_elapsed(all,0));

	return 0;

}

//===================END Main Program===================================
