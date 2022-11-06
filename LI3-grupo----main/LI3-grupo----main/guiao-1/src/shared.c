#include <shared.h>
#include <rides.h>
#include <users.h>
#include <drivers.h>
#include <time.h>

	void run_shared(){

//=================================================Files========================================================================

		char *link_users = "saida/users-ok.csv";
		char *link_rides = "saida/rides-ok.csv";
		char *link_drivers = "saida/drivers-ok.csv";

		FILE *origem_users = fopen(link_users,"r");
		FILE *origem_rides = fopen(link_rides,"r");
		FILE *origem_drivers = fopen(link_drivers,"r");

		char *out_users = "saida/users-final.csv";
		char *out_rides = "saida/rides-final.csv";
		char *out_drivers = "saida/drivers-final.csv";

		FILE *output_users = fopen(out_users,"w");
		FILE *output_rides = fopen(out_rides,"w");
		FILE *output_drivers = fopen(out_drivers,"w");


		if (!origem_users) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_users);
		if (!origem_rides) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_rides);
		if (!origem_drivers) printf("Erro na leitura do Ficheiro!! : (%s)\n",link_drivers);

		if (!output_users) printf("Erro na criação do Ficheiro!! : (%s)\n",out_users);
		if (!output_rides) printf("Erro na criação do Ficheiro!! : (%s)\n",out_rides);
		if (!output_drivers) printf("Erro na criação do Ficheiro!! : (%s)\n",out_drivers);



//==================================================HASH_TABLES=================================================================


		GHashTable *hash_table_users_by_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
		GHashTable *hash_table_rides_by_repo_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);
		GHashTable *hash_table_drivers_by_repo_id = g_hash_table_new_full(g_direct_hash,g_direct_equal,NULL,NULL);

		fscanf(origem_users, "%*[^\n]\n");	//Descarta primeira linha do ficheiro
		fscanf(origem_rides, "%*[^\n]\n");	//Descarta primeira linha do ficheiro
		fscanf(origem_drivers, "%*[^\n]\n");	//Descarta primeira linha do ficheiro

		send_to_hash_table_users(origem_users,hash_table_users_by_id); // Cria hash table com entradas do ficheiro origem
		send_to_hash_table_rides(origem_rides,hash_table_commits_by_rides_id); // Cria hash table com entradas do ficheiro origem
		send_to_hash_table_drivers(origem_drivers,hash_table_repos_by_drivers_id); // Cria hash table com entradas do ficheiro origem

		/*
		printf("Há %d entradas na hash_table_users_by_id!! \n" , g_hash_table_size(hash_table_users_by_id));
		printf("Há %d entradas na hash_table_commits_by_repo_id!! \n" , g_hash_table_size(hash_table_commits_by_repo_id));
		printf("Há %d entradas na hash_table_repos_by_id!! \n" , g_hash_table_size(hash_table_repos_by_repo_id));
		*/


//===============================================LOOKUP'S & ESCRITA EM FILE=====================================================		

		void print_user_file(gpointer key, gpointer value, gpointer userdata)
		{
  			GH_USER user = value;
  			struct tm data;

  			get_user_created_at(&data,user);

  			char dateBuff[80];
			strftime(dateBuff, 80,"%F %T",&data);
     		
  			if(user)

    			fprintf(output_users,"%d;%s;%d;%s;%d;%s;%d;%s;%d\n",get_user_id(user),get_user_login(user), 
				get_user_type(user), dateBuff, get_user_followers(user),get_user_followers_list(user), 
				get_user_following(user),get_user_following_list(user), get_user_public_repos(user));
  			

		}

		fprintf(output_users,"username;name;gender;birth_date;account_creation;pay_method;account_status\n");
		g_hash_table_foreach(hash_table_users_by_id, print_user_file, NULL);


		//==============================================================================================================================	

        // optamizar para rides
		void print_commit_file(gpointer key, gpointer value, gpointer userdata)
		{
  			GH_COMMIT commit = value;
  			struct tm data;

  			get_commit_commit_at(&data,commit);

  			char dateBuff[80];
        	strftime(dateBuff, 80,"%F %T",&data);

  			if(commit && g_hash_table_lookup(hash_table_users_by_id,GINT_TO_POINTER(get_commit_author_id(commit))) != NULL
  					  && g_hash_table_lookup(hash_table_users_by_id,GINT_TO_POINTER(get_commit_commiter_id(commit)))!= NULL){

    			char dateBuff[80];
				
    			get_commit_commit_at(&data,commit);	

				strftime(dateBuff, 80,"%F %T",&data);

				fprintf(output_commits,"%d;%d;%d;%s;%s\n",get_commit_repo_id(commit),get_commit_author_id(commit),get_commit_commiter_id(commit),dateBuff,get_commit_message(commit));
			}

		}

		fprintf(output_commits,"repo_id;author_id;commiter_id;commit_at;message\n");
		g_hash_table_foreach(hash_table_commits_by_repo_id, print_commit_file, NULL);


		//==============================================================================================================================	

        // optamizar para drivers
		void print_repo_file(gpointer key, gpointer value, gpointer userdata)
		{
  			GH_REPO repo = value;
  			struct tm data_created;
  			struct tm data_updated;

  			get_repo_created_at(&data_created,repo);
  			get_repo_updated_at(&data_updated,repo);

  			char dateBuff[80];
        	strftime(dateBuff, 80,"%F %T",&data_created);

  			if(repo && g_hash_table_lookup(hash_table_users_by_id,GINT_TO_POINTER(get_repo_owner_id(repo)))!= NULL
  					&& g_hash_table_lookup(hash_table_commits_by_repo_id,GINT_TO_POINTER(get_repo_id(repo)))!= NULL){

    			char dateBuff[80];
				char dateBuff2[80];
	
				strftime( dateBuff, 80,"%F %T",&data_created);
				strftime( dateBuff2, 80, "%F %T",&data_updated);
				
				fprintf(output_repos,"%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",get_repo_id(repo),get_repo_owner_id(repo), 
					get_repo_full_name(repo),get_repo_license(repo), bool2string (get_repo_has_wiki(repo)), get_repo_description(repo),
					get_repo_language(repo),get_repo_default_branch(repo),dateBuff,dateBuff2, get_repo_forks_count(repo), 
					get_repo_open_issues(repo),get_repo_stargazers_count(repo),get_repo_size(repo));

  			}


		}

		fprintf(output_repos,"id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");
		g_hash_table_foreach(hash_table_repos_by_repo_id, print_repo_file, NULL);



	}

//===================================================HASH_TABLES_FUNCS==========================================================		


	GHashTable *send_to_hash_table_users(FILE *origem, GHashTable *hash_table_users){

		int max_leng = 3000100; //==================================================================== MUDAR!!!
		char buff[max_leng]; //==================================================================== MUDAR!!!

		GH_USER user_buffer;

			while (fgets(buff,max_leng,origem)){

				user_buffer = build_user_free(buff);

				g_hash_table_insert(hash_table_users,GINT_TO_POINTER(get_user_id(user_buffer)),user_buffer);



		}

	return hash_table_users;


	}

	GHashTable *send_to_hash_table_rides(FILE *origem, GHashTable *hash_table_riders){

		int max_leng = 3000100; //==================================================================== MUDAR!!!
		char buff[max_leng]; //==================================================================== MUDAR!!!

		GH_COMMIT ride_buffer;


			while (fgets(buff,max_leng,origem)){

				ride_buffer = build_commit_free(buff);

				g_hash_table_insert(hash_table_rides,GINT_TO_POINTER(get_ride_driver_id(ride_buffer)),ride_buffer);
	
		}


	return hash_table_rides;


	}

	GHashTable *send_to_hash_table_drivers(FILE *origem, GHashTable *hash_table_drivers){

		int max_leng = 3000100; //==================================================================== MUDAR!!!
		char buff[max_leng]; //==================================================================== MUDAR!!!

		GH_REPO driver_buffer;


			while (fgets(buff,max_leng,origem)){

				driver_buffer = build_repos_free(buff);

					g_hash_table_insert(hash_table_drivers,GINT_TO_POINTER(get_driver_id(driver_buffer)),driver_buffer);

		}

	return hash_table_drivers;


	}
