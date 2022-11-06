#define _GNU_SOURCE

#include <validation.h>
#include <glib.h>
#include <users.h>
#include <time.h>
#include <stats.h>
#include <stdio.h>
#include <stdlib.h>
#include <rides.h>
#include <drivers.h>

struct aux_to_q5
	{
		struct tm* data1;
		struct tm* data2;
		GTree* tree;
		GHashTable* users_ids;
		int *ids;
		int size;

	};typedef struct aux_to_q5* INBODY;

struct aux_to_q7
	{
		struct tm* data1;
		int *ids;
		int size;

	};typedef struct aux_to_q7* INBODY7;


void call_q1(int i,GH_STATS s){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!!\n", i);


	fprintf(output, "BOT: %d\n", get_total_type_bots(s));
	fprintf(output, "ORGANIZATION: %d\n", get_total_type_orgs(s));
	fprintf(output, "USER: %d\n", get_total_type_users(s));

}

void call_q2(int i,GH_STATS s){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!!\n", i);

	fprintf(output, "%.2f\n", (double)get_total_users(s)/(double)get_total_repos(s));
	
}

void call_q3(int i,GH_STATS s,GHashTable *hash_repo_with_bots){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!!\n", i);

	fprintf(output, "%d\n", g_hash_table_size(hash_repo_with_bots));
	
}

void call_q4(int i,GH_STATS s){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!!\n", i);

	fprintf(output, "%.2f\n", (double)get_total_commits(s)/(double)get_total_users(s));
	
}

void aux_q5(gpointer info1,gpointer info2){

		GH_COMMIT a = (GH_COMMIT)info1;
		INBODY data = (INBODY)info2;

		struct tm data_commit;
		get_commit_commit_at(&data_commit,a);

		//int commiter_id_value=get_commit_commiter_id(a);

		if (between_date(data_commit,*data->data1,*data->data2)){

			//printf("%d\n", get_commit_commiter_id(a));
			data->ids[data->size] = get_commit_commiter_id(a);
			data->size++;


			/*
			gpointer *val = g_hash_table_lookup(data->users_ids, &commiter_id_value);
					
			if (val == NULL) {
			
				printf("NOT FOUND\n");
				//g_hash_table_insert(data->users_ids,GINT_TO_POINTER(commiter_id_value),GINT_TO_POINTER(1));
			}
			else {
			   printf("FOUND\n");
			
			}
			*/

		}

}

int largest(int arr[], int n)
		{
		    int i;

		    int max = arr[0];
		    int max_ind=0;
		 
		    for (i = 1; i < n; i++){
		        if (arr[i] > max){
		            max = arr[i];
		        	max_ind=i;
		        }
		    }

		    return max_ind;
		}

void call_q5(int n,struct tm data,struct tm data2,int i,GPtrArray *commit_arr_ptr,GTree* users_tree){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);


	FILE *output = fopen(path,"w");

	//inicialização da estrutura auxiliar
	INBODY a = malloc(sizeof(INBODY));
	a->data1=&data;
	a->data2=&data2;
	a->tree=users_tree;
	a->users_ids = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,NULL);
	a->ids = malloc(sizeof(int)*10000000);
	a->size=0;

	g_ptr_array_foreach(commit_arr_ptr,aux_q5,a);

    int length = a->size;    
         
    int fr[length];  
        
    for(int k = 0; k < length; k++){    
        int count = 1;    
        for(int j = k+1; j < length; j++){    
            if(a->ids[k] == a->ids[j]){    
                count++;   
                fr[j] = -1;    
            }    
        }    
        if(fr[k] != -1)    
            fr[k] = count;    
    }

	while (n>0){

		int aux_ind = largest(fr,length);
		
		fprintf(output,"%d;%s;%d\n",a->ids[aux_ind],get_user_login(g_tree_lookup (users_tree,GINT_TO_POINTER(a->ids[aux_ind]))), fr[aux_ind]);

		fr[aux_ind] = 0;

		n--;

	}

	free(a);
	free(a->ids);

	printf("Comando index %d ==> OK!! | N = %d | data1 : %d-%d-%d | data2 : %d-%d-%d \n",i,n,data.tm_mday,data.tm_mon+1,data.tm_year+1900,data2.tm_mday,data2.tm_mon+1,data2.tm_year+1900);
	
}

void call_q6(int n,char* lang,int i){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	//FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!! | N = %d | lang = %s\n",i,n,lang);
	
}


void aux_q7(gpointer info1,gpointer info2){

		GH_COMMIT a = (GH_COMMIT)info1;
		INBODY7 data = (INBODY7)info2;

		struct tm data_commit;
		get_commit_commit_at(&data_commit,a);

		if (pos_date(data_commit,*data->data1)){

			data->ids[data->size] = get_commit_repo_id(a);
			data->size++;

		}

}


int aux2_q7(gpointer key,gpointer val,gpointer info1){

	int chave = GPOINTER_TO_INT(key);
	//GH_REPO rep = (GH_REPO) val;
	INBODY7 data = (INBODY7)info1;
	int i = 0;

	while(data->ids[i]!=chave && i<data->size) i++;

	if(data->ids[i]==chave) return 1;

	return 0;

}

void aux3_q7(gpointer key,gpointer val,gpointer info1){

	g_hash_table_insert (info1,key,val);

}

void aux4_q7(gpointer key,gpointer val,gpointer info1){

	int a = GPOINTER_TO_INT(key);

	fprintf(info1, "%d;%s\n",a,get_repo_description(val));

}

void call_q7(struct tm data,int i,GPtrArray *commit_arr_ptr,GHashTable *repos_hash){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	FILE *output = fopen(path,"w");


	INBODY7 a = malloc(sizeof(INBODY7));
	a->data1=&data;
	a->ids = malloc(sizeof(int)*10000000);
	a->size=0;

	g_ptr_array_foreach(commit_arr_ptr,aux_q7,a);

	GHashTable *clone = g_hash_table_new(NULL,NULL);

	g_hash_table_foreach (repos_hash,aux3_q7,clone);

	g_hash_table_foreach_remove(clone,aux2_q7,a);

	g_hash_table_foreach (clone,aux4_q7,output);

	printf("Comando index %d ==> OK!! | data : %d-%d-%d\n",i,data.tm_mday,data.tm_mon+1,data.tm_year+1900);

}

void call_q8(int n, struct tm data, int i){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	//FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!! | data : %d-%d-%d\n",i,data.tm_mday,data.tm_mon+1,data.tm_year+1900);
	
}

void call_q9(int n,int i){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	//FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!!\n", i);
	
}

void call_q10(int n,int i){

	char path[48];
	snprintf(path, 48, "saida/command%d_output.txt", i);

	//FILE *output = fopen(path,"w");

	printf("Comando index %d ==> OK!! | N=%d\n",i,n);
	
}

int run_queries(const char* path,GH_STATS s,GPtrArray *commit_arr_ptr, GHashTable *hash_repos_by_repo_id,GTree* users_tree,GHashTable *hash_repo_with_bots){
	
	FILE *origem = fopen(path,"r");

	int max_leng = 3000100; //==================================================================== MUDAR!!!
	char buff[max_leng]; //==================================================================== MUDAR!!!
	char* aux_buff = buff;
	int i=0,n=0;
	struct tm data = {0};
	struct tm data2 = {0};

	while (fgets(buff,max_leng,origem)){
		i++;
		switch(buff[0]){

			case '1':
		
				if(buff[1] == '0'){

					aux_buff = buff;
					cpStr_space(&aux_buff);

					call_q10(atoi(cpStr_space(&aux_buff)),i);
				
				}

				else{

					if(buff[1] == '\n'){
				
					call_q1(i,s);
					
					}
					
			
				}

			break;

			case '2':

				call_q2(i,s);

			break;

			case '3':

				call_q3(i,s,hash_repo_with_bots);

			break;

			case '4':
			
				call_q4(i,s);

			break;

			case '5':
				
					aux_buff = buff;
					cpStr_space(&aux_buff);

					n = atoi(cpStr_space(&aux_buff));
					
					strptime(cpStr_space(&aux_buff), "%Y-%m-%d", &data);
					strptime(cpStr_space(&aux_buff), "%Y-%m-%d", &data2);

					call_q5(n,data,data2,i,commit_arr_ptr,users_tree);

			break;

			case '6':
				
				aux_buff = buff;
				cpStr_space(&aux_buff);

					n = atoi(cpStr_space(&aux_buff));
					char *lang = cpStr_space(&aux_buff);

					call_q6(n,lang,i);

			break;

			case '7':
				
					aux_buff = buff;
					cpStr_space(&aux_buff);
					
					strptime(cpStr_space(&aux_buff), "%Y-%m-%d", &data);

					call_q7(data,i,commit_arr_ptr,hash_repos_by_repo_id);

			break;

			case '8':
				
					aux_buff = buff;
					cpStr_space(&aux_buff);

					n = atoi(cpStr_space(&aux_buff));
					
					strptime(cpStr_space(&aux_buff), "%Y-%m-%d", &data);

					call_q8(n,data,i);


			break;

			case '9':
				
					aux_buff = buff;
					cpStr_space(&aux_buff);

					n = atoi(cpStr_space(&aux_buff));

					call_q9(n,i);



			break;

			default:


			break;


		}

	}

	return 1;

}