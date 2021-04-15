typedef struct TreeNode {
    char *fname;                        //points to string of filename
    struct TreeNode *directory;         //points to directories
    int permissions;                    // file permission like 'w','r','x' etc
    int size;                           //store size of file
    int link;                           //to check file is a link or regular file
    char *mtime;                        //last modified time
    char *atime;                        //last access time
    char *ctime;                        //last status change time
    struct TreeNode *next, *parent;     // points to next node of same type
}TreeNode;

typedef TreeNode* node;
char *build_path(const char *root, char *filename);
// it generates tree considering given parameter as root node
node generate_ftree(char *fname);

