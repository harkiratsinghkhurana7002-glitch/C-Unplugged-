#include<stdio.h>
#include"../Include/lib_utils.h"
#include"../Include/alb_utils.h"
#include"../Include/playlist_utils.h"
#include<string.h>
#include<stdlib.h>
#include"../Include/structure_Defn.h"


songnode_Lib* LibLinkList(songnode_Lib*head){
    
FILE*ptr=fopen("Source/databasefiles/Lib.dat","rb");
if (ptr==NULL) {
        printf("Error: Could not open Lib.dat\n");
        return NULL;
    }
int n;
if (fread(&n, sizeof(int), 1, ptr) != 1) {
        printf("Error: Could not read song count\n");
        fclose(ptr);
        return NULL;
    }
head=NULL;
for(int i=0;i<n;i++){
songnode_Lib*newnode=malloc(sizeof(songnode_Lib));
fread(&(newnode->data),sizeof(newnode->data),1,ptr);
newnode->next=head;
head=newnode;
}
fclose(ptr);
return head;
}
void display_lib(){
    FILE*ptr=fopen("Source/databasefiles/Lib.txt","r");
    if (ptr == NULL) {
        printf("Error: Could not open file 'databases/Lib.txt'\n");
        return;
    }
    char ch;
    while((ch=fgetc(ptr))!=EOF){
        putchar(ch);
    }
    fclose(ptr);
}
song* getSongByID(songnode_Lib* lib, int songID) {
    songnode_Lib* temp = lib;

    while (temp != NULL) {
        if (temp->data.songID == songID) {
            return &(temp->data);
        }
        temp = temp->next;
    }

    return NULL; 
}
song* getSongByIndex(songnode_Lib* lib, int index){
    int count=1;
    songnode_Lib* temp=lib;

    while(temp!=NULL){
        if(count==index){
            return &(temp->data);
        }
        temp=temp->next;
        count++;
    }

    return NULL; 
}
