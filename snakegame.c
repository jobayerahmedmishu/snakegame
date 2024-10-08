#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<ctype.h>

void set_up();
void draw();
void logic();
void main_interface();
void print_highscore();
void play();
void highscore_update();
void highscore_initialize();
void help();
void settings();
void navigation();
void snake_history_initialize();
void input_history();
void print_history();
void reset_highscore();
void tail_size_update();
void tail_initialize();

int i, j,k=0,len=0, height = 30, width = 30,targetx,targety;
float speed = 1;
int gameover, score;
int x, y, fruitx, fruity, flag=3;
char* tail;

void main()
{
    highscore_initialize();
    snake_history_initialize();

    char c;

    while(1)
    {
        system("cls");
        navigation();
        main_interface();

        printf("  --> ");
        fflush(stdin);
        scanf(" %c",&c);
        fflush(stdin);

        if(c=='1')
        {
            play();
        }
        else if(c=='2')
        {
            print_highscore();
        }
        else if(c=='3')
        {
            help();
        }
        else if(c=='4')
        {
            settings();
        }
        else if(c=='e')
        {
            return;
        }
        else if(c=='5')
        {
            print_history();
        }
        else
        {
            system("cls");
            printf("\tINVALID INPUT\n\n");
        }
    }

}



void setup()
{
    srand(time(NULL));
	gameover = 0;

	x = height / 2;
	y = width / 2;
	flag = 0;

    do
    {
        fruitx = rand() % 20;

    }while(fruitx <= 0||fruitx==x||fruitx>=height-1);

    do
    {
        fruity = rand() % 20;

    }while(fruity == 0||fruity==y||fruity>=width-1);

	score = 0;
}

void draw()
{
	system("cls");
	printf("Score : %d\n",score);

	if (speed==1)
            printf("MODE : EASY\n\n");
    else
            printf("MODE : HARD\n\n");

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (i == 0 || i == width - 1
				|| j == 0
				|| j == height - 1) {
				printf("#");
			}
			else {
				if (i == x && j == y && flag==0)
					printf(">");
                else if(i==x&&j==y&&flag==1)
                    printf("<");
                else if(i==x&&j==y&&flag==2)
                    printf("v");
                else if(i==x&&j==y&&flag==3)
                    printf(">");
                else if(i==x&&j==y&&flag==4)
                    printf("^");
				else if (i == fruitx
						&& j == fruity)
					printf("O");
                else if(i==x&&j>=y-len&&j<=y-1&&flag==3)
                    printf("-");
                else if(flag==1&&i==x&&j<=y+len&&j>=y+1)
                    printf("-");
                else if(flag==2&&j==y&&i<=x-1&&i>=x-len)
                    printf("|");
                else if(flag==4&&j==y&&i>=x+1&&i<=x+len)
                    printf("|");
				else
					printf(" ");
			}
		}
		printf("\n");
	}

}

void input()
{
	if (kbhit()) {
		switch (tolower(getch()))
		{
            case 'a':
                flag = 1;
                targetx=x;
                targety=y;
                break;
            case 's':
                flag = 2;
                targetx=x;
                targety=y;
                break;
            case 'd':
                flag = 3;
                targetx=x;
                targety=y;
                break;
            case 'w':
                flag = 4;
                targetx=x;
                targety=y;
                break;
            case 'h':
                gameover = 1;
                break;
		}
	}
}


void logic()
{
	sleep(speed);
	switch (flag)
	{
        case 1:
            y--;
            break;
        case 2:
            x++;
            break;
        case 3:
            y++;
            break;
        case 4:
            x--;
            break;
        default:
            break;
	}

	if (x <= 0 || x >= height || y <= 0 || y >= width)
		gameover = 1;

	if (x == fruitx && y == fruity)
    {
        do
        {
            fruitx = rand() % 20;

        }while(fruitx <= 0||fruitx==x||fruitx>=height-1);

        do
        {
            fruity = rand() % 20;

        }while(fruity <= 0||fruity==y||fruity>=width-1);

            score += 10;
            len++;
	}
}

void main_interface()
{
    printf("1 --> play\n");
    printf("2 --> Highscore\n");
    printf("3 --> Help\n");
    printf("4 --> Settings\n");
    printf("5 --> History\n");
    return;
}

void play()
{
    char c;

    do
    {
        setup();

        while (gameover==0)
        {
            draw();
            input();
            logic();
        }

        highscore_update();
        input_history();

        while(1)
        {
            printf("\n 1 --> play again .\n   --> ");
            fflush(stdin);
            scanf(" %c",&c);
            fflush(stdin);
            c=tolower(c);
            if(c=='h')
            {
                system("cls");
                return;
            }
            else if(c=='e')
            {
                exit(0);
            }
            else if(c=='1')
            {
                break;
            }
            else
            {
                printf("\tINVALID INPUT\n");
            }
        }

    }while(tolower(c)=='1');
}

void print_highscore()
{
    char c;
    system("cls");

    printf("\tHIGHSCORE : ");

    FILE *file = fopen("highscore.txt","r");

    while((c=fgetc(file))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");
    fclose(file);

    while(1)
    {
        printf(" 1 --> reset highscore \n   --> ");
        fflush(stdin);
        scanf(" %c",&c);
        fflush(stdin);
        if(tolower(c)=='h')
        {
            system("cls");
            return;
        }
        else if(tolower(c)=='e')
        {
            exit(0);
        }
        else if(tolower(c)=='1')
        {
            reset_highscore();
            return;
        }
    }

    return;
}

void highscore_update()
{
    FILE* file = fopen("highscore.txt","r");
    char c;
    char* tmp=malloc(sizeof(char));
    int i = 0;

    while((c=fgetc(file))!=EOF)
    {
        tmp[i]=c;
        i++;
        tmp = realloc(tmp,sizeof(char));
    }
    tmp[i]='\0';

    int highscore = atoi(tmp);

    if(score>highscore)
    {
        printf("\n\n\tYAYY!! YOU HAVE SCORED THE HIGHEST POINTS\n\n");
        fclose(file);
        FILE* file = fopen("highscore.txt","w");
        fprintf(file,"%d",score);
        fclose(file);
    }
    else
    {
        fclose(file);
    }
    return;
}

void highscore_initialize()
{
    FILE* file = fopen("highscore.txt","r");
    if(file==NULL)
    {
        fclose(file);
        FILE*file= fopen("highscore.txt","w");
        fprintf(file,"0");
        fclose(file);
    }
    else
    {
        fclose(file);
        return;
    }
}

void help()
{
    char c;
    system("cls");
    printf("Use 'a' , 's' , 'd' , 'w' to move the snake left, down, right and upwards.\n");
    printf("Eat the fruits represented as '*' within the box to increase your score.\n");
    printf("Avoid hitting the walls of the box. If you do it will result in a game over.\n");
    printf("Press 'h' to go back to the main interface.\n");
    fflush(stdin);
    while(1)
    {
        printf("  --> ");
        scanf("%c",&c);
        fflush(stdin);
        if(c=='h')
        {
            return;
        }
        else if(c=='e')
        {
            exit(0);
        }
        else
        {
            printf("Invalid input\n");
        }
    }

}

void settings()
{
    char c;

    system("cls");

    while(1)
    {
        printf("1 --> EASY MODE\n");
        printf("2 --> HARD MODE\n");
        fflush(stdin);
        printf("  --> ");
        scanf(" %c",&c);
        fflush(stdin);

        if(c=='1')
        {
            speed=1;
            return;
        }
        else if(c=='2')
        {
            speed=0.01;
            return;
        }
        else if(tolower(c)=='h')
        {
            return;
        }
        else if(tolower(c)=='e')
        {
            exit(0);
        }
        else
        {
            system("cls");
            printf("INVALID INPUT\n");
        }
    }

}

void navigation()
{
    printf("\tNAVIGATION:\n\tENTER 1,2,3... TO CHOOSE ANY OPTION\n\t'e' --> exit\n\t'h' --> home\n\n");
}

void snake_history_initialize()
{
    FILE* file = fopen("snakehistory.txt","r");
    if(file == NULL)
    {
        fclose(file);
        FILE* file = fopen("snakehistory.txt","w");
        fclose(file);
        return;
    }
    else
    {
        fclose(file);
        return;
    }
}

void input_history()
{
    time_t currentTime = time(NULL);

    struct tm *localTime = localtime(&currentTime);

    char timeString[100];
    strftime(timeString, sizeof(timeString), "%H:%M:%S DATE:%d-%m-%Y", localTime);

    FILE* file = fopen("snakehistory.txt","a");
    if(speed==1)
        fprintf(file,"TIME:%s MODE:EASY SCORE:%d\n",timeString,score);
    else
        fprintf(file,"TIME:%s MODE:HARD SCORE:%d\n",timeString,score);

    fclose(file);
}

void print_history()
{
    char r;
    system("cls");

    FILE*file=fopen("snakehistory.txt","r");
    char c;
    while(( c=fgetc(file)) !=EOF)
    {
        printf("%c",c);
    }
    fclose(file);

    fflush(stdin);

    while(1)
    {
        printf("\v1 -> DELETE HISTORY \n  -> ");
        fflush(stdin);
        scanf(" %c",&r);
        fflush(stdin);
        if(tolower(r)=='h')
        {
            return;
        }
        else if(tolower(r)=='e')
        {
            exit(0);
        }
        else if(r=='1')
        {
            FILE* file = fopen("snakehistory.txt","w");
            fclose(file);
            return;
        }
        else
        {
            printf("INVALID INPUT\n");
        }
    }
}

void reset_highscore()
{
    FILE*file = fopen("highscore.txt","w");
    fprintf(file,"0");
    fclose(file);
}

