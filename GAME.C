#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>

typedef struct	pp	{
	int nx1;
	int ny1;
	int nx2;
	int ny2;
	int cell1;
	int cell2;
	int used;
	struct pp *next;
}dctpoly;

void init();
void setcursorpos();
void funinwin();
dctpoly *rightcused(int ,int );
void shwds(int ,int );
void reczerotest(int ,int );
int password();
void initialise();
int investigate(int );
void nogenerator(void);
int val(int ,int );
void fillzero(void);
int sumad(int ,int );
int menu(int *,int *,char *);
void showmouseptr();
void drawface(int );
int initmouce();
void drawbox(int );
int dctifwin(int ,int ,int );
void startplay();
void drawflag(dctpoly *,int );
void hidemouseptr();
void esmilewin(int ,int );
void esmilelose(int,int );
void drawminibox(int,int,int,int);
void assinvaluetopoly();
int filling_sp(int ,int );
dctpoly *createpolynode(int ,int ,dctpoly *,int,int,int,int);
dctpoly *colorfillpoly(dctpoly *,int ,int );

dctpoly *head=NULL;
union REGS i,o;
int norc=10,mineno=6;                              /* no. of row or column */
int mine_array[25][25];                   /* main array */

int main()
{
	int noofgrid=10,mine_no=6;
	char _continue,msg[40],test='e';
	time_t t;
	dctpoly *genes;
	init();
	initmouce();
	agnply:
	menu(&noofgrid,&mine_no,&test);
	showmouseptr();setcursorpos();
	norc=noofgrid;
	mineno=mine_no;          //mineno & norc is 4 array;
	cleardevice();
	showmouseptr();
	setcolor(15);
	drawbox(noofgrid);
	drawface(1);
	assinvaluetopoly();
	startplay();
	getch();
	agnply1:
	{
		dctpoly *xxx=head;
		genes=xxx;
		while(genes!=NULL)	{
			free(genes);
			genes=xxx->next;
			xxx=xxx->next;
		}
	}
	cleardevice();
	goto agnply;
}

int menu(int *grid,int *level,char *test)
{
	char choice,msg[100];
	int no,ch,crtpass;
	setcolor(15);
	agchoice:
	fflush(stdin);
	cleardevice();
	sprintf(msg,"MINESWEEPER",2);outtextxy(220,5,msg);
	setcolor(8);
	sprintf(msg," lay");outtextxy(240,20,msg);
	sprintf(msg,"Leve ");outtextxy(240,40,msg);
	sprintf(msg," ules");outtextxy(239,60,msg);
	sprintf(msg,"Cre its");outtextxy(230,80,msg);
	sprintf(msg,"Ins ruction");outtextxy(223,100,msg);
	sprintf(msg,"Box  o");outtextxy(238,120,msg);
	sprintf(msg,"E it");outtextxy(245,140,msg);
	setcolor(15);
	sprintf(msg,"P",15);outtextxy(240,20,msg);
	sprintf(msg,"l",15);outtextxy(270,40,msg);
	sprintf(msg,"R",15);outtextxy(239,60,msg);
	sprintf(msg,"   d");outtextxy(230,80,msg);
	sprintf(msg,"   t");outtextxy(223,100,msg);
	sprintf(msg,"    N");outtextxy(238,120,msg);
	sprintf(msg," x");outtextxy(245,140,msg);
		setcolor(15);
		sprintf(msg,"BOX NO: ");outtextxy(10,420,msg);
		setcolor(8);
		sprintf(msg,"%d",*grid);outtextxy(70,420,msg);
	switch(*test)	{
		case 'e':
			setcolor(15);
			sprintf(msg,"LEVEL:");outtextxy(10,400,msg);
			setcolor(8);
			sprintf(msg,"Easy");outtextxy(65,400,msg);
			break;
		case 'm':
			setcolor(15);
			sprintf(msg,"LEVEL:");outtextxy(10,400,msg);
			setcolor(8);
			sprintf(msg,"Medium");outtextxy(65,400,msg);
			break;
		case 'h':
			setcolor(15);
			sprintf(msg,"LEVEL:");outtextxy(10,400,msg);
			setcolor(8);
			sprintf(msg,"Hard");outtextxy(65,400,msg);
			break;
	}
	setcolor(15);
	wrongentry1:
	choice=getch();
	switch(choice)	{
		case 'l':
			cleardevice();
			sprintf(msg,"e :Easy");
			outtextxy(10,400,msg);
			sprintf(msg,"m :Medium");
			outtextxy(10,410,msg);
			sprintf(msg,"h :Hard");
			outtextxy(10,420,msg);
			sprintf(msg,"Enter Level:");
			outtextxy(10,430,msg);
			wrongentry2:
			*test=getch();
			if(*test!='e' && *test!='m' && *test!='h')
				goto wrongentry2;
			cleardevice();
			goto agchoice;
		case 'p':
			if(*test=='e' && *grid>=17)
				*level=(*grid*2)+20;
			if(*test=='m' || *test=='M')
				*level=(*grid*3);
			if(*test=='h' || *test=='H')
				*level=(*grid*4);
			else
				*level=(*grid*2);
			break;
		case 'r':
			cleardevice();
			sprintf(msg,"1.You Can Uncover a Square By Left Clicking It.");
			outtextxy(2,5,msg);
			sprintf(msg,"2.If U uncover A Mine U Will Lose Game.");
			outtextxy(2,20,msg);
			sprintf(msg,"3.If a number appers on a sqare it indicates how many mines are in eight squre that surrounds the numbered one.");
			outtextxy(2,35,msg);
			sprintf(msg,"4.To mark a squre you suspect contains a mine, right click it.");
			outtextxy(2,50,msg);
			sprintf(msg,"5.Game level and number of squre are user input.");
			outtextxy(2,65,msg);
			sprintf(msg,"press any key to return to main menu.....");
			outtextxy(2,440,msg);
			getch();
			goto agchoice;
		case 'd':
			cleardevice();
			setcolor(15);
			sprintf(msg,"Programer:");
			outtextxy(2,5,msg);
			sprintf(msg,"Special Thanks:");
			outtextxy(2,65,msg);
			sprintf(msg,"Idea From:");
			outtextxy(2,85,msg);
			sprintf(msg,"E mail ID:");
			outtextxy(2,105,msg);

			setcolor(8);
			sprintf(msg,"    Debdipta Ghosh");
			outtextxy(92,5,msg);
			sprintf(msg,"    Electronics & Communication Dept.");
			outtextxy(92,25,msg);
			sprintf(msg,"    Asansol Engineering College");
			outtextxy(92,45,msg);
			sprintf(msg,"Rajat Kanti Sarkar");
			outtextxy(122,65,msg);
			//sprintf(msg,"");
			//outtextxy(122,65,msg);
			sprintf(msg,"Microsoft Minesweeper Game");
			outtextxy(122,85,msg);
			sprintf(msg,"debdipta_itu@yahoo.co.in");
			outtextxy(122,105,msg);
			getch();
			goto agchoice;
		case 't':
			cleardevice();
			setcolor(15);
			sprintf(msg,"This Progran is Written In C language.");
			outtextxy(3,10,msg);
			sprintf(msg,"To Get Full Algorithm & Part of Program Contact in E-MAIL.");
			outtextxy(3,40,msg);
			getch();
			goto agchoice;
		case 'x':
			cleardevice();
			closegraph();
			restorecrtmode();
			exit(0);
		case 'n':
			cleardevice();
			sprintf(msg,"Up & Down Key to Increase and Decrease");
			outtextxy(2,420,msg);
			sprintf(msg,"Spacebar to exit........");
			outtextxy(2,430,msg);
			while(1)	{
				gotoxy(35,15);printf("Box: %d",*grid);
				agn:
				ch=getkey();
				if(ch!=80 && ch!=72 && ch!=57)
					goto agn;
				if(ch==72)
					*grid=*grid+1;
				if(ch==80)
					*grid=*grid-1;
				if(*grid<=10)
					*grid=10;
				if(*grid>=25)
					*grid=25;
				if(ch==57)
					break;
			}
			cleardevice();
			goto agchoice;
		default:
			goto wrongentry1;
	}
	return 0;
}

int initmouce()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return o.x.ax;
}

void showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}

getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
	return 0;
}
void setcursorpos()
{
	i.x.ax=4;
	int86(0x33,&i,&o);
	o.x.ax=1;o.x.bx=2;
}
void init()
{
   int gdriver = DETECT, gmode, errorcode;
   /*registerfarbgidriver(EGAVGA_driver_far);
   registerfarbgifont(sansserif_font_far);
   registerfarbgifont(small_font_far);
   registerfarbgifont(gothic_font_far);
   registerfarbgifont(triplex_font_far);*/
   initgraph(&gdriver, &gmode,"c:\\tc\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)	{
	  printf("Graphics error: %s\n", grapherrormsg(errorcode));
	  printf("Press any key to halt:");
	  getch();
	  exit(1);
   }
}

void drawbox(int nobox)
{
	int i,midx,midy,tempx=0,tempy=0,j;
	dctpoly *pre;
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	midx-=7*nobox;midy-=7*nobox;
	setcolor(7);
	setcolor(8);
	for(j=0;j<3;j++)
		line(midx+tempx-5,midy+tempy-5+j,midx+tempx+15*nobox,midy+tempy-5+j);j=1;
	for(i=0;i<3;i++)
		line(midx+tempx-5+i,midy+tempy-5,midx+tempx-5+i,midy+tempy+15*nobox);
	setcolor(15);i=0;
	for(j=0;j<3;j++)
		line(midx+tempx-5-i--,midy+tempy+15*nobox-j,midx+tempx+15*nobox-i-2,midy+tempy+15*nobox-j);
	j=0;
	for(i=0;i<3;i++)
		line(midx+tempx+15*nobox-i,midy+tempy-5-j--,midx+tempx+15*nobox-i,midy+tempy+15*nobox-j-2);
	{
		tempx=0;tempy=0;
		for(j=0;j<nobox;j++)	{
			for(i=0;i<nobox;i++)	{
				setcolor(15);
				line(midx+tempx-1,midy+tempy-1,midx+tempx+10,midy+tempy-1);
				line(midx+tempx-2,midy+tempy-2,midx+tempx+10,midy+tempy-2);
				line(midx+tempx-2,midy+tempy-2,midx+tempx-2,midy+tempy+12);
				line(midx+tempx-1,midy+tempy-1,midx+tempx-1,midy+tempy+11);
				setcolor(8);
				line(midx+tempx-2,midy+tempy+12,midx+tempx+12,midy+tempy+12);
				line(midx+tempx-1,midy+tempy+11,midx+tempx+12,midy+tempy+11);
				line(midx+tempx+12,midy+tempy-2,midx+tempx+12,midy+tempy+12);
				line(midx+tempx+11,midy+tempy-2,midx+tempx+11,midy+tempy+12);
				pre=createpolynode(j,i,pre,midx+tempx,midy+tempy,midx+tempx+10,midy+tempy+10);
				colorfillpoly(pre,7,-1);
				tempx+=10;
				midx+=5;
			}
			midx-=5*nobox;
			tempx-=10*nobox;
			tempy+=10;
			midy+=5;
		}
	}
}

dctpoly *createpolynode(int x,int y,dctpoly *pre,int x1,int y1,int x2,int y2)
{
	dctpoly *init;int i;
	time_t g_num;
	init=(dctpoly*) malloc(sizeof(dctpoly));
	init->nx1=x1;
	init->ny1=y1;
	init->nx2=x2;
	init->ny2=y2;
	init->used=0;
	init->cell1=x;
	init->cell2=y;
	init->next=NULL;
	if(head==NULL)	{
		head=init;
		pre=init;
	}
	else
		pre->next=init;
	pre=init;
	return pre;
}

dctpoly *colorfillpoly(dctpoly *ranhead,int color,int drwbomb)
{
	int poly[10],x=(ranhead->nx1+ranhead->nx2)/2,y=(ranhead->ny1+ranhead->ny2)/2;
	char msg[5];
	if(drwbomb==1)	{
		poly[0]=(ranhead->nx1)-2;
		poly[1]=(ranhead->ny1)-2;

		poly[2]=(ranhead->nx2)+1;
		poly[3]=(ranhead->ny1-2);

		poly[4]=(ranhead->nx2)+1;
		poly[5]=(ranhead->ny2)+2;

		poly[6]=(ranhead->nx1)-2;
		poly[7]=(ranhead->ny2)+2;

		poly[8]=poly[0];
		poly[9]=poly[1];

		setfillstyle(SOLID_FILL,color);
		fillpoly(5,poly);
		setcolor(0);
		if(mine_array[ranhead->cell1][ranhead->cell2]!=0)	{
			if(mine_array[ranhead->cell1][ranhead->cell2]==1)
			setcolor(1);
			if(mine_array[ranhead->cell1][ranhead->cell2]==2)
				setcolor(6);
			if(mine_array[ranhead->cell1][ranhead->cell2]==3)
				setcolor(2);
			if(mine_array[ranhead->cell1][ranhead->cell2]==4)
				setcolor(YELLOW);
			sprintf(msg,"%d",mine_array[ranhead->cell1][ranhead->cell2]);
			outtextxy(x-3,y-3,msg);
		}
		return 0;
	}
	setcolor(color);
	poly[0]=(ranhead->nx1);
	poly[1]=(ranhead->ny1);

	poly[2]=(ranhead->nx2);
	poly[3]=(ranhead->ny1);

	poly[4]=(ranhead->nx2);
	poly[5]=(ranhead->ny2);

	poly[6]=(ranhead->nx1);
	poly[7]=(ranhead->ny2);

	poly[8]=poly[0];
	poly[9]=poly[1];

	setfillstyle(SOLID_FILL,color);
	fillpoly(5,poly);

	if(drwbomb==1)	{
		poly[0]=(ranhead->nx1)-2;
		poly[1]=(ranhead->ny1);

		poly[2]=(ranhead->nx2)-2;
		poly[3]=(ranhead->ny1)+2;

		poly[4]=(ranhead->nx2)+2;
		poly[5]=(ranhead->ny2)+2;

		poly[6]=(ranhead->nx1)+2;
		poly[7]=(ranhead->ny2)-2;

		poly[8]=poly[0];
		poly[9]=poly[1];

		setfillstyle(SOLID_FILL,color);
		fillpoly(5,poly);
		if(mine_array[ranhead->cell1][ranhead->cell2]==1)
			setcolor(1);
		if(mine_array[ranhead->cell1][ranhead->cell2]==2)
			setcolor(6);
		if(mine_array[ranhead->cell1][ranhead->cell2]==3)
			setcolor(2);
		if(mine_array[ranhead->cell1][ranhead->cell2]==4)
			setcolor(13);
		sprintf(msg,"%d",mine_array[ranhead->cell1][ranhead->cell2]);
		outtextxy(x-3,y-3,msg);
	}

	if(drwbomb==0)	{
		x=(ranhead->nx1+ranhead->nx2)/2;
		y=(ranhead->ny1+ranhead->ny2)/2;
		setcolor(0);
		ellipse(x,y,0,360,4,4);
		setfillstyle(SOLID_FILL,0);
		fillellipse(x,y,4,4);
		setcolor(15);
		ellipse(x-1,y-1,0,360,1,1);
		setfillstyle(SOLID_FILL,15);
		fillellipse(x-1,y-1,1,1);
	}
	setcolor(15);
	return 0;
}

void startplay()
{
	int dctwin=1,button,xpos,ypos;
	char msg[20];
	dctpoly *temp=head;
	while(dctwin==1 && dctifrealwin()==-1)	{
		setcolor(0);
		showmouseptr();
		getmousepos(&button,&xpos,&ypos);
		if(button==1 || button==2)	{
			hidemouseptr();
			dctwin=dctifwin(xpos,ypos,button);
			if(dctwin==0 && dctifrealwin()==-1)	{                    /*lose condition*/
				while(temp!=NULL)	{
					if(mine_array[temp->cell1][temp->cell2]==-1 && temp->used==2)
						colorfillpoly(temp,7,dctwin);
					if(mine_array[temp->cell1][temp->cell2]==-1 && temp->used!=2)
						colorfillpoly(temp,4,dctwin);
					temp=temp->next;
				}
				{
					char msg[45];
					sprintf(msg,"Press Any Key To Go To Main Menu....");
					outtextxy(2,450,msg);
				}
				return ;
			}
		}
	}
}

int dctifwin(int xpos,int ypos,int button)
{
	dctpoly *temp=head;
	int dctgame,simple=1;
	while(temp!=NULL)	{
		if(xpos>=temp->nx1 && xpos<=temp->nx2
			&& ypos>=temp->ny1 && ypos<=temp->ny2 && button!=1)	{
			if(temp->used==0)
				temp->used=2;
			else if(temp->used==2)	{
				drawflag(temp,7);
				temp->used=0;
			}
			if(temp->used==2)
				drawflag(temp,4);
			return 1;
		}
		if(xpos>=temp->nx1 && xpos<=temp->nx2
			&& ypos>=temp->ny1 && ypos<=temp->ny2
			&& mine_array[temp->cell1][temp->cell2]==-1 && button==1 && temp->used==0)	{
			dctgame=0;                           //value lose is cell=-1
			drawface(dctgame);
			return 0;
		}
		if(xpos>=temp->nx1 && xpos<=temp->nx2
			&& ypos>=temp->ny1 && ypos<=temp->ny2
			&& mine_array[temp->cell1][temp->cell2]!=-1 && button==1 && temp->used==0)	{
			reczerotest(temp->cell1,temp->cell2);
			temp->used=1;
			colorfillpoly(temp,7,simple);
			dctgame=1;                           //win
			drawface(dctgame);
			return 1;
		}
		temp=temp->next;
	}
	return 1;
}

void reczerotest(int r,int c)
{
	dctpoly *temp;
	temp=rightcused(r,c);
	if(mine_array[r][c]==0 && r>=0 && r<norc && c>=0 && c<norc && temp->used==0)
	{
		shwds(r,c);
		//nif(temp->used!=2)
			temp->used=1;
		shwds(r-1,c-1);
		reczerotest(r-1,c-1);
		shwds(r-1,c);
		reczerotest(r-1,c);
		shwds(r-1,c+1);
		reczerotest(r-1,c+1);
		shwds(r,c-1);
		reczerotest(r,c-1);
		shwds(r,c+1);
		reczerotest(r,c+1);
		shwds(r+1,c-1);
		reczerotest(r+1,c-1);
		shwds(r+1,c);
		reczerotest(r+1,c);
		shwds(r+1,c+1);
		reczerotest(r+1,c+1);
	}
}

void shwds(int r,int c)
{
	dctpoly *temp=head,*tmp2;
	tmp2=rightcused(r,c);
	if(tmp2->used==0)
	{
		while(mine_array[r][c]!=-1 && r>=0 && r<norc && c>=0 && c<norc)
		{
			if(temp->cell1==r && temp->cell2==c)	{
					colorfillpoly(temp,7,1);setcolor(0);//imp color set
				if(mine_array[r][c]!=0)
					temp->used=1;
				return ;
			}
			temp=temp->next;
		}
	}
}

dctpoly *rightcused(int r,int c)
{
	dctpoly *temp=head;
	while(mine_array[r][c]!=-1 && r>=0 && r<norc && c>=0 && c<norc)	{
		if(temp->cell1==r && temp->cell2==c)
			break;
		temp=temp->next;
	}
	return temp;
}

void hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}

void drawface(int dctgame)
{
	int maxx,maxy;
	setcolor(14);
	maxx=getmaxx()/2;
	ellipse(maxx,40,0,360,15,15);
	setfillstyle(SOLID_FILL,14);
	fillellipse(maxx,40,15,15);
	setcolor(15);
	//rectangle(maxx-25,10,maxx+25,70);
	//rectangle(maxx-28,17,maxx+28,73);
	if(dctgame==1)
		esmilewin(maxx,40);
	else
		esmilelose(maxx,40);
}

void esmilewin(int x,int y)
{
	setcolor(0);
	ellipse(x,y+5,180,360,5,2);
	ellipse(x,y+6,180,360,5,2);
	ellipse(x-5,y-5,0,360,1,1);
	ellipse(x+5,y-5,0,360,1,1);
	setfillstyle(SOLID_FILL,0);
	fillellipse(x-5,y-5,1,1);
	fillellipse(x+5,y-5,1,1);
	ellipse(x-5,y-5,0,360,2,2);
	ellipse(x+5,y-5,0,360,2,2);
	setfillstyle(SOLID_FILL,7);
	fillellipse(x-5,y-5,1,1);
	fillellipse(x+5,y-5,1,1);
}

void esmilelose(int x,int y)
{
	setcolor(0);
	ellipse(x,y+9,0,180,5,2);      //lip
	ellipse(x,y+10,0,180,5,2);

	ellipse(x-5,y-5,0,360,1,1);     //eye
	ellipse(x+5,y-5,0,360,1,1);
	line(x+5,y,x+5,y+3);
	line(x-5,y,x-5,y+3);

	setfillstyle(SOLID_FILL,0);
	fillellipse(x-5,y-5,1,1);
	fillellipse(x+5,y-5,1,1);
	ellipse(x-5,y-5,0,360,2,2);  //eye
	ellipse(x+5,y-5,0,360,2,2);
	setfillstyle(SOLID_FILL,7);
	fillellipse(x-5,y-5,1,1);
	fillellipse(x+5,y-5,1,1);
}

getkey()
{
	union REGS i,o;
	while(!kbhit());
	i.h.ah=0;int86(22,&i,&o);
	return(o.h.ah);
}

void drawflag(dctpoly *poly_,int color)
{
	int x,y ;
	x=(poly_->nx1+poly_->nx2)/2;
	y=(poly_->ny1+poly_->ny2)/2;
	if(color==4)
		setcolor(4);
	else
		setcolor(7);
	setfillstyle(SOLID_FILL,color);
	fillellipse(x,y,3,3);
}

void assinvaluetopoly()
{
	int r,c;
	fillzero();                         /*these four fn mst be called in main */
	randomize();
	initialise();
	nogenerator();
}

void initialise()        /*mine no. should be less than no. of box */
{
	int i,j,flag;
	for(j=0; j<mineno ; j++)
	{
			do
			{
				i=rand()%(norc*norc);
				flag=investigate(i);
			}while(flag==0);
	}
}

int investigate(int i)                 /* investigating whether the random cell is preoccupied with mine */
{
	int m,n;
	m=i/norc;
	n=i%norc;
	if(mine_array[m][n]==-1)
		return 0;
	else if(filling_sp(m,n) && filling_sp(m-1,n-1) && filling_sp(m-1,n) && filling_sp(m-1,n+1) && filling_sp(m,n-1) && filling_sp(m,n+1) && filling_sp(m+1,n-1) && filling_sp(m+1,n) && filling_sp(m+1,n+1))
	{
		mine_array[m][n]=-1;
		return 1;
	}
	else
		return 0;
}

void fillzero(void)                          /* filling the array with zero this must be done before starting a new game */
{
	int r,c;
	for(r=0;r<20;r++)
		for(c=0;c<20;c++)
			mine_array[r][c]=0;
	return ;
}

void nogenerator(void)                         /* generate the no. indicating mines */
{
	int r,c;
	for(r=0;r<norc;r++)
		for(c=0;c<norc;c++)
		{
			if(mine_array[r][c]!=-1)
				mine_array[r][c]=sumad(r,c);
		}
}

int sumad(int r,int c)
{
	int sum;
	sum=val(r-1,c-1)+val(r-1,c)+val(r-1,c+1)+val(r,c-1)+val(r,c+1)+val(r+1,c-1)+val(r+1,c)+val(r+1,c+1);
	return sum;
}

int val(int r,int c)
{
	if(r>=0 && r<norc && c>=0 && c<norc && mine_array[r][c]==-1)
		return 1;
	else
		return 0;
}

int filling_sp(int r,int c)                /*this fn stops mines to be placed in awkward positions i.e. where no adjacent cell represents the mine*/
{
	if(r>=0 && r<norc && c>=0 && c<norc)
	{
		if(((r==0 && c==0) || (r==0 && c==norc-1) || (r==norc-1 && c==0) || (r==norc-1 && c==norc-1)) && (sumad(r,c)+mine_array[r][c]*(-1))==3)
			return 0;
		else if((r==0 || c==0 || r==norc-1 || c==norc-1) && (sumad(r,c)+mine_array[r][c]*(-1))==5)
			return 0;
		else if((sumad(r,c)+mine_array[r][c]*(-1))==8)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

int dctifrealwin()
{
	dctpoly *temp=head;
	while(temp!=NULL)	{
		if(temp->used==0)
			return -1;
		if(temp->used==2 && mine_array[temp->cell1][temp->cell2]!=-1)
			return -1;
		temp=temp->next;
	}
	funinwin();
	return 1;
}

void funinwin()
{
	int x=getmaxx()/2,y=40;
	setcolor(0);
	ellipse(x,y+5,180,360,5,2);
	ellipse(x,y+6,180,360,5,2);

	ellipse(x-5,y-5,0,360,1,1);
	ellipse(x+5,y-5,0,360,1,1);
	setfillstyle(SOLID_FILL,0);

	fillellipse(x-5,y-5,5,3);
	fillellipse(x+5,y-5,5,3);
	line(x-10,y-5,x-15,y);
	line(x-10,y-4,x-15,y+1);
	line(x+10,y-5,x+20,y);
	line(x+10,y-4,x+20,y+1);
}