#include <sys/stat.h>
#include "category.h"

char *readword(char *command, int i);
int getbit(int size, int time, int perm, int m, int l, int d, int pname, int name);
void searchbyname(node root, char *filename, int size1, int size2, int Case);
void category(node root, char filename);
void delete_tree(node root);
void help();
