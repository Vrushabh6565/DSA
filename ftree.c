#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <windows.h>
#define S_ISLNK(K) 0
#include <time.h>
#include "ftree.h"


//create path from file name (required for search)
char *build_path(const char *root, char *filename) {
	char *path = malloc(strlen(root) + strlen(filename) + 2);
	strcpy(path, root);
	strcat(path, "/");
	strcat(path, filename);
	strcat(path, "\0");
	return path;

}

//find file name from given path
char *get_fname(char *path) {
	char *filename;
	filename = (char*)basename(path);
	return filename;
}

//creates directory tree form given path or file as root node
node generate_ftree(char *fname) {
    struct TreeNode *root = (struct TreeNode*) malloc(sizeof(struct TreeNode));
    struct stat s;
	if (stat(fname, &s) < 0) {
		//printf("stat error\n");
		//exit(0);
	}
	// If fname is a regular file or link
	if (S_ISREG(s.st_mode) || S_ISLNK(s.st_mode)) {
		root->fname = get_fname((char *) fname);
		root->permissions = s.st_mode;
		root->link = S_ISLNK(s.st_mode);
		root->size = s.st_size/1048576;
		root->mtime = (char*)malloc(sizeof(char) * 20);
		root->atime = (char*)malloc(sizeof(char) * 20);
		root->ctime = (char*)malloc(sizeof(char) * 20);
		strftime(root->mtime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_mtime));
		strftime(root->atime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_atime));
		strftime(root->ctime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_ctime));
		root->directory = NULL;
		root->next = NULL;
		root->parent = NULL;
	}
    // fname is a directory
	else {
		DIR *dir;
		struct dirent *direntry;
		struct TreeNode *prev = NULL;
		root->fname = get_fname((char *)fname);
		root->permissions = s.st_mode;
		root->link = S_ISLNK(s.st_mode);
		root->size = s.st_size/1048576;                         //convert size from bytes to MB
		root->mtime = (char*)malloc(sizeof(char) * 20);
		root->atime = (char*)malloc(sizeof(char) * 20);
		root->ctime = (char*)malloc(sizeof(char) * 20);
		strftime(root->mtime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_mtime));
		strftime(root->atime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_atime));
		strftime(root->ctime,20,"%d/%m/%Y %H:%M:%S", localtime(&s.st_ctime));
		root->directory = NULL;
		root->next = NULL;
		root->parent = NULL;
		dir = opendir(fname);
		if (dir == NULL){
			//printf("Could not open directory");
		}
		while ((direntry = readdir(dir)) != NULL){
			if ((*direntry).d_name[0] != '.') {                     //here we take care of first two files like '.' and '..'
				struct TreeNode *curr = (struct TreeNode*) malloc(sizeof(struct TreeNode));
				char *path = build_path(fname, (*direntry).d_name);
				curr = generate_ftree(path);
				//printf("%s\n",curr->fname);
				// In the first call, there is no previous so we set one
				if (prev == NULL) {
					prev = curr;
					curr->parent = root;
					//printf("*** %s ****\n",prev->fname);
				}
                else {
				// After the first call, we move the pointer to create a LinkedList
					prev->next = curr;
					prev = prev->next;
					curr->parent = root;
				}
				// In the first call, the root's contents is null so we point the first directory entry to it.
				if (root->directory == NULL) {
					root->directory = prev;
					curr->parent = root;
                    //printf("-----%s----\n", root->directory->fname);
				}
			}
		}
		closedir(dir);                          //closed directory
	}
	return root;
}

