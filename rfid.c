#include <stdio.h>
char bin[24] = "";
char data[16];
void main(){
   char input[6] = "BD7AB7";
   int output = hextobin(input);
   printf(" \n ---------------");
   printf(output);
   printf(" \n ---------------");
   int decimal_output = binToCard(output);
   printf("\n %d",decimal_output);

}

 int hextobin(char hex[6]) {
    for(int i=0;i<6;i++){

        switch (hex[i]){
            case '0':  strcat(bin,"0000")  ; break;
            case '1': strcat(bin,"0001")  ; break;
            case '2':  strcat(bin,"0010")  ; break;
            case '3':  strcat(bin,"0011")  ; break;
            case '4':  strcat(bin,"0100")  ; break;
            case '5':  strcat(bin,"0101")  ; break;
            case '6':  strcat(bin,"0110")  ; break;
            case '7':  strcat(bin,"0111")  ; break;
            case '8':  strcat(bin,"1000")  ; break;
            case '9':  strcat(bin,"1001")  ; break;
            case 'A':  strcat(bin,"1010")  ; break;
            case 'B':  strcat(bin,"1011")  ; break;
            case 'C':  strcat(bin,"1100")  ; break;
            case 'D':  strcat(bin,"1101")  ; break;
            case 'E':  strcat(bin,"1110")  ; break;
            case 'F':  strcat(bin,"1111")  ; break;
        }
    }
int c=0;
int i=9;

while(bin[i]!='\0'){
    data[c]=bin[i];
    c++;
    ++i;
}
data[c]='\0';
i=0;
   return data;
}

int binToCard (char n[]){
    int dec = 0;
    int i=0;
//24
    printf(n);
    int base = 16384;
    while(n[i] != '\0' ) {
        printf("\n %d ", n[i]-48);
        dec += (n[i]-48) * (base);
        base = base/2;
       i++;
    }
    return dec;
}

