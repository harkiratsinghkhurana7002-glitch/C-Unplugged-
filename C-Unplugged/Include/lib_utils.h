
#ifndef LIB_UTILS_H
#define LIB_UTILS_H
#include"structure_Defn.h"
songnode_Lib* LibLinkList(songnode_Lib*head);
void display_lib();
song* getSongByID(songnode_Lib* lib, int songID);
song* getSongByIndex(songnode_Lib* lib, int index);
#endif