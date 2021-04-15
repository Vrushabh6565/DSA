#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "functions.h"


char *readword(char *command, int i) {              //it provide the flag words in command
    char *word = (char*)calloc(10, '\0');
    int j = 0;
    while(command[i] != '\0' && command[i] != ' ') {
        word[j] = command[i];
        i++;
        j++;
    }
    return word;
}

int getbit(int size, int time, int perm, int m, int l, int d, int pname, int name) {        //it will create the bit pattern
    int bit = 1;
    bit = bit * 10 + size;
    bit = bit * 10 + time;
    bit = bit * 10 + perm;
    bit = bit * 10 + m;
    bit = bit * 10 + l;
    bit = bit * 10 + d;
    bit = bit * 10 + pname;
    bit = bit * 10 + name;
    return bit;
}

void searchbyname(node root, char *filename, int size1, int size2, int Case) {          //search file by its name
    if(!root)
        return;
    searchbyname(root->directory, filename, size1, size2, Case);                           //recurrsive call
    searchbyname(root->next, filename,size1, size2, Case);
    if(strcmp(root->fname, filename) == 0) {
        if(root != NULL && Case == 0) {                                                     //printing files if name found by respective case.
             file_path(root);
             printf("\n");
        }
        if(root != NULL && Case == 1) {
            printf("| %d MB |\t", root->size);
            file_path(root);
            printf("\n");
        }
        if(root != NULL && Case == 11 && root->size >= size1 && root->size <= size2) {
            printf("| %d MB |\t", root->size);
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
        if(Case == 9) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
        if(Case == 99 && root->size >= size1 && root->size <= size2) {
            time_info(root);
            printf("| %d  MB |\t",root->size);
            file_path(root);
            printf("\n");
        }
    }
    return;
}



/*void catagory(node root, char *filename) {
    if(!root)
        return;
    char file_path[100];
    catagory(root->directory, filename);
    catagory(root->next, filename);
    if(strcmp(filename, "docs") == 0)
        if(strstr(root->fname, ".docx") || strstr(root->fname, ".pptx") || strstr(root->fname, ".txt") || strstr(root->fname, ".pdf")) {
            char *str = root->fname;
            if(str != NULL) {
                while(root != NULL) {
                    printf("%s/", root->fname);
                    root = root->parent;
                }
                printf("Users/C\n");
            }
        }
    return;
}*/


void category(node root, char filename) {       //printing files category wise
    if(!root)
        return;
    /*
    d = docs
    l = links
    m = media
    */
    if(filename == 'd') {
        printf("\n\n~~~pdf format~~~\n");
        pdf(root, 0);
        printf("\n\n~~~php format~~~\n");
        php(root, 0);
        printf("\n\n~~~text format~~~\n");
        txt(root, 0);
        printf("\n\n~~~word format~~~\n");
        docx(root, 0);
        printf("\n\n~~~ppt format~~~\n");
        pptx(root, 0);
        printf("\n\n~~~excel format~~~\n");
        xls(root, 0);

    }
    else if(filename == 'm') {
        printf("\n\n~~~IMAGES~~~\n");
        img(root, 0);
        printf("\n\n~~~AUDIO~~~\n");
        audio(root, 0);
        printf("\n\n~~~VIDEO~~~\n");
        video(root, 0);
    }

    else if(filename == 'l') {
        printf("~~~LINKS~~~\n\n");
        links(root, 0);
    }
    return;
}

void delete_tree(node root) {           // if -exit flag used then free each node and then return
	if (root->directory == NULL){
		free(root);
	}
	else {
		delete_tree(root->directory);
		free(root);
		}
	if (root->next != NULL) {
		delete_tree(root->next);
		free(root);
	}
}


void help() {
    printf("----------------------flags-----------------------\n");
    printf("FLAG\t\tUSES\n\n");
    printf("-name        used to find files by its name.\n");
    printf("-pname       used to find files by its partial name.\n");
    printf("-type d      used to find doc files.\n");
    printf("-type l      used to find file links.\n");
    printf("-type m      used to find media files.\n");
    printf("-perm        used to get permissions of file.\n");
    printf("-time        used to get mtime,atime,ctime of file.\n");
    printf("-size        used to get file with size(in MB)\n");
    printf("-exit        used to get out of find command\n\n\n");
    printf("----------------------flag combinations-----------------------\n");
    printf("words in rounded brackets are optional\n");
    printf("-name filename                   Case 0       print all files with name filename\n");
    printf("-pname str                       Case 0       print all files containing str in filename\n");
    printf("-type d                          Case -       used to find doc files.\n");
    printf("-type l                          Case -       used to find file links.\n");
    printf("-type m                          Case -       used to find media files.\n");
    printf("-perm                            Case 6       print all files with permissions\n");
    printf("-perm -pname str                 Case 3       print all files having str in filename with permissions\n");
    printf("-perm -name str                  Case 3       print all files having str as filename with permissions\n");
    printf("-time                            Case 5       print all files with time information\n");
    printf("-time -pname str                 Case 2       print all files having str in their filename with time information\n");
    printf("-time -name str                  Case 2       print all files having str file name with time information\n");
    printf("-time -perm                      Case 8       print all files with time information and permissions\n");
    printf("-size (num1 num2)                Case 4,44    print all files with size(in MB) in between num1 <= size <= num2\n");
    printf("-size (num1 num2) -pname str     Case 1,11    print all files with size(in MB) in between num1 <= size <= num2 having str in their file name\n");
    printf("-size (num1 num2) -name str      Case 1,11    print all files with size(in MB) in between num1 <= size <= num2 having str  name\n");
    printf("-size (num1 num2) -time          Case 7,77    print all files with size(in MB) in between num1 <= size <= num2 and time info\n");
    printf("-size (num1 num2) -time -pname   Case 10,100  print all files with size(in MB) in between num1 <= size <= num2 and time info with str in file name\n");
    printf("-size (num1 num2) -time -name    Case 9,99    print all files with size(in MB) in between num1 <= size <= num2 and time info\n");

}
