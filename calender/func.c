#include <stdio.h>
#include <string.h>

struct tag {

  float time[48];
  char mission[48][50];
};
struct delete_ {
  int tag;
  int start_index_time;
  int end_index_time;
  char mission[40];
};
struct delete_ del_tag[48];
struct tag tags[7];

char tags_name[7][10] = {"Montag",  "Dienstag", "Mittwoch", "Donnerstag",      "Freitag", "Samstag",  "Sonntag"};

void list(){
        
  for(int i=0; i<7 ; i++){
    printf("\n----------------\n");
    printf("%s\n",tags_name[i]);
    for(int k=0 ; k<47 ; ){
      int b=1;
      if(strcmp(tags[i].mission[k],"-")!=0){

        
        for(int j =k+1;j<48;j++){
            if(strcmp(tags[i].mission[k],tags[i].mission[j]) == 0){
              b++;     
            }else{
              printf("%.2f - %.2f %s\n", tags[i].time[k],tags[i].time[k+b], tags[i].mission[k]);
              k+=b;
              break;
            }
        }
      }else{
        k++;
      }
    }
     printf("----------------\n");
      
  }
}

void list_tag(int a){
a--;
printf("%s\n",tags_name[a]);
int x =0;
    for(int k=0 ; k<47 ; ){
      int b=1;
      if(strcmp(tags[a].mission[k],"-")!=0){

        
        for(int j =k+1;j<48;j++){
            if(strcmp(tags[a].mission[k],tags[a].mission[j]) == 0){
              b++;     
            }else{
              printf("(%d)%.2f - %.2f %s\n",x+1 ,tags[a].time[k],tags[a].time[k+b], tags[a].mission[k]);
              del_tag[x].tag =a;
              del_tag[x].start_index_time =k;
              del_tag[x].end_index_time =k+b;
              strcpy(del_tag[x].mission,tags[a].mission[k]);
              x++;
              k+=b;
              break;
            }
        }
      }else{
        k++;
      }
    }

  
}

void load() {
  FILE *fptr;

  char txt[5] = ".txt";
  char t[10];
  fptr = fopen("montag.txt", "r");

  for (int j = 0; j < 7; j++) {
    sprintf(t, "%d", j);
    strcat(t, txt);
    fptr = fopen(t, "r");
    // printf("haftanın %d. günü\n",j+1);

    for (int i = 0; i < 48; i++) {
      fscanf(fptr, "%f %s", &tags[j].time[i], tags[j].mission[i]);
      // printf("saat :%.2f aufgabe : %s\n",tags[j].time[i],tags[j].mission[i]);
    }
  }
  fclose(fptr);
}

void update(int tag) {
  char txt[5] = ".txt";
  char t[10];
  sprintf(t, "%d", tag);
  strcat(t, txt);
  remove(t);
  FILE *fptr;
  fptr = fopen(t, "w");

  for (int i = 0; i < 48; i++) {
    fprintf(fptr, "%.2f %s\n", tags[tag].time[i], tags[tag].mission[i]);
  }

  fflush(fptr);
}




void add(int tag, float index_time_start, float index_time_end,
         char mission[40]) {

  for (int i = index_time_start; i <= index_time_end; i++) {

    strcpy(tags[tag].mission[i], mission);
    update(tag);
  }
}




void selection_byself(float time) {
  int x = 0;
  for (int a = 0; a < 7; a++) {
    printf("%s\n", tags_name[a]);
    for (int i = 0; i <= 48 - 2 * time; i++) {
      x = 0;

      if (strcmp(tags[a].mission[i], "-") == 0) {
        x = 1;
        for (int j = i + 1; j < i + 2 * time; j++) {

          if (strcmp(tags[a].mission[j], "-") != 0) {
            x = 0;
          }
        }

        if (x == 1) {
          int end = i + 2 * time;
          if (i == 48 - 2 * time) {
            printf("[%.2f-0.00] -\n", tags[a].time[i]);
          } else {

            printf("[%.2f-%.2f] -\n", tags[a].time[i], tags[a].time[end]);
          }
        }
      }
    }
  }
  wieder:
  printf("Wählen Sie Tag((1)Montag-(7)Sonntag) Uhr(2.00) \n");
  int tag;
  float clock;
  char mission[40];
  
  
  scanf("%d %f", &tag, &clock);
  if(tag < 8 && tag >0 && clock>=0.00 &&clock <= 23.30){
  printf("Geben Sie den Namen ein \n");
  scanf("%s", mission);
  for (int i = 0; i < 48; i++) {
    if (clock == tags[tag].time[i]) {
      add(tag-1, i, i + 2 * time - 1, mission);
      break;
    }
  }
  printf("fertig Noch etwas\n");
  }else{
    printf("Fehler");
    goto wieder;
  }
}




void find(float time) {

  char choise;
  int x = 0;
  for (int a = 0; a < 7; a++) {

    for (int i = 0; i <= 48 - 2 * time; i++) {

      if (strcmp(tags[a].mission[i], "-") == 0) {
        x = 1;
        for (int j = i + 1; j < i + 2 * time; j++) {

          if (strcmp(tags[a].mission[j], "-") != 0) {
            x = 0;
          }
        }
        if (x == 1) {
   str:       printf("Der erste verfügbare Slot ist am %s ab %.2f Uhr? OK (1), "
                 "Selbst wählen (2)?\n",
                 tags_name[a], tags[a].time[i]);
          scanf(" %c", &choise);

          if (choise == '1') {
            char mission[40];
            printf("%.2f Stunden für %.2f Uhr am %s werden zugewiesen für:\n",
                   time, tags[a].time[i], tags_name[a]);
            scanf("%s", mission);
            add(a, i, i + 2 * time - 1, mission);
            goto hier;
          } else if(choise == '2') {
            selection_byself(time);
          }else{
            printf("Fehler");
            goto str;
          }
        }
      }
    }
  }

hier:
  printf("fertig Noch etwas\n");
}



void del_mission(int j){
  j--;
  for(int i = del_tag[j].start_index_time;i<del_tag[j].end_index_time;i++){
    strcpy(tags[del_tag[j].tag].mission[i],"-");
    update(del_tag[j].tag);
  }
  
}




