#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

//cube global declaration with r g o b w y being colors and the number is the orientation

char cube_corners[8][3]={{'r','g','w'},{'g','o','w'},{'o','b','w'},{'b','r','w'},
{'r','g','y'},{'g','o','y'},{'o','b','y'},{'b','r','y'}};
char cube_corners_verif[8][3]={{'r','g','w'},{'g','o','w'},{'o','b','w'},{'b','r','w'},
{'r','g','y'},{'g','o','y'},{'o','b','y'},{'b','r','y'}};
char cube_edges[12][2]={{'g','w'},{'o','w'},{'b','w'},{'r','w'},{'r','g'},{'g','o'},{'o','b'}
,{'b','r'},{'g','y'},{'o','y'},{'b','y'},{'r','y'}};
char cube_edges_verif[12][2]={{'g','w'},{'o','w'},{'b','w'},{'r','w'},{'r','g'},{'g','o'},{'o','b'},{'b','r'},{'g','y'},{'o','y'},{'b','y'},{'r','y'}};


//edge of the solve cross function
char edge[2]={'w','g'};
//corner of the corner solving function
char corner[4]={'r','g','w'};
//cube face-color conception
char cubes[55];
char cube[6][9];
char cube[6][9]={{'w','w','w','w','w','w','w','w','w'},{'r','r','r','r','r','r','r','r','r'},{'o','o','o','o','o','o','o','o','o'}
,{'b','b','b','b','b','b','b','b','b'},{'g','g','g','g','g','g','g','g','g'},{'y','y','y','y','y','y','y','y','y'}};
int verif=0;

//solution sequence
char solution[200];

//filling the pieces from the face-color conception

void update_edges(){
    cube_edges[0][0]=cube[4][3];
    cube_edges[0][1]=cube[0][5];

    cube_edges[1][0]=cube[2][1];
    cube_edges[1][1]=cube[0][7];

    cube_edges[2][0]=cube[3][5];
    cube_edges[2][1]=cube[0][3];

    cube_edges[3][0]=cube[1][7];
    cube_edges[3][1]=cube[0][1];

    cube_edges[4][0]=cube[1][5];
    cube_edges[4][1]=cube[4][1];

    cube_edges[5][0]=cube[4][7];
    cube_edges[5][1]=cube[2][5];

    cube_edges[6][0]=cube[2][3];
    cube_edges[6][1]=cube[3][7];

    cube_edges[7][0]=cube[3][1];
    cube_edges[7][1]=cube[1][3];

    cube_edges[8][0]=cube[4][5];
    cube_edges[8][1]=cube[5][5];

    cube_edges[9][0]=cube[2][7];
    cube_edges[9][1]=cube[5][1];

    cube_edges[10][0]=cube[3][3];
    cube_edges[10][1]=cube[5][3];

    cube_edges[11][0]=cube[1][1];
    cube_edges[11][1]=cube[5][7];
}
void update_corners(){

    
    cube_corners[0][0]=cube[1][8];
    cube_corners[0][1]=cube[4][0];
    cube_corners[0][2]=cube[0][2];

    cube_corners[1][0]=cube[4][6];
    cube_corners[1][1]=cube[2][2];
    cube_corners[1][2]=cube[0][8];

    cube_corners[2][0]=cube[2][0];
    cube_corners[2][1]=cube[3][8];
    cube_corners[2][2]=cube[0][6];
    

    cube_corners[3][0]=cube[3][2];
    cube_corners[3][1]=cube[1][6];
    cube_corners[3][2]=cube[0][0];

    cube_corners[4][0]=cube[1][2];
    cube_corners[4][1]=cube[4][2];
    cube_corners[4][2]=cube[5][8];

    cube_corners[5][0]=cube[4][8];
    cube_corners[5][1]=cube[2][8];
    cube_corners[5][2]=cube[5][2];

    cube_corners[6][0]=cube[2][6];
    cube_corners[6][1]=cube[3][6];
    cube_corners[6][2]=cube[5][0];

    cube_corners[7][0]=cube[3][0];
    cube_corners[7][1]=cube[1][0];
    cube_corners[7][2]=cube[5][6];
}
void update(){  
    update_edges();
    update_corners();
}


//piece finding function will return the position of the piece relative to the table above

int find_edge(char c1,char c2){
    int i=0;
    while(i<12){
        if (cube_edges[i][0]==c1 && cube_edges[i][1]==c2){
            return i;
        }
        if(cube_edges[i][1]==c1 && cube_edges[i][0]==c2){
            return i;
        }
        i++;
    }
    return -1;
}
int find_corner(char c1,char c2,char c3){
    for (int i=0;i<8;i++){
        
        //printf("\npiece being compared %c %c %c to the original %c %c %c\n",cube_corners[i][0],cube_corners[i][1],cube_corners[i][2],c1,c2,c3);
        if (cube_corners[i][0]==c1){
            if (cube_corners[i][1]==c2){
                if (cube_corners[i][2]==c3) return i;
            }
            if (cube_corners[i][1]==c3){
                if (cube_corners[i][2]==c2) return i;
            }
        }
        if (cube_corners[i][0]==c2){
            if (cube_corners[i][1]==c1){
                if (cube_corners[i][2]==c3) return i;
            }
            if (cube_corners[i][1]==c3){
                if (cube_corners[i][2]==c1) return i;
            }
        }
        if (cube_corners[i][0]==c3){
            if (cube_corners[i][1]==c2){
                if (cube_corners[i][2]==c1) return i;
            }
            if (cube_corners[i][1]==c1){
                if (cube_corners[i][2]==c2) return i;
            }
        }
    }
    return -1;
}
int find_piece(char piece_type, char colors[]){
    int i=0;
    if (piece_type=='e'){
        while(i<12){
            if (cube_edges[i][0]==colors[0] && cube_edges[i][1]==colors[1]){
                return i;
            }
            if(cube_edges[i][1]==colors[0] && cube_edges[i][0]==colors[1]){
                return i;
            }
            i++;
        }
    }
    if (piece_type=='c'){
        while(i<8){
            if (cube_corners[i][0]==colors[0] && cube_corners[i][1]==colors[1] && cube_corners[i][2]==colors[2]){
                return i;
            }
            i++;
        }
    }
    return -1;
}
int find_edge_orientation(char c1,char c2){
    char temp=c1;
    //printf("\n%c %c\n",c1,c2);
    c1=cube_edges[find_edge(c1,c2)][0];c2=cube_edges[find_edge(temp,c2)][1];
    if (c2=='w' || c2=='y') return 0;
    else if (c1!='w' && c1!='y' && c2!='w' && c2!='y'){
        //determine the orientation by assigning that a color is 'greater' than another by giving them order
        //the order is g>r>b>o
        //declaration of order :
        char order[4]={'g','o','b','r'};

        //printf("\n%c %c\n",c1,c2);
        int p;
        for (int i=0;i<4;i++){
            //printf("\nim here\n");
            if(c1==order[i]){
                if (order[i]=='r'){
                    p=-1;
                }
                else p=i;
                break;
            }
        }
        //printf("\n\n%c %c %c \n\n",c1,order[p+1],c2);
        if ( c2==order[p+1] ) return 0;
        else return 1;
    }
    else return 1;
}
int find_corner_orientation(){
    update();
    char auxi[3];
    auxi[0]=cube_corners[find_corner(corner[0],corner[1],corner[2])][0];
    auxi[1]=cube_corners[find_corner(corner[0],corner[1],corner[2])][1];
    auxi[2]=cube_corners[find_corner(corner[0],corner[1],corner[2])][2];
    for (int i=0;i<3;i++){
        if (auxi[i]=='y' || auxi[i]=='w'){
            return i;
        }
    }
}

//verification

int verify_sum_colors(){
    //verify colors
    int somme[6]={0,0,0,0,0,0};
    int i,j;
    for(i=0;i<6;i++){
            for(j=0;j<9;j++){
                switch (cube[i][j]){
                    case 'w' : somme[0]+=1;break ;
                    case 'r' : somme[1]+=1;break ;
                    case 'o' : somme[2]+=1;break ;
                    case 'b' : somme[3]+=1;break ;
                    case 'g' : somme[4]+=1;break ;
                    case 'y' : somme[5]+=1;break ;
                }
            }
    }

    for(i=0;i<6;i++){
        if(somme[i]!=9){
            return -1;
        }
    }
    return 1;
}

//verify edges
int verify_edge(){
    int k;
    for(k=0;k<12;k++){
        if(find_edge(cube_edges_verif[k][0],cube_edges_verif[k][1])==-1){
                return -1;
        }
    }
    return 1;
}

//verify corners
int different(char c1,char c2,char c3){
    if (c1==c2 || c1==c3 || c3==c2 )
        return -1;
    else return 1;
}


int verify_corner(){
    int k;
    for(k=0;k<8;k++){
        if(different(cube_corners_verif[k][0],cube_corners_verif[k][1],cube_corners_verif[k][2])==-1 || find_corner(cube_corners_verif[k][0],cube_corners_verif[k][1],cube_corners_verif[k][2])==-1){
                return -1;
        }
    }
    return 1;
}

//verify cube

int verify(){
    if(verify_sum_colors()==-1 || verify_edge()==-1 || verify_corner()==-1)
        return -1;
    return 1;
}

//display

void display() {
    for (int i=0;i<6;i++) {
        for (int j = 0; j < 9; j++) {
            printf("%c\t",cube[i][j]);
        }
        printf("\n");
    }
}
void display_new(){
    printf("\n      %c %c %c",cube[5][6],cube[5][3],cube[5][0]);
    printf("\n      %c %c %c",cube[5][7],cube[5][4],cube[5][1]);
    printf("\n      %c %c %c",cube[5][8],cube[5][5],cube[5][2]);
    printf("\n%c %c %c",cube[1][0],cube[1][1],cube[1][2]);printf(" %c %c %c",cube[4][2],cube[4][5],cube[4][8]);printf(" %c %c %c",cube[2][8],cube[2][7],cube[2][6]);printf(" %c %c %c",cube[3][6],cube[3][3],cube[3][0]);
    printf("\n%c %c %c",cube[1][3],cube[1][4],cube[1][5]);printf(" %c %c %c",cube[4][1],cube[4][4],cube[4][7]);printf(" %c %c %c",cube[2][5],cube[2][4],cube[2][3]);printf(" %c %c %c",cube[3][7],cube[3][4],cube[3][1]);
    printf("\n%c %c %c",cube[1][6],cube[1][7],cube[1][8]);printf(" %c %c %c",cube[4][0],cube[4][3],cube[4][6]);printf(" %c %c %c",cube[2][2],cube[2][1],cube[2][0]);printf(" %c %c %c",cube[3][8],cube[3][5],cube[3][2]);
    printf("\n      %c %c %c",cube[0][2],cube[0][5],cube[0][8]);
    printf("\n      %c %c %c",cube[0][1],cube[0][4],cube[0][7]);
    printf("\n      %c %c %c",cube[0][0],cube[0][3],cube[0][6]);
}

//moves

void do_move(char move){
    char aux[6][9];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            aux[i][j] = cube[i][j];
        }
    }
        switch (move)
        {
        case 'R':
                cube[0][6]=aux[3][6];
                cube[0][7]=aux[3][7];
                cube[0][8]=aux[3][8];

                cube[4][6]=aux[0][6];
                cube[4][7]=aux[0][7];
                cube[4][8]=aux[0][8];

                cube[3][6]=aux[5][2];
                cube[3][7]=aux[5][1];
                cube[3][8]=aux[5][0];

                cube[5][2]=aux[4][6];
                cube[5][1]=aux[4][7];
                cube[5][0]=aux[4][8];

                cube[2][0]=aux[2][6];
                cube[2][2]=aux[2][0];
                cube[2][6]=aux[2][8];
                cube[2][8]=aux[2][2];
                
                cube[2][1]=aux[2][3];
                cube[2][3]=aux[2][7];
                cube[2][5]=aux[2][1];
                cube[2][7]=aux[2][5];
                sprintf(solution,"%sR",solution);
            break;
        case 'L':
                cube[0][0]=aux[4][0];
                cube[0][1]=aux[4][1];
                cube[0][2]=aux[4][2];

                cube[4][0]=aux[5][8];
                cube[4][1]=aux[5][7];
                cube[4][2]=aux[5][6];

                cube[3][0]=aux[0][0];
                cube[3][1]=aux[0][1];
                cube[3][2]=aux[0][2];

                cube[5][8]=aux[3][0];
                cube[5][7]=aux[3][1];
                cube[5][6]=aux[3][2];
                
                cube[1][0]=aux[1][6];
                cube[1][2]=aux[1][0];
                cube[1][6]=aux[1][8];
                cube[1][8]=aux[1][2];
                
                cube[1][1]=aux[1][3];
                cube[1][3]=aux[1][7];
                cube[1][5]=aux[1][1];
                cube[1][7]=aux[1][5];
                sprintf(solution,"%sL",solution);
            break;
        case 'F':
                cube[0][2]=aux[2][2];
                cube[0][5]=aux[2][5];
                cube[0][8]=aux[2][8];

                cube[1][2]=aux[0][2];
                cube[1][5]=aux[0][5];
                cube[1][8]=aux[0][8];

                cube[2][2]=aux[5][2];
                cube[2][5]=aux[5][5];
                cube[2][8]=aux[5][8];

                cube[5][2]=aux[1][2];
                cube[5][5]=aux[1][5];
                cube[5][8]=aux[1][8];


                cube[4][0]=aux[4][6];
                cube[4][2]=aux[4][0];
                cube[4][6]=aux[4][8];
                cube[4][8]=aux[4][2];
                
                cube[4][1]=aux[4][3];
                cube[4][3]=aux[4][7];
                cube[4][5]=aux[4][1];
                cube[4][7]=aux[4][5];
                sprintf(solution,"%sF",solution);
                    break;
        case 'B':
                cube[0][0]=aux[1][0];
                cube[0][3]=aux[1][3];
                cube[0][6]=aux[1][6];

                cube[2][0]=aux[0][0];
                cube[2][3]=aux[0][3];
                cube[2][6]=aux[0][6];

                cube[5][0]=aux[2][0];
                cube[5][3]=aux[2][3];
                cube[5][6]=aux[2][6];

                cube[1][0]=aux[5][0];
                cube[1][3]=aux[5][3];
                cube[1][6]=aux[5][6];

                cube[3][0]=aux[3][6];
                cube[3][2]=aux[3][0];
                cube[3][6]=aux[3][8];
                cube[3][8]=aux[3][2];
                
                cube[3][1]=aux[3][3];
                cube[3][3]=aux[3][7];
                cube[3][5]=aux[3][1];
                cube[3][7]=aux[3][5];
                sprintf(solution,"%sB",solution);
                    break;
        case 'U':
                cube[1][0]=aux[4][2];
                cube[1][1]=aux[4][5];
                cube[1][2]=aux[4][8];

                cube[4][2]=aux[2][8];
                cube[4][5]=aux[2][7];
                cube[4][8]=aux[2][6];

                cube[2][6]=aux[3][0];
                cube[2][7]=aux[3][3];
                cube[2][8]=aux[3][6];

                cube[3][6]=aux[1][0];
                cube[3][3]=aux[1][1];
                cube[3][0]=aux[1][2];

                cube[5][0]=aux[5][6];
                cube[5][2]=aux[5][0];
                cube[5][6]=aux[5][8];
                cube[5][8]=aux[5][2];
                
                cube[5][1]=aux[5][3];
                cube[5][3]=aux[5][7];
                cube[5][5]=aux[5][1];
                cube[5][7]=aux[5][5];
                sprintf(solution,"%sU",solution);
                    break;
        case 'D':
                cube[1][6]=aux[3][8];
                cube[1][7]=aux[3][5];
                cube[1][8]=aux[3][2];

                cube[4][0]=aux[1][6];
                cube[4][3]=aux[1][7];
                cube[4][6]=aux[1][8];

                cube[2][0]=aux[4][6];
                cube[2][1]=aux[4][3];
                cube[2][2]=aux[4][0];

                cube[3][2]=aux[2][0];
                cube[3][5]=aux[2][1];
                cube[3][8]=aux[2][2];

                cube[0][0]=aux[0][6];
                cube[0][2]=aux[0][0];
                cube[0][6]=aux[0][8];
                cube[0][8]=aux[0][2];
                
                cube[0][1]=aux[0][3];
                cube[0][3]=aux[0][7];
                cube[0][5]=aux[0][1];
                cube[0][7]=aux[0][5];
                sprintf(solution,"%sD",solution);
                    break;
        default:
            break;
        }
}
void moves(char sequence[]){
    int len=strlen(sequence);
    for (int i=0;i<len;i++){
        char m=sequence[i];
        //printf("%c",m);
        if(tolower(m)==m){
            do_move(toupper(sequence[i]));do_move(toupper(sequence[i]));do_move(toupper(sequence[i]));
        }
        else do_move(toupper(sequence[i]));
    }
}

//solving the cross

char find_move(char c1,char c2){
    int cord=find_edge(c1,c2);
    int or=find_edge_orientation(c1,c2);
    or=or%4;
    //printf("\nfind move of the edge %c %c\n",c1,c2);
    //printf("with or %d cord %d\n",or,cord);
    if ((or==0 && (cord==0 || cord==8 || cord==5)) || (or==1 && (cord==4))){
        //printf("I AM HERE\n");
        return 'F';
    }
    if ((or==0 && (cord==1 || cord==9 || cord==6)) || (or==1 && (cord==5))){
        return 'R';
    }
    if ((or==0 && (cord==2 || cord==10 || cord==7)) || (or==1 && (cord==6))){
        return 'B';
    }
    if ((or==0 && (cord==3 || cord==11 || cord==4)) || (or==1 && (cord==7))){
        //printf("I AM HERE\n");
        return 'L';
    }
    if ( cord>7 && or==1 ){
        return 'U';
    }
    if (cord<4 && or==1) return 'D';
}
int cross_solve_moves(int cord,int or,int dest,int edges_solved){
    //printf("\nedge colors %c %c cord %d dest %d or %d\n\n",edge[0],edge[1],cord,dest,or);
    char move[2]="";
    //printf("the move string is %s ",move);
    if (cord==dest && or==0){
        //printf("\nI AM IN IF SOLVED COND\n");
        return 0;
    }
    if(cord==-1){
        int temp;
        printf("\nPIECE NOT FOUND\n");
        update();
        for (int i=0;i<12;i++){
        printf("edge %d",i);
        for (int j=0;j<2;j++){
            printf(" %c ",cube_edges[i][j]);
        }
        printf("\n");
        }
        scanf("%d",&temp);
    }
    if (cord<4){
        if (or==0){
                if (edges_solved==0){
                    while (cord!=dest)
                    {
                        moves("D");
                        update();
                        cord=find_edge(edge[0],edge[1]);
                    }
                }
                else{
                    int temp=0;
                    switch (cord)
                    {
                        case 1:
                            moves("RR");
                            while(cord!=dest+8){
                                moves("U");
                                temp++;
                                update();
                                cord=find_edge(edge[0],edge[1]);
                            }
                            if (temp==1) moves("FF");
                            if (temp==2) moves("LL");
                            if (temp==3) moves("BB");
                            temp=0;
                            break;
                        case 3:
                            moves("LL");
                            while(cord!=dest+8){
                                moves("U");
                                temp++;
                                update();
                                cord=find_edge(edge[0],edge[1]);
                            }
                            if (temp==1) moves("BB");
                            if (temp==2) moves("RR");
                            if (temp==3) moves("FF");
                            temp=0;
                            break;
                        case 0:
                            temp=0;
                            moves("FF");
                            while(cord!=dest+8){
                                moves("U");
                                temp++;
                                update();
                                cord=find_edge(edge[0],edge[1]);
                            }
                            if (temp==1) moves("LL");
                            if (temp==2) moves("BB");
                            if (temp==3) moves("RR");
                            temp=0;
                            break;
                        case 2:
                            temp=0;
                            moves("BB");
                            while(cord!=dest+8){
                                moves("U");
                                temp++;
                                update();
                                cord=find_edge(edge[0],edge[1]);
                            }
                            if (temp==1) moves("RR");
                            if (temp==2) moves("FF");
                            if (temp==3) moves("LL");
                            temp=0;
                            break;
                        default:
                            break;
                        }
            }
        }
        else{
            if(edges_solved==0){
                if(cord==0) moves("FL");
                if(cord==1) moves("RF");
                if(cord==2) moves("BR");
                if(cord==3) moves("LB");
                update();
                cord=find_edge(edge[0],edge[1]);
                or=find_edge_orientation(edge[0],edge[1]);
                cross_solve_moves(cord,or,dest,edges_solved);
            }
            else {
                switch (cord)
                {
                case 0:
                    moves("FluL");
                    break;
                case 1:
                    moves("RfuF");
                    break;
                case 2:
                    moves("BrUR");
                    break;
                case 3:
                    moves("lFuf");
                    break;
                default:
                    break;
                }
                update();
                cord=find_edge(edge[0],edge[1]);
                or=find_edge_orientation(edge[0],edge[1]);
                cross_solve_moves(cord,or,dest,edges_solved);
            }
        }
    }
    else if (cord>3 && cord<8){
        move[0]=' ';move[1]=' ';
        if (((cord-4)==dest && or==1) || ((cord-5)==dest && or==0)){
            move[0]=find_move(edge[0],edge[1]);
            //printf("THE MOVE IS %c\n",move[0]);
            while(cord!=dest){
                do_move(move[0]);
         //       printf("%c",move[0]);
                update();
                cord=find_edge(edge[0],edge[1]);
            }
        }
        else{
            int temp=0;
            char m=find_move(edge[0],edge[1]);
            if(dest==1)temp=3;
            if(dest==2)temp=2;
            if(dest==3)temp=1;
            if(m=='R')temp+=1;
            if(m=='B')temp+=2;
            if(m=='L')temp+=3;
            temp=temp%4;
            for(int i=0;i<temp;i++){
                moves("D");
            }
            while (cord>3)
            {
                do_move(m);
                printf("%c",m);
                update();
                cord=find_edge(edge[0],edge[1]);
            }
            for(int i=0;i<temp;i++){
                moves("d");
            }
            
        }
    }
    else{
        if(or==0){
            while((cord-8)!=dest){
                moves("U");
                update();
                cord=find_edge(edge[0],edge[1]);
            }
            move[0]=find_move(edge[0],edge[1]);
            moves(move);moves(move);
        }
        else{
            if(cord==8)moves("FrfR");
            if(cord==9)moves("RbrB");
            if(cord==10)moves("BlbL");
            if(cord==11)moves("LflF");
            update();
            cord=find_edge(edge[1],edge[0]);
            or=find_edge_orientation(edge[0],edge[1]);
            cross_solve_moves(cord,or,dest,edges_solved);
        }
    }
}
int solve_cross(){
    char colord[3]={'o','b','r'};
    int dest_cord=0;
    int solved_edges=0;
    edge[0]='g';edge[1]='w';
    if(solved_edges!=4){
    for(int i=0;i<4;i++){
        update();
        int cord=find_edge(edge[0],edge[1]);
        int or=find_edge_orientation(edge[0],edge[1]);
        cross_solve_moves(cord,or,dest_cord,solved_edges);
        solved_edges++;
        if (i<3){
            dest_cord++;
            edge[0]=colord[i];
        }
        if(solved_edges==4) {
            //printf("\nsolved edges %d\n",solved_edges);
            break;
        }
        //printf("\nsolved edges %d\n",solved_edges);
    }
    }
    solved_edges=0;
    update();
    if (find_edge('g','w')==0) solved_edges++;
    if (find_edge('o','w')==1) solved_edges++;
    if (find_edge('b','w')==2) solved_edges++;
    if (find_edge('r','w')==3) solved_edges++;
    //printf("solved edges final %d\n",solved_edges);
}


//solving corners

int solve_corners_moves(int cord,int or,int dest){
    //printf("\n");
    //printf("\ncorner %c %c %c with cord %d or %d dest %d\n",corner[0],corner[1],corner[2],cord,or,dest);
    if (cord==dest && or==2){
        return 0;
    }
    else if(cord%4==dest){
        if (cord%4==0){
            while(!(cord==dest && or==2)){
                moves("luLU");
                update();
                cord=find_corner(corner[0],corner[1],corner[2]);
                or=find_corner_orientation();
                //printf("\ncord is %d ord is %d\n",cord,or);
            }
        }
        if (cord%4==1){
            while(!(cord==dest && or==2)){
                moves("RUru");
                update();
                cord=find_corner(corner[0],corner[1],corner[2]);
                or=find_corner_orientation();
            }
        }
        if (cord%4==2){
            while(!(cord==dest && or==2)){
                moves("ruRU");
                update();
                cord=find_corner(corner[0],corner[1],corner[2]);
                or=find_corner_orientation();
            }
        }
        if (cord%4==3){
            while(!(cord==dest && or==2)){
                moves("ULul");
                update();
                cord=find_corner(corner[0],corner[1],corner[2]);
                or=find_corner_orientation();
            }
        }
    }
    else{
        if(cord>3){
            while(!(cord%4==dest)){
                moves("U");
                update();
                cord=find_corner(corner[0],corner[1],corner[2]);
                or=find_corner_orientation();
            }
            solve_corners_moves(cord,or,dest);
        }
        else{
            if(cord==0) moves("luL");
            if(cord==1) moves("RUr");
            if(cord==2) moves("ruR");
            if(cord==3) moves("Lul");
            update();
            cord=find_corner(corner[0],corner[1],corner[2]);
            or=find_corner_orientation();
            solve_corners_moves(cord,or,dest);
        }
    }

}
int solve_corners(){
    update();
    corner[0]='r';corner[1]='g';corner[2]='w';
    int cord=find_corner(corner[0],corner[1],corner[2]);
    int or=find_corner_orientation();
    int dest=0;
    //printf("\ncorner   %c    %c     %c with cord %d or %d dest %d\n",corner[0],corner[1],corner[2],cord,or,dest);
    solve_corners_moves(cord,or,dest);
    //printf("\ncorner 1 inserted\n");

    update();
    corner[0]='g';corner[1]='o';corner[2]='w';
    cord=find_corner(corner[0],corner[1],corner[2]);
    or=find_corner_orientation();
    dest++;
    solve_corners_moves(cord,or,dest);
    //printf("\ncorner 2 inserted\n");
    
    update();
    corner[0]='o';corner[1]='b';corner[2]='w';
    cord=find_corner(corner[0],corner[1],corner[2]);
    or=find_corner_orientation();
    dest++;
    solve_corners_moves(cord,or,dest);
    //printf("\ncorner 3 inserted\n");

    update();
    corner[0]='b';corner[1]='r';corner[2]='w';
    cord=find_corner(corner[0],corner[1],corner[2]);
    or=find_corner_orientation();
    dest++;
    solve_corners_moves(cord,or,dest);
    //printf("\ncorner 4 inserted\n");
}
 
 
 //solving the 2nd layer

int solve_layer_2_moves(int cord,int or,int dest){
    //display_new();
    //printf("\nedge colors %c %c cord %d dest %d or %d\n\n",edge[0],edge[1],cord,dest,or);
    //printf("\n");
    //for (int i=0;i<12;i++){
        //printf("edge %d",i);
        //for (int j=0;j<2;j++){
        //    printf(" %c ",cube_edges[i][j]);
        //}
        //printf("\n");
    //}
    if(cord==dest && or==0){
        return 0;
    }
    else if(cord<8){
        if(cord==4)moves("FufulUL");
        if(cord==5)moves("RurufUF");
        if(cord==6)moves("BuburUR");
        if(cord==7)moves("LulubUB");
        update();
        cord=find_edge(edge[0],edge[1]);
        or=find_edge_orientation(edge[0],edge[1]);
        solve_layer_2_moves(cord,or,dest);
    }
    else{
        if(or==0){
            int d;
            if(dest==5) d=8;
            if(dest==6) d=9;
            if(dest==7) d=10;
            if(dest==4) d=11;
            //printf("\ncord is %d d is %d\n",cord,d);
            while (cord!=d)
            {
                //printf("\nINSIDE LOOP : cord is %d d is %d\n",cord,d);
                //printf("\n");
                //display_new();
                //printf("\n");
                moves("U");
                //printf("\n");
                //display_new();
                //printf("\n");
                update();
                cord=find_edge(edge[0],edge[1]);
            }
            //insert to the right
            if(cord==8) moves("URUrufuF");
            if(cord==9) moves("UBUburuR");
            if(cord==10) moves("ULUlubuB");
            if(cord==11) moves("UFUfuluL");
        }
        else{
            while (!(cord-4==dest))
            {
                moves("U");
                update();
                cord=find_edge(edge[0],edge[1]);
            }
            //insert to the left
            if(cord==8) moves("uluLUFUf");
            if(cord==9) moves("ufuFURUr");
            if(cord==10) moves("uruRUBUb");
            if(cord==11) moves("ubuBULUl");
        }
    }
 }
int solve_layer_2(){
    //printf("\n");
    //printf("\n");
    edge[0]='r';edge[1]='g';
    update();
    int cord=find_edge(edge[0],edge[1]);
    int or=find_edge_orientation(edge[0],edge[1]);
    int dest=4;
    solve_layer_2_moves(cord,or,dest);
    //printf("\n");
    //printf("\nedge 1 inserted\n");
    //printf("\n");

    edge[0]='g';edge[1]='o';
    update();
    cord=find_edge(edge[0],edge[1]);
    or=find_edge_orientation(edge[0],edge[1]);
    dest++;
    solve_layer_2_moves(cord,or,dest);
    //printf("\n");
    //printf("\nedge 2 inserted\n");
    //printf("\n");

    edge[0]='o';edge[1]='b';
    update();
    cord=find_edge(edge[0],edge[1]);
    or=find_edge_orientation(edge[0],edge[1]);
    dest++;
    solve_layer_2_moves(cord,or,dest);
    //printf("\n");
    //printf("\nedge 3 inserted\n");
    //printf("\n");

    edge[0]='b';edge[1]='r';
    update();
    cord=find_edge(edge[0],edge[1]);
    or=find_edge_orientation(edge[0],edge[1]);
    dest++;
    solve_layer_2_moves(cord,or,dest);
    //printf("\n");
    //printf("\nedge 4 inserted\n");
    //printf("\n");

    return 0;
}

//SOLVING THE LAST LAYERRRR!!!!

//solving 2-look OLL

//making the cross on the yellow face

int yellow_cross(){
    if(verif==4){
        //printf("\nINVALID CUBE INPUT\n");
        return -1;
    }
    if (cube[5][1]=='y' && cube[5][3]=='y' && cube[5][5]=='y' && cube[5][7]=='y') return 0;
    else{
        if(cube[5][3]=='y' && cube[5][7]=='y'){
            moves("FURurf");
            return 0;
        }
        if(cube[5][1]=='y' && cube[5][7]=='y'){
            moves("FRUruf");
            return 0;
        }
        else if(!(cube[5][1]=='y' || cube[5][3]=='y' || cube[5][5]=='y' || cube[5][7]=='y')){
            moves("FURurf");
            verif++;
            yellow_cross();
        }
        else if(verif<3){
            moves("U");
            verif++;
            yellow_cross();
            
        }
        else{
            //printf("\nINVALID CUBE INPUT\n");
            return -1;
        }
    }
}

//second look oll

int oll(){
    if(verif==4){
        //printf("\nINVALID CUBE INPUT\n");
        return -1;
    }
    if (cube[5][0]=='y' && cube[5][2]=='y' && cube[5][6]=='y' && cube[5][8]=='y'){
        return 0;
    }
    //cases where no corners are oriented
    //case where corners are parallel
    if (cube[4][2]=='y' && cube[4][8]=='y' && cube[3][0]=='y' && cube[3][6]=='y'){
        moves("FRUruRUruRUruf");
        return 0;
    }
    //case where they are perpendicular
    if (cube[4][8]=='y' && cube[1][0]=='y' && cube[1][2]=='y' && cube[3][6]=='y'){
        moves("RUURRuRRuRRUUR");
        return 0;
    }
    //cases 2 corners are solved
    //headlights
    if (cube[5][0]=='y' && cube[5][6]=='y' && cube[4][2]=='y' && cube[4][8]=='y'){
        moves("RRDrUURdrUUr");
        return 0;
    }
    //reverse headlights
    if (cube[5][0]=='y' && cube[5][2]=='y' && cube[4][2]=='y' && cube[3][0]=='y'){
        moves("LFrflFRf");
        return 0;
    }
    //corners oriented one by one
    if (cube[5][2]=='y' && cube[5][6]=='y' && cube[1][2]=='y' && cube[3][6]=='y'){
        moves("rflFRfLF");
        return 0;
    }
    //cases where 1 corner is solved
    //sune right
    if (cube[5][8]=='y' && cube[4][8]=='y' && cube[2][6]=='y' && cube[3][0]=='y'){
        moves("RUrURUUr");
        return 0;
    }
    //sune left
    if (cube[5][2]=='y' && cube[1][0]=='y' && cube[4][2]=='y' && cube[3][6]=='y'){
        moves("luLulUUL");
        return 0;
    }
    else{
        moves("U");
        verif++;
        oll();
    }
}

//pll for coners
int pll_corners(){
    if (cube[1][0]==cube[1][2] && cube[4][2]==cube[4][8] && cube[2][6]==cube[2][8] && cube[3][0]==cube[3][6]){
        while(cube[1][1]!='r'){
        moves("U");
        }
        return 0;
    }
    //adjacent corner swap
    if (cube[1][0]==cube[1][2] || cube[4][2]==cube[4][8] || cube[2][6]==cube[2][8] || cube[3][0]==cube[3][6]){
        while (cube[1][0]!=cube[1][2])
        {
            moves("U");
        }
        moves("RUrurFRRuruRUrf");
    }
    //diagonal corner swap
    else{
        moves("FRuruRUrfRUrurFRf");
    }
    if (!(cube[1][0]==cube[1][2] && cube[4][2]==cube[4][8] && cube[2][6]==cube[2][8] && cube[3][0]==cube[3][6])){
        return -1;
    }
    while(cube[1][1]!='r'){
        moves("U");
    }
}

//pll for edges
int pll_edges(){
    int z=0;
    if (verif==4){
        //printf("\nINVALID CUBE INPUT\n");
        return -1;
    }
    if (cube[1][1]==cube[1][0] && cube[2][7]==cube[2][0] && cube[4][5]==cube[4][0] && cube[3][3]==cube[3][0]){
        return 0;
    }
    if (!(cube[1][1]=='r' && cube[2][7]=='o' && cube[4][5]=='g' && cube[3][3]=='b')){
        z=1;
    }
    //H perm
    if(cube[1][1]==cube[2][5] && cube[4][5]==cube[3][0]){
        moves("RRUURRUURRURRUURRUURRu");
    }
    //Z perm
    else if((cube[1][1]!='r' && cube[2][7]!='o' && cube[4][5]!='g' && cube[3][3]!='b' && z!=1)){
        moves("ruRRURUruRURuRur");
    }
    //U perm
    else if (cube[3][3]==cube[3][0]){
        if(cube[2][7]==cube[1][0]){
            moves("RuRURURuruRR");
        }
        else moves("lUlululULULL");
    }
    else{
        moves("U");
        verif++;
        pll_edges();
    }
}

//full pll
int pll(){
    pll_corners();
    //printf("\n\npll corners done\n\n");
    printf("\n");
    verif=0;
    int ver=pll_edges();
    if (ver==-1){
        return -1;
    }
    while(cube[1][0]!='r'){
        moves("U");
    }
    //printf("\n");
}


int main() {
    scanf("%s",cubes);
    int k=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<9;j++){
            if (i==1)k=1;
            if (i==2)k=5;
            if (i==3)k=2;
            if (i==4)k=4;
            if (i==5)k=3;
            cube[k][j]=cubes[i*9+j];
        }
    }
    sprintf(solution, "");
    if(verify()==-1){
        printf(" \n cube not verified \n");
        return -1;
    }
    solve_cross();
    solve_corners();
    solve_layer_2();
    verif=0;
    int ver=yellow_cross();
    if (ver==-1){
        return -1;
    }
    verif=0;
    ver=oll();
    if (ver==-1){
        return -1;
    }
    verif=0;
    ver=pll();
    if (ver==-1){
        return -1;
    }
    printf("%s", solution);
    return 0;

    //printf("WORKS\n");
    //char colors[6]={'w','r','o','b','g','y'};
    /*display_new();
    printf("\n\n");
    moves("RLLBDrbdffUURLFLLRLRFlubfub");
    sprintf(solution,"");
    printf("\n\n");
    update();
    for(int i=0;i<8;i++){
        printf("\ncorner %d ",i);
        for(int j=0;j<3;j++){
            printf(" %c ",cube_corners[i][j]);
        }
        printf("\n");
    }
    for (int i=0;i<12;i++){
        printf("edge %d",i);
        for (int j=0;j<2;j++){
            printf(" %c ",cube_edges[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    display_new();
    printf("\n");
    update(); 
    solve_cross();
    display_new();
    update();
    printf("\n\n%d",find_corner('r','w','g'));
    for (int i=0;i<12;i++){
        printf("edge %d",i);
        for (int j=0;j<2;j++){
            printf(" %c ",cube_edges[i][j]);
        }
        printf("\n");
    }
    display_new();
    solve_corners();
    printf("\n");
    display_new();
    update();
    solve_layer_2();
    printf("\n");
    display_new();
    update();
    verif=0;
    printf("\n");
    yellow_cross();
    printf("\nYELLOW CROSS MADE\n");
    printf("\n");
    display_new();
    printf("\n");
    verif=0;
    oll();
    printf("\noll finished\n");
    printf("\n");
    display_new();
    printf("\n");
    pll();
    printf("\n");
    printf("pll finished");
    printf("\n");
    display_new();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("%s",solution);*/
}