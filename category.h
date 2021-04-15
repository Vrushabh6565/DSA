#include "ftree.h"
#include <sys/stat.h>
void searchbypart(node root, char *filename, int size1, int size2, int Case);
void file_path(node root);
void next_dir(node root);
void time_info(node root);
void permission(node root);
void print_ftree(node root,int size1, int size2, int Case);
void txt(node root, int);
void pdf(node root, int);
void php(node root, int);
void docx(node root, int);
void pptx(node root, int);
void xls(node root, int);
void audio(node root, int);
void video(node root, int);
void img(node root, int);
void links(node root, int);
