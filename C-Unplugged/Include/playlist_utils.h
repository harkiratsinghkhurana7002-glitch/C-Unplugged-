#ifndef PLAYLIST_UTILS_H
#define PLAYLIST_UTILS_H
#include"structure_Defn.h"
playlist_linklist* album_to_playlist(playlist_linklist*play,albums*alb);
playlist_linklist* song_to_playlist(playlist_linklist*play,int songIndex,songnode_Lib*lib);
playlist_node* next_song(playlist_linklist*play,playlist_node*curr);
playlist_node* prev_song(playlist_linklist*play,playlist_node*curr);
playlist_node* current_song(playlist_linklist*play,playlist_node*curr);
void view_playlist(playlist_linklist*play,songnode_Lib*lib);
playlist_node* del_song_from_playlist(playlist_linklist*play,int songID);
#endif