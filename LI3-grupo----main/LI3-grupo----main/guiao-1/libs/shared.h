#ifndef main_def
#define main_def

#include <glib.h>
#include <stdio.h>
#include <rides.h>
#include <users.h>
#include <drivers.h>
#include <validation.h>


	GHashTable *send_to_hash_table_users(FILE *origem, GHashTable *hash_table_users);
	GHashTable *send_to_hash_table_rides(FILE *origem, GHashTable *hash_table_rides);
	GHashTable *send_to_hash_table_drivers(FILE *origem, GHashTable *hash_table_drivers);
	void run_shared();

#endif