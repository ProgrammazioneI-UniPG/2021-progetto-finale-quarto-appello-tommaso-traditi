// TOMMASO TRADITI             MATRICOLA N. 331519

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "gamelib.h"
unsigned short int imp=0,set;
static void intro(){
  system("clear");

printf("\t\t\t\t\t\t\tCONSIGLIO DI INGRANDIRE LO SCHERMO PER EVITARE GLITCH GRAFICI\n");
sleep(2);
system("clear");
printf("\t\t\t\t\t\t\t\t\tTOMMASO TRADITI   MATRICOLA N. 331519\n");
sleep(2);
system("clear");
}

void menu(){
  e:
  system("clear");
  printf("\033[1;31m");
  printf("\t                              ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄                                                                                                                            \n");
  printf("\t                          ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀                                                                                                                        \n");
  printf("\t                         ⣸⣿⡏⠀⠀");printf("\033[1;36m ⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿");printf("\033[1;37m⣄ ");printf("\033[1;33m       _________  ________  ________  ________   ________   ________  ___                                        \n");
  printf("\t\033[1;31m⠀                  ⣀⣤⣴⣶⣶⣿⡟");printf("\033[1;36m⠀⠀⠀⢸⣿⣿⣿⣆");printf("\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷ ");printf("\033[1;33m      |\\___   ___\\\\   __  \\|\\   __  \\|\\   ___  \\|\\   ___  \\|\\   __  \\|\\  \\                             \n");
  printf("\t\033[1;31m                  ⢸⣿⡇⠀⠀⣿⣿⡇");printf("\033[1;36m⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿");printf("\033[1;37m⣿⣿⣿⡿ ");printf("\033[1;33m      \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\              \n");
  printf("\t\033[1;31m                  ⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧ ");printf("\033[1;33m           \\ \\  \\ \\ \\   _  _\\ \\   __  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \\  \\                \n");
  printf("\t\033[1;31m                  ⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿ ");printf("\033[1;33m            \\ \\  \\ \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \\  \\          \n");
  printf("\t\033[1;31m                  ⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃ ");printf("\033[1;33m             \\ \\__\\ \\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\__\\\\ \\__\\ \\_______\\ \\__\\            \n");
  printf("\t\033[1;31m                       ⠀ ⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀ ");printf("\033[1;33m             \\|__|  \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|__| \\|__|\\|_______|\\|__|                             \n");
  printf("\t\033[1;31m                        ⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏                                                                                                                       \n");
  printf("\n");
  printf("\033[1;37;44m . 　　　。　　　　•　 　.　　 。　　　　　 ඞ 。 . 　　 • 　　　　• 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 \n");
  printf(" . 　。　　　•　 　ﾟ　　。 　　.. 　　　。　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　.　　 。　　　　　 ඞ 。 . 　　 • 　　　　•.   \n");
  printf("　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　\n");
  printf(" 　　.　　　 　　.　　. 　　　　　 ඞ 。 . 　　 • 　　　　•　　.　。　　 。　 .   ");printf("\033[1;32m1...IMPOSTA GIOCO");printf("\033[1;37m 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　  \n");
  printf("　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　.  ");printf("\033[1;32m2...........GIOCA");printf("\033[1;37m　　.　　　 　　.　　　　　。　　 。　.　　 。　　　　　 ඞ 。 . 　　 • 　　　　• \n");
  printf("　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　.  ");printf("\033[1;32m3...TERMINA GIOCO");printf("\033[1;37m 　　.　　　 　　.　　　　　。　　 。　.  　　.　　　 　　.　　　　　。　　 。　.\n");
  printf("　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　　　　　。　　 。　. 　　.　　　 　　.　  \n");
  printf(" . 　　　。　　　　•　 　.　　 。　　　　　 ඞ 。 . 　　 • 　　　　• 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 \n");
  printf(" . 　。　　　•　 　ﾟ　　。 　　.. 　　　。　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　。 　　.. 　　　。　　　　•　 　ﾟ　　.　　 。　　　　　 ඞ 。 . 　　 • 　　　　•.   \n");
  printf("\033[0;0;0m");

        do{
           printf("\n\t\t\t\tSCELTA...    ");
          //controllo sull'input
          while (scanf("%hu",&imp) != 1 || imp >3|| imp <1){
                  printf("\n\t\t\033[1;31m SCELTA NON CORRETTA! \n\n\t\t REINSERISCI IL VALORE:\n");
                  printf("\n\t\t\033[1;32m1...IMPOSTA GIOCO\n");
                  printf("\t\t\033[1;32m2...........GIOCA\n");
                  printf("\t\t\033[1;32m3...TERMINA GIOCO\n");
                  printf("\n\t\tSCELTA... ");
                  printf("\033[0;0;0m");
              while (getchar() != '\n');
          }
          switch(imp){
                 case 1:
                        imposta_gioco ();
                        break;
                 case 2:
                        if (set == 0){
                            system("clear");
                            printf("Devi prima impostare  il gioco \n");
                            sleep(2);
                            system ("clear");
                            goto e;
                        }
                        else{
                        system ("clear");
                        gioca();}
                        break;
                 case 3:
                       system("clear");
                       termina_gioco ();
                 default:
                       break;
         }
    }while( imp >3|| imp <1);
}
int main(){
  intro();
  menu();
}
