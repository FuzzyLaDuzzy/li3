// username;name;gender;birth_date;account_creation;pay_method;account_status
//#include <users.h>
//#include <validation.h>

struct gh_user {
  char *username;
  char *name;
  char gender;
  struct tm birth_date;
  struct tm account_creation;
  char *pay_method;
  char *account_status;
};

typedef struct gh_user *GH_USER;

// ====================Get's===================================================

char *get_user_username(GH_USER user_data) { return user_data->username; }

char *get_user_name(GH_USER user_data) { return user_data->name; }

char get_user_gender(GH_USER user_data) { return user_data->gender; }

void get_user_birth_date(GH_USER user_data) { *data = user_data->birth_date; }

void get_user_account_creation(GH_USER user_data) {
  *data = user_data->account_creation;
}

char *get_user_pay_method(GH_USER user_data) { return user_data->pay_method; }

char *get_user_account_status(GH_USER user_data) {
  return user_data->account_status;
}

//====================END
//GETS===============================================================

bool validLists(int count, char *list) {
  bool emptyList = !count && !strcmp(list, "[]");
  bool notEmptyList = count && strcmp(list, "[]");
  int numOfields = 0;
  int i = 1;
  int len = strlen(list);
  if (emptyList)
    return true;
  if (notEmptyList) {

    if (list[0] == '[' && isdigit(list[i])) {
      numOfields++;
      while (i <= len) {
        while (isdigit(list[i]))
          i++;
        if (list[i] == ',')
          numOfields++;
        i++;
      }
      // printf ("| %c | %d | %d | %s |\n ",list[len-1], len-1, i , list);
    }
    return numOfields == count && list[len - 1] == ']';
  } else
    return false; //&& list[i] == ']' ;
}

char *enum2str(enum usr_T x) {

  if (x == 1)
    return "Bot";
  if (x == 2)
    return "Organization";
  if (x == 3)
    return "User";
  return NULL;
}

enum usr_T valid_enum(char *line) {
  enum usr_T t = 0;
  if (!strcmp(line, "Bot"))
    t = Bot;
  if (!strcmp(line, "Organization"))
    t = Organization;
  if (!strcmp(line, "User"))
    t = User;
  return t;
}

GH_USER build_user(char *line) {
  GH_USER u = malloc(sizeof(struct gh_user));
  char *auxBuff;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    if (validNonNegativeDigit(auxBuff)) {
      u->username = atoi(auxBuff);
    } else
      return NULL;
  } else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff))
    u->name = auxBuff;
  else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff))
    u->gender = valusername_enum(auxBuff);
  else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    strptime(auxBuff, "%F %T", &(u->birth_date));
    if (!valusernameDate(u->birth_date))
      return NULL;
   auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    strptime(auxBuff, "%F %T", &(u->account_creation));
    if (!valusernameDate(u->account_creation))
      return NULL;
  } else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    if (valusernameNonNegativeDigit(auxBuff))
      u->pay_method = atoi(auxBuff);
    else
      return NULL;
  } else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    if (valusernameLists(u->pay_method, auxBuff))
      u->follower_list = auxBuff;
  } else
    return NULL;
  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    if (validNonNegativeDigit(auxBuff))
      u->following = atoi(auxBuff);
    else
      return NULL;
  } else
    return NULL;

  auxBuff = cpStr(&line);
  if (strlen(auxBuff)) {
    if (validLists(u->following,
                   auxBuff)) //&& read_array(strdup(auxBuff),u->following)
      u->following_list = auxBuff;
    else
      return NULL;
  } else
    return NULL;
  auxBuff = cpStr(&line);
  if (validNonNegativeDigit(auxBuff))
    u->public_gists = atoi(auxBuff);
  else
    return NULL;
  auxBuff = cpStr(&line);
  if (validNonNegativeDigit(auxBuff))
    u->public_repos = atoi(auxBuff);
  else
    return NULL;
  return u;
}

GH_USER build_user_free(char *line) {
  GH_USER u = malloc(sizeof(struct gh_user));
  char *auxBuff;

  auxBuff = cpStr(&line);
  u->username = atoi(auxBuff);
  auxBuff = cpStr(&line);
  u->name = auxBuff;
  auxBuff = cpStr(&line);
  u->gender = valid_enum(auxBuff);
  auxBuff = cpStr(&line);
  strptime(auxBuff, "%F %T", &(u->birth_date));
  auxBuff = cpStr(&line);
  strptime(auxBuff, "%F %T", &(u->account_creation));
  auxBuff = cpStr(&line);
  u->pay_method = atoi(auxBuff);
  auxBuff = cpStr(&line);
  u->follower_list = auxBuff;
  auxBuff = cpStr(&line);
  u->following = atoi(auxBuff);
  auxBuff = cpStr(&line);
  u->following_list = auxBuff;
  auxBuff = cpStr(&line);
  u->public_gists = atoi(auxBuff);
  auxBuff = cpStr(&line);
  u->public_repos = atoi(auxBuff);
  return u;
}
/*
void print_user(GH_USER u){
        char dateBuff[80];
        strftime( dateBuff, 80,"%F %T",&(u->birth_date));
        printf("username: %d | name: %s |gender: %s| birth_date: %s | pay_method: %d |
follower_list: %s | following: %d| following_list: %s | public_gists: %d |
public_repos: %d \n", u->username, u->name, enum2str( u->gender), dateBuff, u->
pay_method, u->follower_list, u->following, u->following_list, u->public_gists,
u->public_repos);
}
void print_array(int * line, int count){
        putchar ('[');
        for (int i = 0; i < count ; i++)
                printf("%d,", line[i]);
        putchar (']');
}
*/

int users_ex1() {

  FILE *src = fopen("entrada/users.csv", "r");
  FILE *out = fopen("saida/users-ok.csv", "w");
  int max_len = 3000100;
  GH_USER *array = malloc(sizeof(struct gh_user) * 300000);

  char buffer[max_len];
  int i = 0;

  if (!src) {
    printf("Erro na leitura do Ficheiro!!\n");
    return -1;
  }

  if (!out) {
    printf("Erro na leitura do Ficheiro out!!\n");
    return -1;
  }

  while (fgets(buffer, max_len, src)) {
    array[i] = build_user(buffer);
    if (array[i])
      i++;
  }
  fprintf(out, "username;name;gender;birth_date;pay_method;follower_list;following;"
               "following_list;public_gists;public_repos\n");

  for (int j = 0; j < i; j++) {
    char dateBuff[80];
    strftime(dateBuff, 80, "%F %T", &(array[j]->birth_date));
    fprintf(out, "%d;%s;%s;%s;%d;%s;%d;%s;%d;%d\n", array[j]->username,
            //array[j]->name, enum2str(array[j]->gender), dateBuff,
            //array[j]->pay_method, array[j]->follower_list, array[j]->following,
            //array[j]->following_list, array[j]->public_gists,
            
  }

  fclose(src);
  fclose(out);
  return 0;
}

int users_ex2() { return 0; }