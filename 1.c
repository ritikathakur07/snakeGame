#include<stdio.h>
#include<stdlib.h>//for rand()
#include<conio.h>//for kbhit()
#include<windows.h>//for color schemes
int width=20,height=20,gameOver;
int cas;
int x,y;					//set coordinates for the head of the snake
int fruitX,fruitY,score;	//sets the coordinates for the food of the snake
int flag;
int tailX[100], tailY[100];
int CountTail=0; 
char c;
int prevX, prevY, prev2X, prev2Y; //to increase the length of snake
void setup()				//to set the position of food and snake
{
	system("COLOR 3F");
	prevX=tailX[0];
	prevY=tailY[0];
gameOver=0;					//game continues to proceed. When it is 1, then the game gets over
x=width/2;					//sets the x coordinate of snake in the middle=10
y=height/2;					//sets the y coordinate of snake in the middle=10

label1:
fruitX=rand()%20;			//generates x co-ordinate for food
if(fruitX==0)
	goto label1;

label2:
fruitY=rand()%20;			//generates y co-ordinate for food
if(fruitY==0)
	goto label2;
score=0;					//sets intial score=0
}
void draw()					//to draw the boundary/field of the game
{
	int i,j,k;
	
	system("cls");		//clears screen
	//system("COLOR F0");
	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			if(i==0||i==height-1||j==0||j==width-1)
				printf("*");
			else
			{
				if(i==fruitX && j==fruitY)
					printf("F");
				else if(i==x && y==j)		//if i=10,j=10 then display snake
					printf("O");
				else
				{
					int ch=0; // counter to keep the boundary intact
					// ordered pair of (i,j) 
					for(k=0;k<CountTail;k++)
					{
						if(i==tailX[k] &&j==tailY[k])
						{
							printf("o");
							ch=1;
						}
					}	
					if(ch==0)	
						printf(" ");
				}
			}
		}
		printf("\n");
	}
	printf("SCORE = %d", score);
}//end of draw
void input()	//determines which key is pressed by keyboard
{
	if(kbhit())		//returns non zero value if a key is pressed
	{
		switch(getch())		//catches the character pressed by user
		{
			case 'a':flag=1;
				break;
			case 's': flag=2;
				break;
			case 'w': flag=3;
				break;
			case 'z':flag=4;
				break;
			case 'n':
				gameOver=1;			//game gets over
				break;
		}
	}
}
void MakeLogic()	//moves the snake according to flag value
{
	
	int i;
	prevX=tailX[0];
	prevY=tailY[0];
	tailX[0]=x;
	tailY[0]=y;
//appending snake 
	for(i=1;i<CountTail;i++)
	{
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(flag)
	{
		case 1:
			y--;	//when a is pressed moves snake to left
			break;
		case 2:
			y++;        //when s is pressed ,moves snake to right
			break;
		case 3:
			x--;            //when w is pressed,moves snake to top
			break;
		case 4:
			x++;            //when s is pressed, moves snake to bottom
			break;
		default:
			break;
	}
	if(x<0||x>20||y<0||y>20)		//if snake reaches beyond the boundary,game gets over 
		gameOver=1;
	for(i=0;i<CountTail;i++)
	{
		if(x==tailX[i] && y==tailY[i])
			gameOver=1;
	}	
	if(x==fruitX && y==fruitY)		//if both of their co=ordinates match
	{
	label3:
	fruitX=rand()%20;			//generates the random position for food
	if(fruitX==0)
		goto label3;
	label4:
	fruitY=rand()%20;			
	if(fruitY==0)
		goto label4;
	score+=10;		//increments score when snake eats the food	
	CountTail++;
	}
}
void displayFile()
{
	system("cls");
	system("COLOR F2");
	FILE *fp2;
	char buff[255];
	char c;
	fflush(stdin);
	fp2=fopen("file5.txt","r");/*read only mode*/
	if(fp2==NULL)
	{
		printf("Error in opening file");
	}
	while((c=getc(fp2))!=EOF)
	{
		printf("\t\t\t");
	do
	{
		printf("%c",c);
	}while((c=getc(fp2))!='\n');
	printf("\n\t\n");
	}
	fclose(fp2);
	fflush(stdin);
}
void rules()
{
	printf("\t___________________________________________________________\n");
	printf("\t\t\tR U L E S   F O R    T H E    G A M E \n\n");
	printf("\t___________________________________________________________\n\n");
	printf("\t1. If the snake touches/reaches the boundary,the game exits.\n\n");
	printf("\t2. If snakes bites itself or touches its tail,the game exits.\n\n");
	printf("\t3. A user can play multiple times until at any case\n\n\tthe game gets exits, by entering his/her name again!\n\n");
	printf("\t\t\tGOOD LUCK WITH THE GAME!!\n\n");
}
int play()
{
//	label7:	
	int m,n,a;
	char name[50];
	puts("ENJOY YOUR GAME!!\n");
	printf("Enter your name : \n");
	scanf("%s",name);
	setup();
	CountTail=0;//will be reset for each player
	while(!gameOver)	//if gameover=0 then the game proceeds otherwise when 1, exits 
	{
		draw();
		input();
		MakeLogic();
	//slows down the movement of snake as the 2 loops processes
		for(m=0;m<1000;m++)
			for(n=0;n<10000;n++);
		for(m=0;m<1000;m++)
			for(n=0;n<10000;n++);
	}//end of while
	//storing score in file
	FILE *fp;
	fflush(stdin);
	fp=fopen("file5.txt","a");/*output file*/
	if(fp==NULL)
	{
		printf("Error in opening file");
	}
	fprintf(fp,"Player Name: %s = %d\n",name,score);
	fclose(fp);
	printf("\nPress 'Y' to continue again,");
	printf("\n'n' to Quit: ");
	fflush(stdin);
	scanf("%c",&c);		
	if(c=='y'||c=='Y')
		return 1;
}
int main_menu()
{
	int d,counter;
	if(counter==20)
		system("cls");
	do
	{
		if(cas==4)
		break;
	printf("\t\t________________________________________________\n");
	printf("\t\t\t\tM A I N   M E N U\n\n");
	printf("\t\t________________________________________________\n");
	printf("\t\t\t\t1. Play the Game\n\n");
	printf("\t\t\t\t2. Rules for the Game\n\n");
	printf("\t\t\t\t3. Scoreboard\n\n");
	printf("\t\t\t\t4. Quit\n");
	printf("\t\t-------------------------------------------------\n\n\n");
	
	scanf("%d",&cas);
	fflush(stdin);
	switch(cas)
	{
		case 1:
			d=play();
			if(d==1)
			main_menu();
			break;
		case 2:
			rules();	
			break;
		case 3:
			displayFile();
			break;
		case 4:
			break;
		default:
			printf("\nEnter a Valid choice!\n");
			break;
	}
	counter=20;
	if(cas==4)
	break;
	}while(cas!=4);
	if(cas==4)
	return 0;
	//goto label7;
}
void home()
{
	system("COLOR F5");
	printf("\t\t -------------------------------------------------\n");
	printf("\t\t ________________________________________________\n");
	printf("\t\t      		 Presented by:                    \n");
	printf("\t\t ________________________________________________\n");
	printf("\t\t |     		  DIXITA DEY                  	|\n");
	printf("\t\t |             	     AND                 	|\n");
	printf("\t\t |   		 RITIKA THAKUR                  |\n");
	printf("\t\t |______________________________________________|\n");
	printf("\t\t -------------------------------------------------\n\n");	
}
int main()
{
	home();//display name
	main_menu();//menu of the game
	return 0;	
}
