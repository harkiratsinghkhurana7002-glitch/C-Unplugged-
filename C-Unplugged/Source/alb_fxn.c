#include<stdio.h>
#include"../Include/lib_utils.h"
#include"../Include/alb_utils.h"
#include"../Include/playlist_utils.h"
#include<string.h>
#include<stdlib.h>
#include"../Include/structure_Defn.h"

int lastAlbumID=4999;

albums*AlbLinkList(albums*alb){

FILE*ptr=fopen("Source/databasefiles/alb.dat","rb");
if(ptr==NULL){
printf("Error:Could not fetch data from alb.dat\n");
return NULL;
}

int num_of_albums;
size_t check=fread(&num_of_albums,sizeof(int),1,ptr);

alb=NULL;

if(check==0){
fclose(ptr);
return alb;
}

for(int i=0;i<num_of_albums;i++){

albums*temp=malloc(sizeof(albums));

fread(&temp->albumID,sizeof(int),1,ptr);

fread(temp->albumname,sizeof(temp->albumname),1,ptr);

int num_of_songs;
fread(&num_of_songs,sizeof(int),1,ptr);

songid_node*headID=NULL;

for(int j=0;j<num_of_songs;j++){
int id;
fread(&id,sizeof(int),1,ptr);
songid_node*newID=malloc(sizeof(songid_node));
newID->songID=id;
newID->next=headID;
headID=newID;
}

temp->songs=headID;
temp->next_Album=alb;
alb=temp;
}

fread(&lastAlbumID,sizeof(int),1,ptr);

fclose(ptr);
return alb;
}

int count_alb(albums*alb){
    
    albums*temp=alb;int count=0;
    while(temp!=NULL){
        count++;
        temp=temp->next_Album;
    }
    return count;
}
int count_song(songid_node* songs) {
    int count = 0;
    songid_node* temp=songs;

    while (temp!=NULL) {
        count++;
        temp=temp->next;
    }

    return count;
}
void update_albums(albums*alb){
    FILE*ptr=fopen("Source/databasefiles/alb.dat","wb");
    if(ptr==NULL){
        printf("Error: Saving albums\n");
        return;
    }

    int n=count_alb(alb);
    fwrite(&n, sizeof(int), 1, ptr);

    albums*temp=alb;

    for(int i=0;i<n;i++){
        fwrite(&temp->albumID, sizeof(int), 1, ptr);

        fwrite(temp->albumname, sizeof(temp->albumname), 1, ptr);

        int m=count_song(temp->songs);
        fwrite(&m, sizeof(int), 1, ptr);

        songid_node* idnode=temp->songs;
        while(idnode!=NULL){
            fwrite(&idnode->songID, sizeof(int), 1, ptr);
            idnode=idnode->next;
        }

        temp=temp->next_Album;
    }

    fwrite(&lastAlbumID, sizeof(int), 1, ptr);

    fclose(ptr);
}

void list_all_albums(albums*alb){

    if(alb==NULL){
        printf("Album is empty\n");
        return;
    }
    albums*temp=alb;int count=1;
    printf("--- List of Albums ---\n");
    while(temp!=NULL){
        printf("%d. %s\n",count,temp->albumname);
        temp=temp->next_Album;count++;
    }
    return;
}
albums*add_song_to_album(albums*alb,int index,songnode_Lib*lib){
if(alb==NULL){
printf("Error:Album Not Found\n");
return alb;
}

int songID=1000+(index-1);

song* s=getSongByID(lib,songID);
if(s==NULL){
printf("Invalid Song Number\n");
return alb;
}

songid_node*check=alb->songs;
while(check!=NULL){
if(check->songID==songID){
printf("Song Already Exists In Album\n");
return alb;
}
check=check->next;
}

songid_node*newid=malloc(sizeof(songid_node));
newid->songID=songID;
newid->next=NULL;

if(alb->songs==NULL){
alb->songs=newid;
printf("Song '%s' added successfully\n",s->songname);
return alb;
}

songid_node*temp=alb->songs;
while(temp->next!=NULL){
temp=temp->next;
}
temp->next=newid;

printf("Song '%s' added successfully\n",s->songname);
return alb;
}

albums*del_song_from_alb(albums*alb,int index,songnode_Lib*lib){
if(alb==NULL){
printf("Error:Album not Found\n");
return alb;
}

if(alb->songs==NULL){
printf("Error:Album is empty\n");
return alb;
}

songid_node*temp=alb->songs;
int count=1;
while(temp!=NULL&&count<index){
temp=temp->next;
count++;
}

if(temp==NULL){
printf("Invalid song index\n");
return alb;
}

int sid=temp->songID;

song* s=getSongByID(lib,sid);

if(alb->songs->songID==sid){
songid_node*del=alb->songs;
alb->songs=del->next;
free(del);
printf("Song '%s' deleted successfully\n",s->songname);
return alb;
}

songid_node*prev=alb->songs;
while(prev->next!=NULL&&prev->next->songID!=sid){
prev=prev->next;
}

if(prev->next==NULL){
printf("Invalid song index\n");
return alb;
}

songid_node*del=prev->next;
prev->next=del->next;
free(del);

printf("Song '%s' deleted successfully\n",s->songname);
return alb;
}
albums* create_new_album(albums*head,char albumname[]){

    albums*newAlb = malloc(sizeof(albums));
    strcpy(newAlb->albumname,albumname);

    newAlb->albumID = ++lastAlbumID;
    newAlb->songs   = NULL;
    newAlb->next_Album = NULL;

    if(head == NULL) return newAlb;

    albums*temp = head;
    while(temp->next_Album != NULL)
        temp = temp->next_Album;

    temp->next_Album = newAlb;

    return head;
}

void view_songs(albums*alb,songnode_Lib*lib){

if(alb==NULL){
printf("Error:Album not found.\n");
return;
}

if(alb->songs==NULL){
printf("Album is empty.\n");
return;
}
printf("--- Songs in Album: %s ---\n",alb->albumname);
songid_node*temp=alb->songs;
int count=1;
while(temp!=NULL){
song* s=getSongByID(lib,temp->songID);
if(s!=NULL){
printf("%d.%s by %s (%d sec)\n",count,s->songname,s->artistname,s->duration);
}
temp=temp->next;
count++;
}
printf("Total Songs:%d\n",count-1);
}

albums* findAlbumByIndex(albums*alb, int index){
    if(alb==NULL){
        printf("Error: No albums exist.\n");
        return NULL;
    }
    albums*temp = alb;
    int count = 1;
    while(temp!=NULL && count<index){
        temp = temp->next_Album;
        count++;
    }
    if(temp==NULL){
        printf("Error: Invalid album index %d\n", index);
        return NULL;
    }

return temp;
}
albums* delete_album(albums* head,int index){
    if(head==NULL){
        printf("No albums exist.\n");
        return NULL;
    }

    if(index==1){
        albums* t=head;
        head=head->next_Album;

        songid_node* s=t->songs;
        while(s!=NULL){
            songid_node* x=s;
            s=s->next;
            free(x);
        }

        printf("Album '%s' deleted successfully.\n",t->albumname);
        free(t);
        return head;
    }

    albums* temp=head;
    int count=1;

    while(temp->next_Album!=NULL && count<index-1){
        temp=temp->next_Album;
        count++;
    }

    if(temp->next_Album==NULL){
        printf("Invalid album index.\n");
        return head;
    }

    albums* del=temp->next_Album;
    temp->next_Album=del->next_Album;

    songid_node* s=del->songs;
    while(s!=NULL){
        songid_node* x=s;
        s=s->next;
        free(x);
    }

    printf("Album '%s' deleted successfully.\n",del->albumname);
    free(del);

    return head;
}
void updateLastAlbumID(albums* head){
    albums* temp = head;
    while(temp != NULL){
        if(temp->albumID > lastAlbumID){
            lastAlbumID = temp->albumID;
        }
        temp = temp->next_Album;
    }
}
