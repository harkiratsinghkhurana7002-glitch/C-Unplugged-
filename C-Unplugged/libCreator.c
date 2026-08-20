#include <stdio.h>
#include <string.h>

typedef struct song {
    int songID;               
    char songname[50];
    char artistname[20];
    int duration;
} song;

int main() {
    FILE *ptr1 = fopen("Source/databasefiles/Lib.dat", "wb");
    if (ptr1 == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int n; 
    printf("Enter the number of songs:\n");
    scanf("%d", &n);

    fwrite(&n, sizeof(int), 1, ptr1);

    for (int i = 0; i < n; i++) {
        song s;

        
        s.songID = 1000 + i;

        printf("Enter the name for Song No.%d\n", i + 1);
        scanf(" %[^\n]", s.songname);

        printf("Enter the Artist name for Song No.%d\n", i + 1);
        scanf(" %[^\n]", s.artistname);

        printf("Enter the Duration for Song No.%d\n", i + 1);
        scanf("%d", &s.duration);

        
        fwrite(&s, sizeof(song), 1, ptr1);
    }

    fclose(ptr1);
    printf("Your New Library has been created successfully\n");
    return 0;
}
