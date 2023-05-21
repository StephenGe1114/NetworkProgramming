 ///
 /// @file    1.c
 /// @author  gsw(1499186594@qq.com)
 ///
   
/*传递一个路径名，还有一个文件名，搜索对应路径下是否有该文件，有就打印显示，显示绝对路径*/

#include "func.h"

void findFile(char path[128], char fileName[128])
{
    int ret = chdir(path);
    if(-1 == ret) {
        perror("chdir");
    }
    path = getcwd(NULL, 0);
    if(!path) {
        perror("getcwd");
    }
    DIR* dir = opendir(path);
    if(!dir) {
        perror("opendir");
        return;
    }
    struct dirent* p = NULL;
    char buf[128] = {0};
    while((p = readdir(dir)) != NULL) {
        if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
        } else {
            if(4 == p->d_type) {
                sprintf(buf, "%s/%s", path, p->d_name);
                findFile(buf, fileName);
            } else if(!strcmp(p->d_name, fileName)) {
                printf("%s/%s\n", path, fileName);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    args_check(argc, 3);
    findFile(argv[1], argv[2]);
    return 0;
}
