#include <validation.h>
#include <repos.h>


struct gh_repo{

		int id;
		int owner_id;
		char *full_name;
		char *license;
		bool has_wiki;
		char *description;
		char *language;
		char *default_branch;
	  struct tm created_at;
	  struct tm updated_at;
		int forks_count;
		int open_issues;
		int stargazers_count;
		int size;

};typedef struct gh_repo* GH_REPO;

//==============Get's===================================================	

int get_repo_id(GH_REPO repo_data){
	return repo_data->id;
}

int get_repo_owner_id(GH_REPO repo_data){
	return repo_data->owner_id;
}

char* get_repo_full_name(GH_REPO repo_data){
	return repo_data->full_name;
}

char* get_repo_license(GH_REPO repo_data){
	return repo_data->license;
}

bool get_repo_has_wiki(GH_REPO repo_data){
	return repo_data->has_wiki;
}

char* get_repo_description(GH_REPO repo_data){
	return repo_data->description;
}

char* get_repo_language(GH_REPO repo_data){
	return repo_data->language;
}

char* get_repo_default_branch(GH_REPO repo_data){
	return repo_data->default_branch;
}

void get_repo_created_at(struct tm* data,GH_REPO repo_data){
	*data = repo_data->created_at;
}

void get_repo_updated_at(struct tm* data,GH_REPO repo_data){
	*data = repo_data->updated_at;
}

int get_repo_forks_count(GH_REPO repo_data){
	return repo_data->forks_count;
}

int get_repo_open_issues(GH_REPO repo_data){
	return repo_data->open_issues;
}

int get_repo_stargazers_count(GH_REPO repo_data){
	return repo_data->stargazers_count;
}

int get_repo_size(GH_REPO repo_data){
	return repo_data->size;
}
//==============END Get's===============================================	

/*
REPO.c
leitura e armazenamento do ficheiro repo
*/

/*
	int atexit(void (*func)(void))
Causes the specified function func to be called when the program terminates normally
*/

/*
Definição da estrutura repo
 - alterar campos numericos  para int ou unsigned int
*/


/*
Cria uma struct repo e aloca memória à mesma
*/	
GH_REPO build_repos(char *buffer){
//ver fiabilidade do atoi e fazer define max_len
	char * auxBuff; 
	GH_REPO r = malloc (sizeof (struct gh_repo));
	
	auxBuff =cpStr(&buffer);
	  if(validNonNegativeDigit(auxBuff)) 
	  	r->id = atoi(auxBuff); 
	  else return NULL;
	auxBuff =cpStr(&buffer);
      if(validNonNegativeDigit(auxBuff)) 
      	r->owner_id = atoi(auxBuff); 
	  else return NULL;
	auxBuff =cpStr(&buffer);
	  if(strlen (auxBuff)) 
      	r->full_name = auxBuff; 
	  else return NULL;
	auxBuff =cpStr(&buffer);
	  if(strlen (auxBuff)) 
      	r->license = auxBuff; 
	  else return NULL;
	auxBuff =cpStr(&buffer);
	  if(strlen (auxBuff)) 
        r-> has_wiki = string2bool(auxBuff); 
	  else return NULL;
        r-> description = cpStr(&buffer);//pode ser campo vazio
	auxBuff =cpStr(&buffer);
	  if(strlen (auxBuff)) 
        r->language = auxBuff; 
	  else return NULL;	
	auxBuff = cpStr(&buffer);
	  if(strlen (auxBuff)) 
        r->default_branch = auxBuff; 
	  else return NULL;
	auxBuff = cpStr(&buffer);
	  strptime (auxBuff, "%F %T", &(r->created_at));
	  if (validDate(r->created_at) == false|| !strlen (auxBuff)) return NULL;
    auxBuff = cpStr(&buffer);
      strptime (auxBuff, "%F %T", &(r->updated_at));
      if (validDate(r->updated_at)==false || !strlen (auxBuff)) return NULL;
	auxBuff = cpStr(&buffer);	
	  if(validNonNegativeDigit(auxBuff)) 
	  r->forks_count = atoi(auxBuff); 
	  else return NULL;
	auxBuff =cpStr(&buffer); 	
	  if(validNonNegativeDigit(auxBuff)) 
      r->open_issues = atoi(auxBuff); 
	  else return NULL;
	auxBuff =cpStr(&buffer); 	
	  if(validNonNegativeDigit(auxBuff)) 
      r->stargazers_count = atoi(auxBuff); 
	  else return NULL;
	auxBuff = cpStr(&buffer); 	
   	  if(validNonNegativeDigit(auxBuff)) 
	  r->size =  atoi(auxBuff); 
      else return NULL;
	return r;
}

GH_REPO build_repos_free(char *buffer){
//ver fiabilidade do atoi e fazer define max_len
	char * auxBuff; 
	GH_REPO r = malloc (sizeof (struct gh_repo));
	
	auxBuff =cpStr(&buffer);
	  	r->id = atoi(auxBuff); 
	auxBuff =cpStr(&buffer);
      	r->owner_id = atoi(auxBuff); 
	auxBuff =cpStr(&buffer);
      	r->full_name = auxBuff; 
	auxBuff =cpStr(&buffer);
      	r->license = auxBuff; 
	auxBuff =cpStr(&buffer);
        r-> has_wiki = string2bool(auxBuff); 
        r-> description = cpStr(&buffer);//pode ser campo vazio
	auxBuff =cpStr(&buffer);
        r->language = auxBuff; 
	auxBuff = cpStr(&buffer);
        r->default_branch = auxBuff; 
	auxBuff = cpStr(&buffer);
	  strptime (auxBuff, "%F %T", &(r->created_at));
    auxBuff = cpStr(&buffer);
      strptime (auxBuff, "%F %T", &(r->updated_at));
	auxBuff = cpStr(&buffer);	
	  r->forks_count = atoi(auxBuff); 
	auxBuff =cpStr(&buffer); 	
      r->open_issues = atoi(auxBuff); 
	auxBuff =cpStr(&buffer);
      r->stargazers_count = atoi(auxBuff); 
	auxBuff = cpStr(&buffer); 	
	  r->size =  atoi(auxBuff); 
	return r;
}

/*
Imprime no ecrã os dados guardados na struct repos
*/
/*
void print_repo(GH_REPO r ){
	char dateBuff[80];
	char dateBuff2[80];
	
		strftime( dateBuff, 80,"%F %T",&(r->created_at));
		strftime( dateBuff2, 80, "%F %T",&(r->updated_at));
		printf("id: %d | owner_id %d |full_name: %s | license: %s | has_wiki:%s  | description %s | language %s | default_branch; %s | created_at %s| updated_at %s | forks_count: %d | open_issues: %d| stargazers_count: %d  size %d |\n",r->id,r->owner_id, r->full_name,r->license, bool2string (r->has_wiki), r->description,r->language,r->default_branch,dateBuff,dateBuff2, r->forks_count, r->open_issues,r->stargazers_count,r->size);
}
*/
/*
void printDate ( GH_REPO r){
	printf("%d\n", r->created_at.tm_year );
	printf("%d\n", r->created_at.tm_mday);
}
*/
int  repos_ex1()
{
	
	FILE *f = fopen ("entrada/repos.csv", "r");
    FILE *out = fopen ("saida/repos-ok.csv", "w");
	int max_len =128000;
	GH_REPO *array = malloc(sizeof(struct gh_repo)*10000100);
	char buff [max_len];
	int i = 0;
	char* buffer= buff;
	GH_REPO aux_build = NULL;
	
	if (f == NULL){
		printf("Erro na abertura!!\n");
		return -1;
	}
	while (fgets(buff, max_len, f)){
		
		aux_build = build_repos(buffer); 

		if(aux_build) array[i++] = aux_build;
	}
		fprintf(out,"id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");

		for (int j = 0; j < i; j++){
	//		print_repo (array[j]);
		char dateBuff[1000];
		char dateBuff2[1000];
	
		strftime( dateBuff, 1000,"%F %T",&(array[j]->created_at));
		strftime( dateBuff2, 1000, "%F %T",&(array[j]->updated_at));
		
		fprintf(out,"%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",array[j]->id,array[j]->owner_id, array[j]->full_name,array[j]->license, bool2string (array[j]->has_wiki), array[j]->description,array[j]->language,array[j]->default_branch,dateBuff,dateBuff2, array[j]->forks_count, array[j]->open_issues,array[j]->stargazers_count,array[j]->size);
	}

	fclose(f);
	fclose(out);
	
	return 0;
}