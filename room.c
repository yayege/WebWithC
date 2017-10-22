

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 1000
#define SIZE 8


void errorPage(char *);
void rePage(char *write);
void changeResourses(int);
void reFresh();
void getInput();
void getResources();
void drop();
void challenge();
void exitRoom();
void submitAns();

int roomGold;
int playerGold;

int playerManna;
int roomManna;

int roomOcc; //if the room occupied 1 for occupied, 0 for not occupied

char *contLenc;
int contLen;
char command[SIZE];
char inventory[SIZE];
char input[MAX];
int goldDrop;
int tempManna;

int main(int argc,char *argv[]){
    
    getInput();
    
    getResources();
    
    
    
    printf("%s\n\n","Content-Type:text/html");
    printf("<!DOCTYPE html>\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<meta charset=\"utf-8\">\n");
    printf("<title>The Jem Room</title>\n");
    printf("<meta name=\"description\" content=\"A game room for COMP 206 Group Project\">\n");
    printf("<link rel=\"stylesheet\" href=\"css/bootstrap.min.css\">\n");
    printf("<link rel=\"stylesheet\" href=\"css/main.css\">\n");
    printf("</head>\n");
    printf("<body>\n");
    
    submitAns();
    
    
    
}
void submitAns(){
    if(strncmp(command,"DROP",4)==0){
        drop();
        changeResourses(1);
        rePage(" ");
    }
    else if(strncmp(command,"PLAY",4)==0){
        challenge();
    }
    else if(strncmp(command,"EXIT",4)==0){
        exitRoom();
        
    }
    else if(strncmp(command,"REFRESH",7)==0){
        rePage(" ");
    }
    else{
        changeResourses(1);
    }
}


void exitRoom(){
    roomManna+=playerManna;
    roomGold+=playerGold;
    rePage("Really sorry for your exit.Please come back.\n");
    changeResourses(0);
    
}


void drop(){
    
    if(playerGold<2){
        errorPage("You do not have enough Gold to buy Manna");
    }
    else{
        
        tempManna=goldDrop/2;
        playerGold=playerGold-goldDrop;
        roomGold=roomGold+goldDrop;
        playerManna=tempManna+playerManna;
        
        }
    
}

void getInput(){
    contLenc=getenv("CONTENT_LENGTH");
    if(contLenc==NULL || sscanf(contLenc,"%d",&contLen)!=1 || contLen>MAX){
        errorPage("Error Reading the Page");
    }
    else {
        fgets(input,contLen+1,stdin);
    }
    
    int i=0;
    int j=0;
    int k=0;
    
    while(input[i]!='='){
        i++;
    }
    i++;
    while(input[i]!='&'){
        inventory[j]=input[i];
        i++; j++;
    }
    inventory[j]='\0';
    
    while(input[i]!='='){
        i++;
    }
    i++;
    while(input[i]!='\0'){
        command[k]=input[i];
        i++, k++;
    }
    command[k]='\0';
    
    
    i=0; j=0;
    int m;
    while(inventory[i]!='%'){
        i++;
    }
    inventory[i++]=',';
    for(m=0;m<5;++m){
        inventory[i]=inventory[i+2];
        i++;
    }
    inventory[i+2]='\0';
    
    while(command[j]!='+' && command[j]!='\0'){
        command[j]=toupper(command[j]);
        j++;
    }
    
    if(command[j]=='+'){
        command[j++]=' ';
    }
    else {
        while(command[j]!='\0'){
            command[j]=command[j+1];
            j++;
        }
        command[j]='\0';
    }
    
    
    i=0, j=0;
    char tempPlayerMana[4], tempPlayerGold[4];
    while (inventory[i]!=','){
        tempPlayerMana[i]=inventory[i];
        i++;
    }
    playerManna=atoi(tempPlayerMana);
    i++;
    while(inventory[i]!='\0'){
        tempPlayerGold[j]=inventory[i];
        i++; j++;
        
    }
    playerGold=atoi(tempPlayerGold);
    
    i=0; j=0;
    char TempDropGold[4];
    while(command[i]!=' ' && command[i]!='\0'){
        i++;
    }
    i++;
    while(command[i]!='\0'){
        TempDropGold[j]=command[i];
        i++; j++;
    }
    
    goldDrop=atoi(TempDropGold);
    
}

void errorPage(char *error){
        printf("<p> GOLD: %d ,  MANNA: %d \n",playerGold,playerManna);
        printf("<h3>Sorry that we couldn't code the Dino Game.</h3>\n");
        printf("<h4>%s</h4>\n",error);
        printf("</body>\n");
        printf("</html>\n");
}
        
void getResources(){
    
    FILE *f;
    f=fopen("../resources.csv", "r+");
    fscanf(f,"%d,%d,%1d",&roomManna,&roomGold,&roomOcc);
    fclose(f);
    if(roomManna<0 || roomGold<0){
        rePage("Room out of resources");
    }
    
}
void changeResourses(int n){
    FILE *fp;
    fp=fopen("../resources.csv", "w+");
    fprintf(fp,"%d,%d,%1d",roomManna,roomGold,n);
    fclose(fp);

}


void rePage(char *write){
  

    printf("<div class=\"container col-lg-6 picture_container\">\n");
    printf("</div>\n");
    printf("<div class=\"container col-lg-6 picture_container\"> \n");
    printf("</div>\n");
    printf("<div class=\"container\"><div class=\"container col-lg-3\">\n");
    printf("</div>\n");
    printf("<div class=\"jumbotron col-lg-6\">\n");
    printf("<p>%s</p>\n",write);
    
    printf("<div class=\"inventory\"><br>\n");
    printf("<br>\n");
    printf("<p>Gold: <b>%d</b></p>",playerGold);
    printf("<p>Mana: <b>%d</b></p>",playerManna);
    printf("</div>\n");
    printf("<br><br>\n");
    
   
    printf("<div class=\"row\">\n");
    printf("<center>\n");
    printf("<form action=\"http://www.cs.mcgill.ca/~hnguye124/cgi-bin/transporter.py\" method=\"post\">\n");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("<input type=\"hidden\" name =\"URL\" value=\"http://www.cs.mcgill.ca/~rgao11/cgi-bin/room.cgi\">\n");
    printf("<input type=\"hidden\" name=\"successURL\" value=\"http://cs.mcgill.ca/~hgokse/cgi-bin/success.py\">\n");
    printf("<input type=\"submit\" value=\"NORTH\">\n");
    printf("</form>\n");
    printf("<br><br>\n");
    
    printf("<form action=\"http://www.cs.mcgill.ca/~syu47/cgi-bin/transporter.py\" method=\"post\">\n");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("<input type=\"hidden\" name =\"URL\" value=\"http://www.cs.mcgill.ca/~syu47/cgi-bin/room.cgi\">\n");
    printf("<input type=\"hidden\" name=\"successURL\" value=\"http://cs.mcgill.ca/~hgokse/cgi-bin/success.py\">\n");
    printf("<input type=\"submit\" value=\"WEST\">\n");
    printf("</form>\n");
    
    printf("<form action=\"http://www.cs.mcgill.ca/~hgokse/cgi-bin/room.cgi\" method=\"post\" style=\"display: inline\">\n");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("<input type=\"text\" name =\"command\">\n");
    printf("<input type=\"submit\" value=\"SUBMIT\">\n");
    printf("</form>\n");
    
    
    printf("<form action=\"http://www.cs.mcgill.ca/~pprade/cgi-bin/transporter.py\" method=\"post\">\n");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("<input type=\"hidden\" name =\"URL\" value=\"http://www.cs.mcgill.ca/~syu47/cgi-bin/room.cgi\">\n");
    printf("<input type=\"hidden\" name=\"successURL\" value=\"http://cs.mcgill.ca/~hgokse/cgi-bin/success.py\">\n");
    printf("<input type=\"submit\" value=\"EAST\">\n");
    printf("</form>\n");
    printf("<form action=\"http://www.cs.mcgill.ca/~syu47/cgi-bin/transporter.py\" method=\"post\">\n");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("<input type=\"hidden\" name =\"URL\" value=\"http://www.cs.mcgill.ca/~syu47/cgi-bin/room.cgi\">\n");
    printf("<input type=\"hidden\" name=\"successURL\" value=\"http://cs.mcgill.ca/~hgokse/cgi-bin/success.py\">\n");
    printf("<input type=\"submit\" value=\"SOUTH\">\n");
    printf("</form>\n");
    printf("<br><br>\n");
    printf("</center>\n");
    printf("</div>\n");
    printf("<div class=\"container\">\n");
    printf("<div class=\"container col-lg-3>\"");
    printf("</body>\n");
    printf("</html>\n");
    
    
    
}
void challenge(void){
   
    
    printf("<p> GOLD: %d ,  MANNA: %d \n",playerGold,playerManna);
    printf("%s\n","<div class=\"container col-lg-6 picture_container\"></div>");
    printf("%s\n","<div class=\"container col-lg-6 picture_container\"></div>");
    printf("%s\n","<div class=\"container\"><div class=\"container col-lg-3\"><div>");
    printf("%s\n","<div class=\"jumbotron col-lg-6\">");
    printf("%s\n","<form class=\"form-inline\" action=\"http://www.cs.mcgill.ca/~hgokse/cgi-bin/game.cgi\" method=\"post\">\n");
    printf("%s\n","<h3> Welcome to the room. Best of luck! </h3>");
    printf("%s\n","<h5> There will be 3 questions to help you prep for COMP 206 Final. If you want to     quick you can type \"QUIT\" in the last text box</h5>");
    printf("%s\n","<label>Question 1: Consider the 32 bit compiler. We need to store address of integer variable to integer pointer. What will be the size of integer pointer ? </label>");
    printf("%s\n"," <input type=\"input\" name=\"q1\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("%s\n","<label>Question 2: In Bash shell, which command can create environment variable</label><br>");
    printf("%s\n"," <input type=\"input\" name=\"q2\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("%s\n","<label>Question 3: In python, which of the following function checks in a string that all characters are numeric?</label>");
    printf("%s\n"," <input type=\"input\" name=\"q3\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("<input type=\"hidden\" name=\"inventory\" value=\"%d,%d\">\n",playerManna,playerGold);
    printf("%s\n","<input type=\"submit\" value=\"SUBMIT\">\n");
    printf("%s\n","</div></div><div class=\"container\"><div class=\"container col-lg-3\">\n");
    printf("</body>\n");
    printf("</html>\n");

    
    
    
    
}
void reFresh(){
    
    if(playerGold>=100){
        //win
        
        
        
        printf("<h1> YOU WIN!!! </h1><h3> Congradulations! </h3><p>It looks like you have collected 100 gold pieces. <br>Good job!</p><p>If you want to play again, click <a href=\"http://www.cs.mcgill.ca/~hgokse/room.html\">here</a>!</p>\n");
        printf("</body>\n");
        printf("</html>\n");

    }
    else if(playerManna<=0){
        // die
       
        printf("<h1> Game over 😞 </h1><p>You do not have any manna left, so the game is over. <br>It was a good try, though! <br></p><p>If you want to start over, click <a href=http://www.cs.mcgill.ca/~hgokse/room.html\">here</a>!</p>\n");
        printf("</body>\n");
        printf("</html>\n");
        
    }
    else{
        rePage(" ");
    }
    
    
}




