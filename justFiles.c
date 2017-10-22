#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


int main(){ 

     FILE *f; 
     char buffer[100];
	f=fopen("input.txt","r");
	while(!feof(f)){ 

	fgets(buffer,100,f); 
        
	}
        for(int i=0; i<50; i++){
        printf("%s",buffer[i]);
        }
	fclose(f); 

}   
