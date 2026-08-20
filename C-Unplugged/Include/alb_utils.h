#ifndef ALB_UTILS_H
#define ALB_UTILS_H
#include"structure_Defn.h"

albums*AlbLinkList(albums*alb);
int count_alb(albums*alb);
int count_song(songid_node* songs);
void update_albums(albums*alb);
void list_all_albums(albums*alb);
albums*add_song_to_album(albums*alb,int index,songnode_Lib*lib);
albums*del_song_from_alb(albums*alb,int index,songnode_Lib*lib);
albums* create_new_album(albums*head,char albumname[]);
void view_songs(albums*alb,songnode_Lib*lib);
albums* findAlbumByIndex(albums*alb, int index);
albums* delete_album(albums* head,int index);
void updateLastAlbumID(albums* head);
#endif