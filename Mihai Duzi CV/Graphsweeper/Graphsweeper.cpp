#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<conio.h>
#include<time.h>
#include<graphics.h>
using namespace std;

int dif, viz[26], nrviz, weasy=0, wmedium=0, whard=0, nr_m=6;
char mesaje[100][256]={"De ce s-a pierdut graful prin labirint? Pentru ca era neorientat.","Jocul original Minesweeper a aparut in anul 1990.","Creatorii jocului Minesweeper sunt Robert Donner si Curt Johnson.","Jocul Minesweeper a fost creat pentru a-i ajuta pe utilizatori sa se familiarizeze cu mouse-ul.","Sansele de a gasi cifra 8(un patrat lipsit de bomba inconjurat de 8 bombe) este de 0.0008219.","Primul turneu de Minesweeper a avut loc in 2005 la Budapesta."};
struct graf{
    int n,a,b,ad[100][100];
}G;

void joc(graf G);
void mainmenu();
void how2play();
void alegedif();
void joc();


///FUNCTII AJUTATOARE
void coord(int i,int &x,int &y){
    x=(i-1)/5*100+520;
    y=(i-1)%5*100+205;
}

int cmmdc(int a,int b){
    if(b==0) return a;
    return cmmdc(b,a%b);
}

float distanta(int ax,int ay,int bx,int by){
    return sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay));
}


///FUNCTII DE GENERARE + AFISARE
void generare_graf(){
    int conex;
    for(int i=1;i<=25;i++) viz[i]=0;
    int xx,xy,yx,yy;
    G.n=25;
    G.a=20;
    G.b=1+2*dif;
    nrviz=G.b;
    for(int i=1;i<=G.n;i++){
        for(int j=1;j<=G.n;j++){
            G.ad[i][j]=0;
        }
    }
    for(int i=0;i<G.b;i++){
        int random;
        do{
            random=rand()%(G.n)+1;
        }while(G.ad[random][random]==-1);
        G.ad[random][random]=-1;
        viz[random]=-1;
    }
    for(int i=0;i<G.a;i++){
        int x,y;
        do{
            x=rand()%(G.n)+1;
            y=rand()%(G.n)+1;
            coord(x,xx,xy);
            coord(y,yx,yy);
        }while(G.ad[x][y]==1||x==y||cmmdc(abs(yy-xy)/100,abs(yx-xx)/100)!=1||xx==yx||xy==yy);
        G.ad[x][y]=1;
        G.ad[y][x]=1;
    }
    for(int i=1;i<=G.n;i++){
        if(G.ad[i][i]!=-1){
            int bombe=0;
            for(int j=1;j<=G.n;j++){
                if(G.ad[i][j]==1&&G.ad[j][j]==-1) bombe++;
            }
            G.ad[i][i]=bombe;
        }
    }
}

void afisare_graf(){
    cout<<"Dificultate: ";
    if(dif==1) cout<<"Usor";
    else if(dif==2) cout<<"Mediu";
    else cout<<"Greu";
    cout<<endl;
    cout<<G.n<<" noduri "<<endl<<G.a<<" muchii "<<endl<<G.b<<" bombe"<<endl;
    for(int i=1;i<=G.n;i++){
        for(int j=1;j<=G.n;j++){
            cout<<G.ad[i][j]<<" ";
            if(G.ad[i][j+1]!=-1) cout<<" ";
        }
        cout<<endl;
    }
}


///FUNCTII PENTRU MENIURI
void mainmenu(){
    cleardevice();
    int cx,cy;
    char ce[2],cm[2],ch[2],ct[2];
    setcolor(BLACK);
    outtextxy(660,120,"GRAPHSWEEPER");
    sprintf(ce,"%i",weasy);
    sprintf(cm,"%i",wmedium);
    sprintf(ch,"%i",whard);
    sprintf(ct,"%i",weasy+wmedium+whard);
    outtextxy(690,150,"USOR");
    outtextxy(735,150,ce);
    outtextxy(690,165,"MEDIU");
    outtextxy(740,165,cm);
    outtextxy(690,180,"GREU");
    outtextxy(735,180,ch);
    outtextxy(690,195,"TOTAL");
    outtextxy(740,195,ct);
    outtextxy(60,750,mesaje[rand()%nr_m]);
    setcolor(LIGHTGREEN);
    rectangle(600,300,840,400);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(720,350,LIGHTGREEN);
    outtextxy(700,350,"JOACA");
    setcolor(YELLOW);
    rectangle(600,420,840,520);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(720,470,YELLOW);
    outtextxy(670,470,"CUM SE JOACA");
    setcolor(RED);
    rectangle(600,540,840,640);
    setfillstyle(SOLID_FILL,RED);
    floodfill(720,590,RED);
    outtextxy(705,590,"IESI");
    do{
        getmouseclick(WM_LBUTTONDOWN,cx,cy);
        if(cx>=600&&cx<=840){
            if(cy>=300&&cy<=400) alegedif();
            if(cy>=420&&cy<=520) how2play();
            if(cy>=540&&cy<=640) closegraph();
        }
    }while(true);
}

void alegedif(){
    cleardevice();
    int cx,cy;
    setcolor(BLACK);
    outtextxy(660,120,"ALEGE DIFICULTATEA");
    setcolor(LIGHTGREEN);
    rectangle(600,300,840,400);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    floodfill(720,350,LIGHTGREEN);
    outtextxy(700,350,"USOR");
    setcolor(YELLOW);
    rectangle(600,420,840,520);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(720,470,YELLOW);
    outtextxy(700,470,"MEDIU");
    setcolor(RED);
    rectangle(600,540,840,640);
    setfillstyle(SOLID_FILL,RED);
    floodfill(720,590,RED);
    outtextxy(705,590,"GREU");
    setcolor(BLUE);
    rectangle(600,660,840,760);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(720,710,BLUE);
    outtextxy(705,710,"INAPOI");
    do{
        getmouseclick(WM_LBUTTONDOWN,cx,cy);
        if(cx>=600&&cx<=840&&cy>=300&&cy<=400){
            dif=1;
            generare_graf();
            //afisare_graf();
            joc(G);
        }
        else if(cx>=600&&cx<=840&&cy>=420&&cy<=520){
            dif=2;
            generare_graf();
            //afisare_graf();
            joc(G);
        }
        else if(cx>=600&&cx<=840&&cy>=540&&cy<=640){
            dif=3;
            generare_graf();
            //afisare_graf();
            joc(G);
        }
        else if(cx>=600&&cx<=840&&cy>=660&&cy<=760) mainmenu();
    }while(true);
}

void how2play(){
    cleardevice();
    int cx,cy;
    setcolor(BLACK);
    outtextxy(640,120,"CUM SE JOACA?");
    outtextxy(100,190,"GRAPHSWEEPER este un joc inspirat din jocul MINESWEEPER.");
    outtextxy(100,260,"Daca in MINESWEEPER trebuia sa descoperi toate bombele dintr-un dreptunghi,");
    outtextxy(100,330,"In GRAPHSWEEPER trebuie sa descoperi toate bombele dintr-un graf.");
    outtextxy(100,400,"Ca in MINESWEEPER, o parte din nodurile grafului vor fi bombe pe care va trebui sa le descoperi.");
    outtextxy(100,470,"Vei pierde daca vei selecta o bomba, dar vei castiga daca vei selecta toate nodurile care nu sunt bombe.");
    outtextxy(100,540,"Jocul are 3 dificultati: Usor, Mediu si Greu. La toat dificultatile, graful are 25 de noduri si 20 de muchii.");
    outtextxy(100,610,"Cele 3 dificutati difera prin numarul de bombe. Sunt 3 bombe la usor, 5 la mediu si 7 la greu.");
    setcolor(BLUE);
    rectangle(600,660,840,760);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(720,710,BLUE);
    outtextxy(705,710,"INAPOI");
    do{
        getmouseclick(WM_LBUTTONDOWN,cx,cy);
        if(cx>=600&&cx<=840&&cy>=660&&cy<=760) mainmenu();
    }while(true);
}

void joc(graf G){
    int cx,cy,nod=0;
    cleardevice();
    int x[26];
    int y[26];
    for(int i=1;i<=25;i++){
        coord(i,x[i],y[i]);
    }
    char c[2];
    int i,j;
    setcolor(LIGHTBLUE);
    for(i=1;i<=G.n;i++){
        for(j=1;j<=G.n;j++){
            if(G.ad[i][j]==1){
                setcolor(BLUE);
                line(x[i],y[i],x[j],y[j]);
            }
        }
    }
    for(i=1;i<=G.n;i++){
        setfillstyle(SOLID_FILL,BLACK);
        setcolor(BLACK);
        circle(x[i],y[i],15);
        floodfill(x[i]-5,y[i]-7,0);
        setcolor(WHITE);
    }
    setcolor(BLACK);
    rectangle(470,160,970,660);
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    floodfill(0,0,BLACK);
    if(dif==1) outtextxy(640,120,"GRAPHSWEEPER - USOR");
    if(dif==2) outtextxy(640,120,"GRAPHSWEEPER - MEDIU");
    if(dif==3) outtextxy(640,120,"GRAPHSWEEPER - GREU");
    setcolor(BLUE);
    rectangle(600,660,840,760);
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(720,710,BLUE);
    outtextxy(705,710,"INAPOI");
    do{
        getmouseclick(WM_LBUTTONDOWN,cx,cy);
        if(cx==-1||cy==-1) continue;
        for(int i=1;i<=25;i++){
            if(distanta(cx,cy,x[i],y[i])<=15){
                nod=i;
            }
        }
        if(nod!=0){
            if(viz[nod]==0){
                viz[nod]=1;
                nrviz++;
                setfillstyle(SOLID_FILL,GREEN);
                setcolor(BLACK);
                circle(x[nod],y[nod],15);
                floodfill(x[nod]-5,y[nod]-7,LIGHTGRAY);
                setcolor(WHITE);
                sprintf(c,"%i",G.ad[nod][nod]);
                outtextxy(x[nod],y[nod],c);
                if(nrviz==G.n){
                    setcolor(GREEN);
                    outtextxy(540,135,"AI CASTIGAT. DA CLICK ORIUNDE PENTRU A TE INTOARCE.");
                    if(dif==1) weasy++;
                    if(dif==2) wmedium++;
                    if(dif==3) whard++;
                    do{
                        getmouseclick(WM_LBUTTONDOWN,cx,cy);
                        if(cx!=-1&&cy!=-1) mainmenu();
                    }while(true);
                }
            }
            if(viz[nod]==-1){
                viz[nod]=-2;
                setfillstyle(SOLID_FILL,RED);
                floodfill(x[nod],y[nod],LIGHTGRAY);
                setcolor(RED);
                outtextxy(540,135,"AI PIERDUT. DA CLICK ORIUNDE PENTRU A TE INTOARCE.");
                do{
                    getmouseclick(WM_LBUTTONDOWN,cx,cy);
                    if(cx!=-1&&cy!=-1) mainmenu();
                }while(true);
            }
        }
        else if(cx>=600&&cx<=840&&cy>=660&&cy<=760){
            mainmenu();
        }
    }while(true);
}



int main(){
    initwindow(1440,810);
    setbkcolor(LIGHTGRAY);
    cleardevice();
    mainmenu();
    while(!kbhit());
    closegraph();
    return 0;
}
