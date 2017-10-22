#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000
#define SIZE 8

int renderController(int state);
void renderInitState();
void renderGameSuccess();
void renderRedirectionPage();
void refreshGame();
void renderGameOver();
void renderGameExit();
void renderGameWon();
void unencode(char *src, int len, char *dest);
void getInput();

char *contLenc;
int contLen;
char command[SIZE];
char inventory[SIZE];
char input[MAX];
int goldDrop;
int tempManna;

int roomGold;
int playerGold;

int playerManna;
int roomManna;

int roomOcc; //if the room occupied 1 for occupied, 0 for not occupied

//char *data = NULL;

// for questions
char q1[SIZE];
char q2[SIZE];
char q3[SIZE];

int main(int argc, const char * argv[]) {
    
    getInput();
    
    printf("%s\n\n","Content-Type:text/html");
    printf("%s","<Doctype html>");
    printf("%s","<html><head><meta charset=\"utf-8\"><title>Game</title>");
    printf("%s","<meta name=\"description\" content=\"A game room for COMP 206 Group Project\">");
    printf("%s","<link rel=\"stylesheet\" href=\"css/bootstrap.min.css\"><link rel=\"stylesheet\" href=\"css/main.css\">");
    printf("%s","</head><body><div class=\"container col-lg-6 picture_container\"></div>");
    printf("%s","<div class=\"container col-lg-6 picture_container\"></div>");
    printf("%s","<div class=\"container\"><div class=\"container col-lg-3\"><div>");
    printf("%s","<div class=\"jumbotron col-lg-6\">");
    
    // take this out when deploying
    FILE *f;
    f=fopen("../resources.csv","r+");
    fscanf(f,"%d,%d,%1d",&roomManna,&roomGold,&roomOcc);
    
    
    if( (strncmp(q1,"2",1)  ==0) &&(strncmp(q2,"export",6)==0)&& (strncmp(q3, "isNumeric",9)==0)){
            // player answer with success
            renderController(1);
        }
        else if(strcmp(q3,"EXIT")){
            renderController(5);
            // TODO: add manna and gold to csv
            
        }else{
            renderController(3);
        }

}


int renderController(int state){
    switch (state) {
        case 0:
            renderInitState();
            break;
        case 1:
            renderGameSuccess();
            break;
        case 2:
            renderRedirectionPage();
            break;
        case 3:
            refreshGame();
            break;
        case 4:
            renderGameOver();
            break;
        case 5:
            renderGameExit();
            break;
        default:
            refreshGame();
            break;
    }
    return 0;
}

void getInput(){
    contLenc=getenv("CONTENT_LENGTH");
    if(contLenc==NULL || sscanf(contLenc,"%d",&contLen)!=1 || contLen>MAX){
        //errorPage("Error Reading the Page");
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
        q1[j]=input[i];
        i++; j++;
    }
    q1[j]='\0';
    
    while(input[i]!='='){
        i++;
    }
    i++;
    j=0;
    while(input[i]!='&'){
        q2[j]=input[i];
        i++; j++;
    }
    q2[j]='\0';
    
    
    while(input[i]!='='){
        i++;
    }
    i++;
    
    while(input[i]!='\0'){
        q3[k]=input[i];
        i++, k++;
    }
    q3[k]='\0';
    
}

void renderInitState(){
   
    printf("%s","<form class=\"form-inline\" action=\"http://www.cs.mcgill.ca/~hgokse/cgi-bin/game.cgi\" method=\"get\">");
    printf("%s","<h3> Welcome to the room. Best of luck! </h3>");
    printf("%s","<h5> There will be 3 questions to help you prep for COMP 206 Final. If you want to     quick you can type \"QUIT\" in the last text box</h5>");
    printf("%s","<label>Question 1: Consider the 32 bit compiler. We need to store address of integer variable to integer pointer. What will be the size of integer pointer ? </label>");
    printf("%s"," <input type=\"input\" name=\"q1\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("%s","<label>Question 2: In Bash shell, which command can create environment variable</label><br>");
    printf("%s"," <input type=\"input\" name=\"q2\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("%s","<label>Question 3: In python, which of the following function checks in a string that all characters are numeric?</label>");
    printf("%s"," <input type=\"input\" name=\"q3\" class=\"form-control\" id=\"user_input\" placeholder=\"Input answer here\"><br>");
    printf("%s","<input type=\"submit\" value=\"SUBMIT\">\n");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body>");
    printf("%s","</html>");
    
}

void renderGameSuccess(){
   
    printf("%s","<div class=\"row\">");
    printf("%s","<h5> You have succeeded the game! You can get at most 5 piece of gold, manna or both. Please type how much gold you want and then click submit before you go to another room! If you enter 2 then you will get 2 pieces of gold and 3 pieces of manna. If you enter more than 5 then you will get 5 pieces of gold by defualt, if you enter 0 then you will get 5 pieces of manna by default</h5>");
    printf("%s","<form action=\"http://www.cs.mcgill.ca/~hgokse/cgi-bin/game.cgi\" class=\"form\"><input type=\"input\" name=\"command\" class=\"form-control\" id=\"user_input\" placeholder=\"Type how much gold you want.\">");
    printf("%s","<input type=\"submit\" value=\"SUBMIT\">\n");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}

void renderRedirectionPage(){
   
    printf("%s","<p> Successfully obtained gold and manna! You can now leave in peace and continue your journey");
    
    printf("%s","<form class=\"form-inline\"><button name=\"north\" formaction=\"http://www.cs.mcgill.ca/~NORTHROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">North</button><input type=\"hidden\" name=\"inventory\" value=\"10,10\"></form>");
    
    printf("%s","<form class=\"form-inline\"><button name=\"west\" formaction=\"http://www.cs.mcgill.ca/~WESTROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">West</button><input type=\"hidden\" name=\"inventory\" value=\"10,10\"></form>");
    
    printf("%s","<form class=\"form-inline\"><button name=\"east\" formaction=\"http://www.cs.mcgill.ca/~EASTROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">East</button><input type=\"hidden\" name=\"inventory\" value=\"10,10\"></form>");
    
    printf("%s","<form class=\"form-inline\"><button name=\"south\" formaction=\"www.cs.mcgill.ca/~SOUTHROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">South</button><input type=\"hidden\" name=\"inventory\" value=\"10,10\"></form>");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}

void refreshGame(){

    
    printf("%s","<form class=\"form-inline\"><button name=\"north\" formaction=\"http://www.cs.mcgill.ca/~NORTHROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">North</button><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></form>",playerGold,playerManna);
    
    printf("%s","<form class=\"form-inline\"><button name=\"west\" formaction=\"http://www.cs.mcgill.ca/~WESTROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">West</button><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></form>",playerGold,playerManna);
    
    printf("%s"," <form class=\"form-inline\"><input type=\"input\" name=\"command\" class=\"form-control\" id=\"user_input\" placeholder=\"Input command here\"></form>");
    
    printf("%s","<form class=\"form-inline\"><button name=\"east\" formaction=\"http://www.cs.mcgill.ca/~EASTROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">East</button><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"></form>",playerGold,playerManna);
    
    printf("%s","<form class=\"form-inline\"><button name=\"south\" formaction=\"www.cs.mcgill.ca/~SOUTHROOM/cgi-bin/transporter.py\" method=\"get\" class=\"btn btn-primary\">South</button><input type=\"hidden\" name=\"inventory\" value=\"10,10\"></form>");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}

void renderGameOver(){
    
    printf("%s","<div class=\"row\">");
    printf("%s","<h4>Sorry your manna has reached 0! Game is now over</h5>");
    printf("%s","<h5>Success is not final, failure is not fatal: it is the courage to continue that counts. - Winston Churchill</h5>");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}

void renderGameExit(){
   
    printf("%s","<div class=\"row\">");
    printf("%s","<h4>Sorry to see you go!</h5>");
    printf("%s","<h5>Your manna and gold has been returned to the universe</h5>");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}

void renderGameWon(){
   
    printf("%s","<div class=\"row\">");
    printf("%s","<h4>You won!</h5>");
    printf("%s","<h5>\"Success is not the key to happiness. Happiness is the key to success. If you love what you are doing, you will be successful.\"– Herman Cain</h5>");
    printf("%s","</div></div><div class=\"container\"><div class=\"container col-lg-3\"></body></html>");
}


           


