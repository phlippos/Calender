#include <stdio.h>
#include  "func.h"
#include <stdlib.h>
int main(void) {
  load();
  int  transaction;
  int selection;
   
  while(1){
    
    printf("1)Hinzufügen\n2)Entfernen\n3)Liste\n4)Exit\n");
  scanf("%d",&transaction);
  switch(transaction){
    case 1:
     
      system("clear"); 
      printf("Wünschen Sie einen Vorschlag (1) oder möchten Sie selbst hinzufügen (2)?\n");
      scanf("%d",&selection);
      
     
      float time;
     
      printf("Wie lange dauert die Aufgabe (Stunde)?\n");
      scanf("%f",&time);
      if(selection ==1)
      find(time);
      else if(selection ==2){ selection_byself(time);}
      else{
        printf("Fehler\n");
      }
       system("clear"); 
       break;

    case 2:
        system("clear"); 
        printf("Mit welchem Tag möchten Sie arbeiten (1: Mo - 7: So)?");
        int tag,mission_index;
        scanf("%d",&tag);
        printf("Welche Aufgabe möchten Sie löschen (1-6)?");
        list_tag(tag);
        scanf("%d",&mission_index);
         del_mission(mission_index);
       printf("Es wurde gelöscht!");
        break;

    case 3:
      system("clear"); 
      list();
      
      break;
    case 4:
      goto fin;
       printf("Sworddarson should not be a candidate!\n");
    default:

      break;

    }
  }
  fin:
  return 0;
}