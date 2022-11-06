#include <stats.h>
#include <repos.h>
#include <users.h>
#include <commits.h>
#include <time.h>


	void build_tree(GTree* usr, GH_STATS s){
	     
	     int total_users = 0;
	     int t_bots = 0;
	     int t_users = 0;
	     int t_orgs = 0;
	    

		FILE *src = fopen("entrada/users-g2.csv","r");
		int max_len = 100000000;
		char* buffer = malloc (sizeof (char)*max_len);
	    char* aux_buff = NULL;
		if (!src){ 
	        printf("Erro na leitura do Ficheiro!!\n");
		}
		
		fscanf(src, "%*[^\n]\n");

		while (fgets(buffer,max_len,src)){
	  		
	  		aux_buff = cpStr (&buffer);
	  		total_users++;
	  		
	  		GH_USER u = build_valid_user(buffer);
	  		
	  		int type = get_user_type(u); 
	  		if (type == 1) t_bots++;
	  		else if (type == 2) t_orgs++;
	  			 else if (type == 3) t_users++;
	  		
	  		gint* serial = GINT_TO_POINTER(atoi(aux_buff));
	        g_tree_insert (usr, serial, u);
	        //printf("%s\n", aux_buff);
					
		}

	     	set_total_users(s,total_users);  
	        set_total_type_bots(s,t_bots);
	        set_total_type_orgs(s,t_orgs);
	        set_total_type_users(s,t_users);

		fclose(src);
	}

//===================================================LIST_FOR_COMMITS==========================================================

	gint ord_by_data(gconstpointer info1,gconstpointer info2){

		GH_COMMIT a = (GH_COMMIT)info1;
		GH_COMMIT b = (GH_COMMIT)info2;

		struct tm* data1 = malloc(sizeof(struct tm));
		struct tm* data2 = malloc(sizeof(struct tm));

		get_commit_commit_at(data1,a);
		get_commit_commit_at(data2,b);

		return (double) difftime(mktime(data1), mktime(data2));

	}

	void g2_send_to_list_commits(FILE* origem_commits,GPtrArray *commit_arr_ptr,GH_STATS s,GTree* users_tree,GHashTable *hash_repo_with_bots){

		int max_leng = 3000100; //==================================================================== MUDAR!!!
		char buff[max_leng]; //==================================================================== MUDAR!!!
		int total_commits=0;

		GH_COMMIT commit_buffer;

			while (fgets(buff,max_leng,origem_commits)){
				total_commits++;
				commit_buffer = build_commit_free(buff);

				if (get_user_type(g_tree_lookup(users_tree,GINT_TO_POINTER(get_commit_commiter_id(commit_buffer))))==1 || 
					get_user_type(g_tree_lookup(users_tree,GINT_TO_POINTER(get_commit_author_id(commit_buffer))))==1)
				{
					g_hash_table_insert(hash_repo_with_bots,GINT_TO_POINTER(get_commit_repo_id(commit_buffer)),NULL);
				}

				g_ptr_array_add (commit_arr_ptr,commit_buffer);

			}


		set_total_commits(s,total_commits);

	}

//===================================================END_LIST_FOR_COMMITS=======================================================



//===================================================HASH_TABLES_FUNCS==========================================================		


	GHashTable *g2_send_to_hash_table_repos(FILE *origem, GHashTable *hash_table_repos,GH_STATS s,GTree* users_tree){

		int max_leng = 3000100; //==================================================================== MUDAR!!!
		char buff[max_leng]; //==================================================================== MUDAR!!!
		int total_repos=0;

		GH_REPO repo_buffer;


			while (fgets(buff,max_leng,origem)){
				total_repos++;
				repo_buffer = build_repos_free(buff);

					g_hash_table_insert(hash_table_repos,GINT_TO_POINTER(get_repo_id(repo_buffer)),repo_buffer);
		}

		set_total_repos(s,total_repos);

		return hash_table_repos;
	
	}

void run_parser(GPtrArray *commit_arr_ptr, GHashTable *hash_repos, GH_STATS s, GTree* users_tree,GHashTable *hash_repo_with_bots){

//=================================================Files========================================================================

		char *link_users = "entrada/users-g2.csv";
		char *link_commits = "entrada/commits-g2.csv";
		char *link_repos = "entrada/repos-g2.csv";

		FILE *origem_users = fopen(link_users,"r");
		FILE *origem_commits = fopen(link_commits,"r");
		FILE *origem_repos = fopen(link_repos,"r");

		if (!origem_users) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_users);
		if (!origem_commits) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_commits);
		if (!origem_repos) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_repos);


//==================================================HASH_TABLES=================================================================


	//	fscanf(origem_users, "%*[^\n]\n");	//Descarta primeira linha do ficheiro
		fscanf(origem_commits, "%*[^\n]\n");	//Descarta primeira linha do ficheiro
		fscanf(origem_repos, "%*[^\n]\n");	//Descarta primeira linha do ficheiro

	//	g2_send_to_hash_table_users(origem_users,hash_table_users_by_id); // Cria hash table com entradas do ficheiro origem
		//g2_send_to_hash_table_commits(origem_commits,hash_commits,s,users_tree,hash_repo_with_bots); // Cria hash table com entradas do ficheiro origem
		g2_send_to_hash_table_repos(origem_repos,hash_repos,s,users_tree); // Cria hash table com entradas do ficheiro origem
		g2_send_to_list_commits(origem_commits,commit_arr_ptr,s,users_tree,hash_repo_with_bots);

		
	//	printf("Há %d entradas na hash_table_users_by_id!! \n" , g_hash_table_size(hash_table_users_by_id));
	//	printf("Há %d entradas na hash_table_commits_by_repo_id!! \n" , g_hash_table_size(hash_table_commits_by_repo_id));
	//	printf("Há %d entradas na hash_table_repos_by_id!! \n" , g_hash_table_size(hash_table_repos_by_repo_id));
		

}