#include <stdio.h>
char bin[24] = "";
char data;
void main(){
unsigned char a[12]="a2123d45a123";
unsigned char b[6];
int c=0;
int i=6;
printf("hi");
while(a[i]!='\0'){
    //printf("1");
    b[c]=a[i];
    printf("%d \n",b[c]);
    c++;
    
    ++i;
}
b[c]='\0';
i=0;
while(b[i] != '\0') {
      i++;
   }
   
   printf("Length of string '%s' is %d", b, i);
   



}