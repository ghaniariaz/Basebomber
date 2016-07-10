/*
* BASE BOMBER: A Simple Computer Game
* Created by Fauzan Mirza, 26/12/2011
* Assignment solution by: <Ghania Riaz> <SAT nat 110>
* Date: 1st January 2012.
*/

#include <stdio.h>  /* for printf() and file I/O functions */  
#include<time.h>    /* for date and time manipulation operations */
#include<stdlib.h>  /* for rand() function */
#include<math.h>   /* for sqrt() function */
#include<ctype.h>   /* for toupper() function */
#include<string.h>  /*for string handling */

#define HIGHSCOREFILE "hiscore.bin"
#define GRIDSIZE_X 150
#define GRIDSIZE_Y 150
#define MAXBOMBS 10   /*number of bombs*/
#define TIMELIMIT 2   /*defining the time limi that is 2 mins*/
#define MAXBUFFLEN 50
#define MAXNAMELEN 50
#define CHEATCODE "cheater"


struct coordinates {
	int x;
	int y;
				  };


struct player  { 
	               char name[100]  ; 
	               unsigned long score ;
			   };

void get_coordinates(struct coordinates *guess)
{ 
	char buffer[MAXBUFFLEN];
	enum { False, True } outofrange ;
	
do 
{



printf ("Enter bomb coordinates: ");

fgets (buffer, MAXBUFFLEN, stdin); 

sscanf (buffer, "(%u,%u)", &guess->x, &guess->y);


if (guess->x>149)

	outofrange = True; 

else if (guess->y>149)

	outofrange = True;
else

	outofrange = False;


if (outofrange == True)
{
printf ("Those coordinates are not valid.\n"); 
printf ("Please enter some valid coordinates like this: (%u,%u)\n", rand() %150, rand()%150);
printf ("The top left corner of the grid is (0,0)\n\tand the bottom right corner is (%u,%u).\n", GRIDSIZE_X-1, GRIDSIZE_Y-1);
}

}
while (outofrange == True);
}
int main()
{
	struct coordinates target, guess; 
	struct player player, highscore;
	char buffer[MAXBUFFLEN];
	double distance, dx, dy;
	int bombs , starttime, timeleft, timelimit;
	FILE *scorefile;
	int i;

printf ("************************************\n");
printf ("***                              ***\n");
printf ("***    Welcome to BASE BOMBER    ***\n");
printf ("***                              ***\n");
printf ("************************************\n\n\n");



srand(time(NULL));

target.x = rand() % GRIDSIZE_X;
target.y = rand() % GRIDSIZE_Y;

printf("%u,%u\n",target.x,target.y);

bombs=MAXBOMBS;



printf ("Please tell me your name, Captain.\n");
printf ("Your name: ");

fgets (player.name, MAXNAMELEN, stdin);


for(i=0; i<sizeof(player.name);i++)

	if (player.name[i] == '\n')
		player.name[i]=0;
		


player.name[0] = toupper(player.name[0]);

printf ("\nNice to meet you, Captain %s.\n",player.name);

player.score = 0;



highscore.score = 0; 
scorefile = fopen(HIGHSCOREFILE,"r");

 

if (scorefile!=NULL)
{ 
	if (fread (&highscore, sizeof(struct player), 1, scorefile) != 1)
	highscore.score = 0;
	fclose (scorefile);
}


printf ("\nYour mission:\n");
printf (" You have %u minutes to locate and bomb the target base.\n", TIMELIMIT);
printf (" The target base is located on a %u x %u grid.\n", GRIDSIZE_X, GRIDSIZE_Y);
printf (" We do not know where exactly the target base is, but we can intercept their\n\tradio communications.\n");
printf (" Every time a bomb is dropped, they report the distance of bomb from their\n\tbase to their HQ by radio.\n");
printf (" We will intercept and tell you this information so that you can decide\n\twhere to drop the next bomb.\n");
printf (" Enter the (x,y) coordinates of the target like this: (%u,%u)\n", rand()%GRIDSIZE_X, rand()%GRIDSIZE_Y);
printf (" We only have %u bombs and each bomb is expensive, so try not to waste bombs.\n", bombs);
printf (" Good luck!\n\n");
printf ("Press ENTER to start the mission. The timer will start immediately.\n");

   fgets(buffer, MAXBUFFLEN, stdin);


       starttime = time(NULL);
       timelimit = starttime+ 120 ;

 

if (strcmp (CHEATCODE, buffer) == 0)
	printf ("Good news! Our spy just reported that the target base is at (%u,%u).\n\n", target.x, target.y);


while (1)
{

	
	timeleft = timelimit - time(NULL); 
	printf ("Countdown until mission ends: %u minutes", timeleft/60); 

		if (timeleft%60!=0)

	printf (", %u seconds.\n", timeleft%60);

		else
	printf (" exactly.\n");



	printf ("There %s %u bomb%s left.\n", bombs >1 ? "are" :"is", bombs, bombs>1 ? "s" : "");

	
get_coordinates(&guess);


	timeleft = timelimit - time(NULL);
if (timeleft <= 0)
{ 
	printf ("\nSorry, Captain %s, you ran out of time!\n", player.name);
printf ("Mission failed.\n");
break;
}


dx = (double)target.x-(double)guess.x; 
dy=(double)target.y-(double)guess.y;
dx=dx*dx;
dy=dy*dy;
distance=dx+dy;
distance = sqrt (distance);


if (distance==0)
{
	printf ("\nCongratulations, Captain %s! You successfully bombed the target base!\n", player.name);
	printf ("Mission accomplished!\n");



       player.score = timeleft + 50*bombs; 
       break;
}

else

{ 
	printf ("The bomb was dropped at (%u,%u)\n", guess.x, guess.y);
    printf ("The distance of the bomb from the target base was %lf \n\n", distance);
}


   bombs--;
if (bombs == 0)
{ 
	printf ("Sorry, Captain %s, there are no more bombs left!\n", player.name);

	printf ("Mission failed.\n"); 

    break;
}

}


	printf ("\n You scored %u points!\n", player.score);

 

if (player.score<highscore.score)

	printf ("The highest score earned was %u points by Major %s.\n",highscore.score, highscore.name);


if (player.score>highscore.score && strcmp (buffer, CHEATCODE) != 0)
{
	printf ("You have beaten the highest score and earned a promotion!\n"); 
	printf ("Well done, Major %s!\n", player.name);



	scorefile = fopen(HIGHSCOREFILE, "w");


if (scorefile != NULL)
{ 
	fwrite(&player, sizeof(struct player),1,scorefile);
	fclose (scorefile);
}
}
return (0);
}
