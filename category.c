#include "category.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <windows.h>
void searchbypart(node root, char *filename, int size1, int size2, int Case) {          //search a file by its partial name
    if(!root)
        return;
    searchbypart(root->directory, filename,size1, size2, Case);                     //recursive call for directory
    searchbypart(root->next, filename,size1, size2, Case);                             //recursive call for files in same directory
    char *str = strstr(root->fname, filename);
    if(str != NULL) {                                                               //print by respective case
        if(root != NULL && Case == 0) {
             file_path(root);
            printf("\n");
        }
        if(root != NULL && Case == 1) {
            printf("| %d MB |\t", root->size);
            file_path(root);
            printf("\n");
        }
        if(root != NULL && Case == 11 && root->size >= size1 && root->size <= size2) {
            printf("| %d  MB|\t", root->size);
            file_path(root);
            printf("\n");
        }
        if(root != NULL && Case == 2) {
            time_info(root);
             file_path(root);
            printf("\n");
        }
        if(root != NULL && Case == 3) {
            permission(root);
             file_path(root);
            printf("\n");
        }
        if(Case == 10) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 100 && root->size >= size1 && root->size <= size2) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
    }
    return;
}

void file_path(node root) {                 //to print file path from given node
    printf("D:");
    next_dir(root);
    return;
}

void next_dir(node root) {                  //recursive function to print file path used by file_path
    if(root->parent != NULL)
        next_dir(root->parent);
    printf("/%s", root->fname);
    return;
}


void time_info(node root) {                 //print time information created,last modified, last accessed
        printf("M:%s | A:%s | C:%s |\t", root->mtime, root->atime, root->ctime);
    return;
}

void permission(node root) {                                    //printing permission of files format directory|user(rd,wr,exe)|grp(rd,wr,exe)|other(rd,wr,exe)
    (root->permissions & S_IFDIR)?printf("d "):printf("- ");
    (root->permissions & S_IRUSR)?printf("r"):printf("-");
    (root->permissions & S_IWUSR)?printf("w"):printf("-");
    (root->permissions & S_IXUSR)?printf("x "):printf("- ");
    (root->permissions & S_IRUSR)?printf("r"):printf("-");      //here for windows S_IRGRP(works in ubantu) not work which is used for group permissions so used S_IRUSER
    (root->permissions & S_IWUSR)?printf("w"):printf("-");
    (root->permissions & S_IXUSR)?printf("x "):printf("- ");
    (root->permissions & S_IREAD)?printf("r"):printf("-");      //here for windows S_IROTH(works in ubantu) not work which is used for others permissions so used S_IREAD
    (root->permissions &S_IWRITE)?printf("w"):printf("-");
    (root->permissions & S_IEXEC)?printf("x\t"):printf("-\t");
    return;
}

void print_ftree(node root, int size1, int size2, int Case) {       //print all files according to given filters
	// To check if its a file
	if (root->directory == NULL){                                   //if file is not directory i.e regular file
        if(Case == 4) {
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 44 && root->size >= size1 && root->size <= size2) {
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 5) {
            time_info(root);
            file_path(root);
            printf("\n");
        }
        if(Case == 6) {
            permission(root);
            file_path(root);
            printf("\n");
        }
        if(Case == 7) {
            time_info(root);
             printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 77 && root->size >= size1 && root->size <= size2) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 8) {
            permission(root);
            time_info(root);
            file_path(root);
            printf("\n");
        }
	}
	else {                                                          //if file is directory then print file and call function recurrsively
        if(Case == 4) {
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 44 && root->size >= size1 && root->size <= size2) {
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 5) {
            time_info(root);
            file_path(root);
            printf("\n");
        }
        if(Case == 6) {
            permission(root);
            file_path(root);
            printf("\n");
        }
        if(Case == 7) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 77 && root->size >= size1 && root->size <= size2) {
            time_info(root);
            printf("| %d  MB |\n",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 8) {
            permission(root);
            time_info(root);
            file_path(root);
            printf("\n");
        }
		print_ftree(root->directory, size1, size2, Case);           //recursive call
    }
	// To print the next file
	if (root->next != NULL) {
		print_ftree(root->next, size1, size2, Case);                //if regular file then print next file
	}
}


void txt(node root, int Case) {                     //print text,php,pdf,docx,pptxxls files
    searchbypart(root, ".txt", 0, 0, Case);
    return;
}

void php(node root, int Case) {
    searchbypart(root, ".php",0,0, Case);
    return;
}

void pdf(node root, int Case) {
    searchbypart(root, ".pdf",0,0, Case);
    return;
}

void docx(node root, int Case) {
    searchbypart(root, ".docx",0,0, Case);
    return;
}
void pptx(node root, int Case) {
    searchbypart(root, ".pptx",0,0,Case);
    return;
}
void xls(node root, int Case) {
    searchbypart(root, ".xls",0,0, Case);
    searchbypart(root, ".xlsx",0,0, Case);
    return;
}

void audio(node root, int Case) {               //print audio file formats
    searchbypart(root, ".mp3",0,0, Case);
    searchbypart(root, ".3gp",0,0, Case);
    searchbypart(root, ".aac",0,0, Case);
    searchbypart(root, ".m4a",0,0, Case);
    searchbypart(root, ".flac",0,0, Case);
    searchbypart(root, ".wav",0,0, Case);
    searchbypart(root, ".wma",0,0, Case);
}

void video(node root, int Case) {           //print video file formats
    searchbypart(root, ".mp4",0,0, Case);
    searchbypart(root, ".mov",0,0, Case);
    searchbypart(root, ".wmv",0,0, Case);
    searchbypart(root, ".flv",0,0, Case);
    searchbypart(root, ".avi",0,0, Case);
    searchbypart(root, ".mkv",0,0, Case);

}


void img(node root, int Case) {                 //print img file formats
    searchbypart(root, ".apng",0,0, Case);
    searchbypart(root, ".avif",0,0, Case);
    searchbypart(root, ".gif",0,0, Case);
    searchbypart(root, ".jpg",0,0, Case);
    searchbypart(root, ".jpeg",0,0, Case);
    searchbypart(root, ".png",0,0, Case);
    searchbypart(root, ".svg",0,0, Case);
    searchbypart(root, ".webp",0,0, Case);
    searchbypart(root, ".bmp",0,0, Case);
    searchbypart(root, ".ico",0,0, Case);
}

void links(node root, int Case) {           //print file links
	if (root->directory == NULL){
        if(root->link)
            file_path(root);
	}
	else {
		print_ftree(root->directory, 0, 0, Case);
        if(root->link)
            file_path(root);
		}
	// To print the next file
	if (root->next != NULL) {
		print_ftree(root->next, 0, 0, Case);
		if(root->link)
            file_path(root);
	}
}
