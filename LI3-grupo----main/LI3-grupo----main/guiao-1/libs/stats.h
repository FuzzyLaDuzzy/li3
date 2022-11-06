#include <stdio.h>
#include <math.h>
#ifndef stats
#define stats

typedef struct stats_data * GH_STATS;

//==============Get's===================================================
/*
Estrutura básica para as estatísticas globais
provavelmente serão incluídos mais dados relevantes para as queries parametrizáveis
(!!!!)INCOMPLETO: Arredondar para %.2f
*/
int get_total_users(GH_STATS s);
int get_total_commits(GH_STATS s);
int get_total_repos(GH_STATS s);
int get_total_type_bots(GH_STATS s);
int get_total_type_users(GH_STATS s);
int get_total_type_orgs( GH_STATS s);
int get_avg_collaborators_per_repo (GH_STATS s);
int get_total_repos_with_bots (GH_STATS s);
int get_avg_commits_per_user (GH_STATS s);

//==============END Get's===============================================
//==============Set's===================================================

void set_total_users(GH_STATS s, int x);
void set_total_commits(GH_STATS s, int x);
void set_total_repos(GH_STATS s, int x);
void set_total_type_bots(GH_STATS s, int x);
void set_total_type_users(GH_STATS s, int x);
void set_total_type_orgs(GH_STATS s, int x);
void set_total_repos_with_bots (GH_STATS s, int x);

//==============END Set's===============================================

#endif