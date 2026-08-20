#ifndef STRUCT_DEFN_H
#define STRUCT_DEFN_H
extern int lastAlbumID;
typedef struct song{
    int songID;              
    char songname[50];
    char artistname[20];
    int duration;
} song;

typedef struct songnode_Lib{
    song data;
    struct songnode_Lib* next;
} songnode_Lib;

typedef struct songid_node {
    int songID;
    struct songid_node* next;
} songid_node;


typedef struct albums{
    int albumID;                
    char albumname[50];
    struct albums* next_Album;
    songid_node* songs;   
} albums;

typedef struct playlist_node{
    int songID;                     
    struct playlist_node* next;
    struct playlist_node* prev;
} playlist_node;

typedef struct playlist_linklist{
    playlist_node* head;
    playlist_node* tail;
} playlist_linklist;

#endif
