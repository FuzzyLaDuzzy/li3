//==================OUR Lib's===========================================
#include <validation.h>
#include <commits.h>


struct gh_commit{

	int repo_id;
	int author_id;
	int commiter_id;
	struct tm commit_at;
	char *message;

};typedef struct gh_commit* GH_COMMIT;



//==============END OUR Lib's===========================================


//==============Get's===================================================	

int get_commit_repo_id(GH_COMMIT commit_data){
	return commit_data->repo_id;
}

int get_commit_author_id(GH_COMMIT commit_data){
	return commit_data->author_id;
}

int get_commit_commiter_id(GH_COMMIT commit_data){
	return commit_data->commiter_id;
}

void get_commit_commit_at(struct tm* data, GH_COMMIT commit_data){

	*data = commit_data->commit_at;

}

char* get_commit_message(GH_COMMIT commit_data){
	return commit_data->message;
}

//==============END Get's===============================================	

/*
//==============Set's===================================================
void set_commit_repo_id(GH_COMMIT data,int repo_id){
	data->repo_id = repo_id;
}
void set_commit_author_id(GH_COMMIT data, int author_id){
	data->author_id = author_id;
}
void set_commit_commiter_id(GH_COMMIT data, int commiter_id){
	data->commiter_id = commiter_id;
}
void set_commit_commit_at(GH_COMMIT data, struct tm data_rec){
	data->commit_at = data_rec;
}
void set_commit_message(GH_COMMIT data, char* message){
	strcpy(data->message,message);
}
//==============END Set's===============================================
*/

//==================Funções=============================================

	GH_COMMIT build_commit(char *buffer){

		GH_COMMIT c = g_malloc(sizeof(struct gh_commit));
		char *auxBuff = NULL;

		auxBuff = cpStr(&buffer);
      		if(validNonNegativeDigit(auxBuff)) 
      			c->repo_id = atoi(auxBuff); 
	  		else return NULL;

		
		auxBuff = cpStr(&buffer);
      		if(validNonNegativeDigit(auxBuff)) 
      			c->author_id = atoi(auxBuff); 
	  		else return NULL;	
		
		
		auxBuff = cpStr(&buffer);
    		if(validNonNegativeDigit(auxBuff)) 
    		  	c->commiter_id = atoi(auxBuff); 
	 		else return NULL;
	

		auxBuff = cpStr(&buffer);
			strptime(auxBuff, "%F %T", &(c->commit_at));
	  		if (validDate(c->commit_at) == false || !strlen (auxBuff)) return NULL;


		auxBuff = cpStr(&buffer);
      			c->message = auxBuff; 

		return c;
	}

	GH_COMMIT build_commit_free(char *buffer){

		GH_COMMIT c = g_malloc(sizeof(struct gh_commit));
		char *auxBuff = NULL;

		auxBuff = cpStr(&buffer);
      			c->repo_id = atoi(auxBuff); 

		auxBuff = cpStr(&buffer);
      			c->author_id = atoi(auxBuff); 

		auxBuff = cpStr(&buffer);
    		  	c->commiter_id = atoi(auxBuff); 

		auxBuff = cpStr(&buffer);
			strptime(auxBuff, "%F %T", &(c->commit_at));

		auxBuff = cpStr(&buffer);
      			c->message = auxBuff; 

		return c;
	}

//==================Funções=============================================


//==================EX-1 block==========================================

int commits_ex1(){

	char link[40] = "entrada/commits.csv";

	FILE *origem = fopen(link,"r");


	FILE *f = fopen (link, "r");
    FILE *out = fopen ("saida/commits-ok.csv", "w");
	int max_len = 128000;
	GH_COMMIT *array = g_malloc(sizeof(struct gh_commit)*10000100);

	char buff [max_len];
	int i = 0;
	char* buffer= buff;
	GH_COMMIT aux_build = NULL;

	if (origem == NULL){ 

		printf("Erro na leitura do Ficheiro!! : (%s)\n",link);
		return -1;
	
	}

	while (fgets(buff, max_len, f) && i<MAX_COMMITS){
		
		aux_build = build_commit(buffer); 
		if(aux_build) array[i++] = aux_build;
	}
	fprintf(out,"repo_id;author_id;commiter_id;commit_at;message\n");

	for (int j = 0; j < i; j++){

		char dateBuff[80];
	
		strftime( dateBuff, 80,"%F %T",&(array[j]->commit_at));

		fprintf(out,"%d;%d;%d;%s;%s\n",array[j]->repo_id,array[j]->author_id,array[j]->commiter_id,dateBuff,array[j]->message);
	}

	fclose(f);
	fclose(out);

	
	return 0;

}

//==============END EX-1 block==========================================



//==================EX-2 block==========================================

int commits_ex2(){

	char link[30] = "saida/commits-ok.csv";

	FILE *origem = fopen(link,"r");


	FILE *f = fopen (link, "r");
    FILE *out = fopen ("saida/commits-final.csv", "w");
	int max_len =128000;
	GH_COMMIT *array = g_malloc(sizeof(struct gh_commit)*10000100);


	char buff [max_len];
	int i = 0;
	char* buffer = buff;
	GH_COMMIT aux_build = NULL;


	if (origem == NULL){ 

		printf("Erro na leitura do Ficheiro!! : (%s)\n",link);
		return -1;
	
	}

	while (fgets(buff, max_len, f)){
		
		aux_build = build_commit(buffer); 
		if(aux_build) array[i++] = aux_build;
	}


	for (int j = 0; j < i; j++){
	
		char dateBuff[80];
	
		strftime(dateBuff, 80,"%F %T",&(array[j]->commit_at));

		fprintf(out,"%d;%d;%d;%s;%s\n",array[j]->repo_id,array[j]->author_id,array[j]->commiter_id,dateBuff,array[j]->message);
	}

	free(array);
	fclose(f);
	fclose(out);


return 0;
}

//==============END EX-2 block===========================================