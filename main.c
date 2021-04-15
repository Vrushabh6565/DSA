#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

int main() {
    char file[] = "D:/";
    char *s = file;
    node root = generate_ftree(s);
//    searchbypart(root, "so", 0, 0, 0);
//    print_ftree(root);
//    char search1[] = "v";
//    searchbypart(root, search1, 1);
//    category(root, "docs");
//    char typ[] = ".cbp";
//    char *type = &typ;
//    permission(root, sear);
//    time_info(root, "1.txt");

    while(1) {
        printf("--------------FIND COMMAND-----------------\n\n");
        printf("FLAG\t\tUSES\n\n");
        printf("-name        used to find files by its name.\n");
        printf("-pname       used to find files by its partial name.\n");
        printf("-type d      used to find doc files.\n");
        printf("-type l      used to find file links.\n");
        printf("-type m      used to find media files.\n");
        printf("-perm        used to get permissions of file.\n");
        printf("-time        used to get mtime,atime,ctime of file.\n");
        printf("-size        used to get file with size(in MB)\n");
        printf("-exit        used to get out of find command\n");
        char *command, *word, *fname;
        int size = 0, size1 = 0, size2 = 0, time = 0, perm = 0, m = 0, l = 0, d = 0, pname = 0, name = 0, timereq = 0;
        clock_t t;
        command = (char*)calloc(100, '\0');
        fgets(command, 100, stdin);
        command[strlen(command) - 1] = '\0';
        for(int i = 0; i < strlen(command); i++) {
            if(command[i] == '-') {
                word = readword(command, i + 1);        //it return the flag name if flag present in command then do respective bit 1 else 0
                if(strcmp(word, "exit") == 0) {
                    delete_tree(root);                  //if want to exit then free tree and exit
                    printf("tree deleted");
                    exit(0);
                }
                if(strcmp(word, "help") == 0) {
                    help();                              //if want help
                }
                if(strcmp(word, "timereq") == 0) {
                    timereq = 1;                        //if want time required to find file
                }
                if(strcmp(word, "size") == 0) {        //if size flag present then make it 1 and set upper and lower limit of size
                    size = 1;
                    int j = i + 6;
                    for(j; command[j] >= '0' && command[j] <= '9'; j++)
                        size1 = size1 * 10 + (command[j] - 48);
                    for(j = j + 1; command[j] >= '0' && command[j] <= '9'; j++)
                        size2 = size2 * 10 + (command[j] - 48);

                }
                if(strcmp(word, "time") == 0) {
                    time = 1;
                }
                if(strcmp(word, "perm") == 0) {
                    perm = 1;
                }
                if(strcmp(word, "type") == 0) {             //if type flag present then check for m, l, d
                    if(command[i + 6] == 'm'){m = 1;}
                    else if(command[i + 6] == 'l'){l = 1;}
                    else if(command[i + 6] == 'd'){d = 1;}
                }
                if(strcmp(word, "pname") == 0) {            //if pname flag then extract name from command
                    pname = 1;
                    int chr = strlen(command) - (i + 5);
                    fname = (char*)calloc(chr, '\0');
                    int k = 0;
                    for(int j = i + 7;j < strlen(command); j++) {
                        fname[k] = command[j];
                        k++;
                    }
                    fname[k] = '\0';
                }
                if(strcmp(word, "name") == 0) {         //if name flag the extract name from command
                    name = 1;
                    int chr = strlen(command) - (i + 7);
                    fname = (char*)calloc(chr, '\0');
                    int k = 0;
                    for(int j = i + 6; j < strlen(command); j++) {
                        fname[k] = command[j];
                        k++;
                    }
                    fname[k] = '\0';
                }
            }
        }
        long int bit = getbit(size, time, perm, m, l, d, pname, name);  // bit pattern 1|size|time|perm|m|l|d|pname|name|
        //printf("%ld\n\n", bit);
       // printf("size = %d   %d  %d\ntime = %d\nperm = %d\nm = %d\nl = %d\nd = %d\npname = %d\nname = %d\n", hidden, size, size1, size2, time, perm, m, l, d, pname, name);
        int Case;
        switch(bit) {
            case 100000010:                             //bit pattern for -pname
                Case = 0;
                searchbypart(root, fname, size1, size2, Case);
                break;

            case 100000001:                                //-name
                Case = 0;
                if(timereq == 0)
                    searchbyname(root, fname, size1, size2, Case);
                if(timereq == 1) {
                    t = clock();
                    searchbyname(root, fname, size1, size2, Case);
                    t = clock() - t;
                    double time_req = ((double)t)/CLOCKS_PER_SEC;
                    printf("\n time required to find file = %f secs", time_req);
                }
                break;

            case 110000010:
                if(size1 == 0 && size2 == 0)                    //-size -pname
                    searchbypart(root, fname, size1, size2, 1);
                else if(size1 >= 0 && size2 >= 0 && size1 <= size2)    //-size (size1) (size2) -pname
                    searchbypart(root, fname, size1, size2, 11);
                break;

            case 110000001:
                if(size1 == 0 && size2 == 0)                //-size -name
                    searchbyname(root, fname, size1, size2, 1);
                else if(size1 >= 0 && size2 >= 0)                   //-size (size1) (size2) -name
                    searchbyname(root, fname, size1, size2, 11);
                break;
            case 101000010:                                     //-time -pname
                searchbypart(root, fname, size1, size2, 2);
                break;
            case 101000001:                                        //-time -name
                searchbyname(root, fname, size1, size2, 2);
                break;
            case 100100010:                                         //-perm -pname
                searchbypart(root, fname, size1, size2, 3);
                break;
            case 100100001:                                           //-perm -name
                searchbyname(root, fname, size1, size2, 3);
                break;
            case 100010000:                                             //-type m || -type l || -type d
                category(root, 'm');
                break;
            case 100001000:
                category(root, 'l');
                break;
            case 100000100:
                category(root, 'd');
                break;
            case 110000000:                                             //-size || -size (size1) (size2)
                if(size1 == 0 && size2 == 0)
                    print_ftree(root, size1, size2, 4);
                else if(size1 >= 0 && size2 >= 0)
                    print_ftree(root, size1, size2, 44);
                break;
            case 101000000:                                             //-time
                print_ftree(root, size1, size2, 5);
                break;
            case 100100000:                                             //-perm
                print_ftree(root, size1, size2, 6);
                break;
            case 111000000:                                            //-size -time
                if(size1 == 0 && size2 == 0)
                    print_ftree(root, size1, size2, 7);
                else if(size1 >= 0 && size2 >= 0)
                    print_ftree(root, size1, size2, 77);
                break;
            case 101100000:                                           //-time -perm
                    print_ftree(root, size1, size2, 8);
                break;
             case 111000001:                                          //-size -time  -name
                if(size1 == 0 && size2 == 0)
                    searchbyname(root, fname, size1, size2, 9);
                else if(size1 >= 0 && size2 >= 0 && size1 <= size2)
                    searchbyname(root, fname, size1, size2, 99);
                break;
             case 111000010:                                            //-size -time  -pname
                if(size1 == 0 && size2 == 0)
                    searchbypart(root, fname, size1, size2, 10);
                else if(size1 >= 0 && size2 >= 0 && size1 <= size2)
                    searchbypart(root, fname, size1, size2, 100);
                break;
            default:
                printf("Something went wrong try again .........(given combination of of flages may not available please type \"-help\" for help) ");
        }
        getc(stdin);
        system("cls");
    }
    return 0;
}
