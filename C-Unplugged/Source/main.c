#include<stdio.h>
#include"../Include/lib_utils.h"
#include"../Include/alb_utils.h"
#include"../Include/playlist_utils.h"
#include<string.h>
#include<stdlib.h>
#include"../Include/structure_Defn.h"

int main(){
  FILE*ptr=fopen("Source/databasefiles/log.txt","a");
fputs("\n",ptr);
fprintf(ptr,"User opened the program\n");

songnode_Lib*lib=NULL;
lib=LibLinkList(lib);

albums*alb=NULL;
alb=AlbLinkList(alb);
updateLastAlbumID(alb);
playlist_linklist*play=malloc(sizeof(playlist_linklist));
play->head=NULL;
play->tail=NULL;

printf("                                                           C-Unplugged: Your Music Partner\n");
printf("Library\n");
display_lib();
printf("\n");

printf("\nYour Albums:\n");
list_all_albums(alb);

  int choice;
int flag=1;

while(flag){
    printf("\nOptions:\n");
    printf("1)List all the songs in the Library\n");
    printf("2)List all the albums in your Library\n");
    printf("3)Open an Album\n");
    printf("4)Create new Album\n");
    printf("5)Modify Album\n");
    printf("6)Delete Album\n");
    printf("7)Add Songs/Album to the playlist\n");
    printf("8)View Playlist\n");
    printf("9)Play playlist\n");
    printf("10)Delete song from playlist\n");
    printf("11)Display Log\n");
    printf("12)Exit the Program\n");

    printf("SELECT YOUR CHOICE\n");
    scanf("%d",&choice);
    fprintf(ptr,"Choice Selected:%d\n",choice);

    switch(choice){
      case 1:{
       display_lib();
       printf("\n");
       fprintf(ptr,"User opened the Library\n"); 
        break;
      }
      case 2:{
      list_all_albums(alb); 
      fprintf(ptr,"User opened the Albums library\n");
      break;
      }
      case 3:{
    printf("Your Albums:\n");
    list_all_albums(alb);

    printf("Enter album number to open:\n");
    int index;
    scanf("%d",&index);
    fprintf(ptr,"User attempted to open album index:%d\n",index);

    albums*a=findAlbumByIndex(alb,index);
    if(a==NULL){
        printf("Invalid album number\n");
        break;
    }

    view_songs(a,lib);
    fprintf(ptr,"User opened album '%s'\n",a->albumname);
    break;
}
case 4: {
    printf("Give the name for the new album:\n");
    char name1[50];
    scanf(" %[^\n]", name1);

    fprintf(ptr, "User attempted to create album '%s'\n", name1);

    albums* result = create_new_album(alb, name1);

    if (result == NULL) {
        printf("Failed to create album.\n");
        fprintf(ptr, "Album '%s' creation FAILED\n", name1);
        break;
    }

    alb = result;

    printf("Album '%s' created successfully\n", name1);
    fprintf(ptr, "Album '%s' created successfully\n", name1);

    break;
}

      case 5:{
    list_all_albums(alb);

    int albIndex;
    printf("Enter the album index to modify:\n");
    scanf("%d",&albIndex);

    albums* tomod=findAlbumByIndex(alb,albIndex);
    if(tomod==NULL)break;

    printf("Options:\n1)Add Song\n2)Delete Song\nChoose:\n");
    int interchoice;
    scanf("%d",&interchoice);

    if(interchoice==1){
        display_lib();
        printf("\n");
        printf("Enter song index from Library to add:\n");
        int sindex;
        scanf("%d",&sindex);

        tomod=add_song_to_album(tomod,sindex,lib);
        fprintf(ptr,"User added Song(index=%d) to Album '%s'\n",sindex,tomod->albumname);
    }

    else if(interchoice==2){
        view_songs(tomod,lib);

        printf("Enter song index inside this album to delete:\n");
        int delIndex;
        scanf("%d",&delIndex);

        tomod=del_song_from_alb(tomod,delIndex,lib);
        fprintf(ptr,"User deleted Song(index=%d) from Album '%s'\n",delIndex,tomod->albumname);
    }

    break;
}
case 6:{
        list_all_albums(alb);
        printf("Enter album index to delete:\n");
        int ind; scanf("%d",&ind);
        alb = delete_album(alb,ind);
        fprintf(ptr,"User deleted album index %d\n",ind);
        break;

}
case 7:{
    int interchoice;
    printf("Options:\n1)Add Song\n2)Add Album\n");
    scanf("%d",&interchoice);

    if(interchoice==1){
        display_lib();
        printf("\n");
        printf("Enter song index to add to playlist:\n");
        int sindex;
        scanf("%d",&sindex);

        play=song_to_playlist(play,sindex,lib);
        fprintf(ptr,"User added Song(index=%d) to playlist\n",sindex);
    }

    else if(interchoice==2){
        list_all_albums(alb);
        printf("Enter album index to add to playlist:\n");
        int aindex;
        scanf("%d",&aindex);

        albums* toadd=findAlbumByIndex(alb,aindex);
        if(toadd!=NULL){
            play=album_to_playlist(play,toadd);
            fprintf(ptr,"User added Album(index=%d) to playlist\n",aindex);
        }
    }

    break;
}
      case 8:{
    view_playlist(play,lib);
    fprintf(ptr,"User viewed the playlist\n");
    break;
}

      case 9:{
    fprintf(ptr,"User played the playlist\n");

    if(play->head==NULL){
        printf("Playlist is empty\n");
        break;
    }

    playlist_node* curr=play->head;
    int ch=1;

    while(ch){
        song* s=getSongByID(lib,curr->songID);
        if(s==NULL){
            printf("Error: Song details missing\n");
            break;
        }

        printf("Song '%s' by %s is playing for %d sec...\n",
               s->songname,s->artistname,s->duration);

        printf("Options:\n1)Next\n2)Prev\n3)Curr\n4)Stop Playlist\n");

        int interchoice;
        scanf("%d",&interchoice);

        switch(interchoice){
            case 1:{
                curr=next_song(play,curr);
                break;}

            case 2:{
                curr=prev_song(play,curr);
                break;}

            case 3:{
                curr=current_song(play,curr);
                break;}

            case 4:{
                ch=0;
                break;}
        }
    }

    break;
}

     case 10:{
    if(play->head==NULL){
        printf("Playlist is empty\n");
        break;
    }

    view_playlist(play,lib);

    printf("Enter the song index in playlist to delete:\n");
    int pindex;
    scanf("%d",&pindex);

    playlist_node* temp=play->head;
    int count=1;

    while(temp!=NULL && count<pindex){
        temp=temp->next;
        count++;
    }

    if(temp==NULL){
        printf("Invalid playlist index %d\n",pindex);
        break;
    }

    int sid=temp->songID;
    play->head=del_song_from_playlist(play,sid);

    if(play->head==NULL){
        play->tail=NULL;
    }
    else{
        playlist_node* t=play->head;
        while(t->next!=NULL)t=t->next;
        play->tail=t;
    }

    fprintf(ptr,"User deleted SongID=%d from playlist\n",sid);
    break;
}
case 11: {
    printf("\n--- Command Log History ---\n");

    FILE *logptr = fopen("Source/databasefiles/log.txt", "r");
    if (logptr == NULL) {
        printf("Error: Could not open log file.\n");
        break;
    }

    char ch;
    while ((ch = fgetc(logptr)) != EOF) {
        putchar(ch);
    }

    fclose(logptr);

    fprintf(ptr, "User viewed command history log\n");
    break;
}

      case 12:{
    fprintf(ptr,"User closed the program\n");
    update_albums(alb);
    flag=0;
    break;
}

    }
    
  }
  fclose(ptr);

playlist_node* temp_play = play->head;
while(temp_play != NULL){
    playlist_node* temp1 = temp_play;
    temp_play = temp_play->next;
    free(temp1);
}
free(play);

albums* temp_alb = alb;
while(temp_alb != NULL){
    albums* temp1 = temp_alb;

  
    songid_node* temp_song = temp1->songs;
    while(temp_song != NULL){
        songid_node* temp_s = temp_song;
        temp_song = temp_song->next;
        free(temp_s);
    }

    
    temp_alb = temp_alb->next_Album;
    free(temp1);
}


songnode_Lib* temp_lib = lib;
while(temp_lib != NULL){
    songnode_Lib* temp = temp_lib;
    temp_lib = temp_lib->next;
    free(temp);
}

printf("Closing the program.....\n");

}
