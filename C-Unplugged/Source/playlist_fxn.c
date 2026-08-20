#include<stdio.h>
#include"../Include/lib_utils.h"
#include"../Include/alb_utils.h"
#include"../Include/playlist_utils.h"
#include<string.h>
#include<stdlib.h>
#include"../Include/structure_Defn.h"
playlist_linklist* album_to_playlist(playlist_linklist*play,albums*alb){
    if(alb==NULL){
        printf("Error:album not found\n");
        return play;
    }

    songid_node*temp=alb->songs;
    if(temp==NULL){
        printf("Album is empty\n");
        return play;
    }

    if(play->head==NULL&&play->tail==NULL){

        playlist_node*temp2=malloc(sizeof(playlist_node));
        temp2->songID=temp->songID;
        temp2->next=NULL;
        temp2->prev=NULL;
        play->head=temp2;
        play->tail=temp2;
        temp=temp->next;

        while(temp!=NULL){
            playlist_node*newnode=malloc(sizeof(playlist_node));
            newnode->songID=temp->songID;
            newnode->next=NULL;
            newnode->prev=temp2;
            temp2->next=newnode;
            play->tail=newnode;
            temp2=newnode;
            temp=temp->next;
        }

    } else {

        while(temp!=NULL){
            playlist_node*newnode=malloc(sizeof(playlist_node));
            newnode->songID=temp->songID;
            newnode->next=NULL;
            newnode->prev=play->tail;
            play->tail->next=newnode;
            play->tail=newnode;
            temp=temp->next;
        }
    }

    printf("Album %s is added to playlist successfully\n",alb->albumname);
    return play;
}
playlist_linklist* song_to_playlist(playlist_linklist*play,int songIndex,songnode_Lib*lib){
    song* s=getSongByID(lib,999+songIndex);
    if(s==NULL){
        printf("Invalid song index\n");
        return play;
    }

    playlist_node*newnode=malloc(sizeof(playlist_node));
    newnode->songID=s->songID;
    newnode->next=NULL;
    newnode->prev=NULL;

    if(play->head==NULL){
        play->head=newnode;
        play->tail=newnode;
        return play;
    }

    play->tail->next=newnode;
    newnode->prev=play->tail;
    play->tail=newnode;

    return play;
}

playlist_node* next_song(playlist_linklist*play,playlist_node*curr){
    if(curr==NULL){
        printf("Error:playlist is empty\n");
        return NULL;
    }
    if(curr->next==NULL){return play->head;}
    return curr->next;
}
playlist_node* prev_song(playlist_linklist*play,playlist_node*curr){
    if(curr==NULL){
        printf("Error:playlist is empty\n");
        return NULL;
    }
    if(curr->prev==NULL){return play->tail;}
    return curr->prev;
}
playlist_node* current_song(playlist_linklist*play,playlist_node*curr){
    if(curr==NULL){
        printf("Error:playlist is empty\n");
        return NULL;
    }
    return curr;
}
void view_playlist(playlist_linklist*play,songnode_Lib*lib){
    if(play->head==NULL){
        printf("Playlist is Empty\n");
        return;
    }

    printf("Your Playlist:\n");
    playlist_node*temp=play->head;
    int count=1;

    while(temp!=NULL){
        song*s=getSongByID(lib,temp->songID);
        if(s!=NULL){
            printf("%d. %s by %s (%d sec)\n",count++,s->songname,s->artistname,s->duration);
        }
        temp=temp->next;
    }
}
playlist_node* del_song_from_playlist(playlist_linklist*play,int songID){
    if(play->head==NULL){
        printf("Playlist is Empty\n");
        return NULL;
    }

    playlist_node*temp=play->head;

    if(temp->songID==songID){
        playlist_node*newHead=temp->next;
        if(newHead!=NULL)newHead->prev=NULL;
        free(temp);
        printf("Song deleted successfully\n");
        return newHead;
    }

    while(temp!=NULL&&temp->songID!=songID){
        temp=temp->next;
    }

    if(temp==NULL){
        printf("No such song exists in the playlist\n");
        return play->head;
    }

    playlist_node*prevNode=temp->prev;
    playlist_node*nextNode=temp->next;

    if(prevNode!=NULL)prevNode->next=nextNode;
    if(nextNode!=NULL)nextNode->prev=prevNode;

    free(temp);

    printf("Song deleted successfully\n");
    return play->head;
}
