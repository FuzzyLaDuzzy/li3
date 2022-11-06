#include <stdio.h>
#include <math.h>

struct stats_data{

  int total_type_users;
  int total_type_bots;
  int total_type_orgs;
  int total_collaborators;
  int total_repos;
  int total_commits;
  int total_users;
  int total_repos_with_bots;

}; 

	typedef struct stats_data * GH_STATS;

//==============Get's===================================================
/*
Estrutura básica para as estatísticas globais
provavelmente serão incluídos mais dados relevantes para as queries parametrizáveis
(!!!!)INCOMPLETO: Arredondar para %.2f
*/

int get_total_users(GH_STATS s){
	return s->total_users;
}

int get_total_commits(GH_STATS s){
	return s->total_commits;
}

int get_total_repos(GH_STATS s){
	return s->total_repos;
}

 int get_total_type_bots(GH_STATS s){
	return s->total_type_bots;
}

 int get_total_type_users(GH_STATS s){
	return s->total_type_users;
}

 int get_total_type_orgs( GH_STATS s){
	return s->total_type_orgs;
}

float get_avg_collaborators_per_repo (GH_STATS s){
	return s->total_collaborators/s->total_repos; //!!! arrendondar a duas casa decimais 
}

 int get_total_repos_with_bots (GH_STATS s){
	return s->total_repos_with_bots;
}

 float get_avg_commits_per_user (GH_STATS s){
	return s->total_commits/s->total_users;
}

//==============END Get's===============================================



//==============Set's===================================================

void set_total_users(GH_STATS s, int x){
	s->total_users = x;
}

void set_total_commits(GH_STATS s, int x){
	s->total_commits = x;
}

void set_total_repos(GH_STATS s, int x){
	s->total_repos = x;
}

void set_total_type_bots(GH_STATS s, int x){
	s->total_type_bots=x;
}

void set_total_type_users(GH_STATS s, int x){
	s->total_type_users=x;
}

void set_total_type_orgs(GH_STATS s, int x){
	s->total_type_orgs=x;
}

void set_total_repos_with_bots (GH_STATS s, int x){
	s->total_repos_with_bots=x;
}

//==============END Set's===============================================