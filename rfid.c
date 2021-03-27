#include<reg51.h>
#include<string.h>
#include<stdio.h>
#define lcdport P1

sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit m1=P2^4;
sbit m2=P2^5;
sbit buzzer=P2^6;
int i,c,dec,base;
char rx_data[50];
char rfid[13],ch=0,input[6];
int count1, count2, count3;
unsigned char result[1];
unsigned char output,decimaloutput;
unsigned char xdata bin[24], temp[16];


 void delay(int itime)
{
    int i,j;
    for(i=0;i<itime;i++)
    for(j=0;j<1275;j++);
}

void daten()
{
    rs=1;
    rw=0;
    en=1;
    delay(5);
    en=0;
}

void lcddata(unsigned char ch)
{
    lcdport=ch & 0xf0;
    daten();
    lcdport=(ch<<4) & 0xf0;
    daten();
}

void cmden(void)
{
    rs=0;
    en=1;
    delay(5);
    en=0;
}

void lcdcmd(unsigned char ch)
{
    lcdport=ch & 0xf0;
    cmden();
    lcdport=(ch<<4) & 0xf0;
    cmden();
}

void lcdstring(char *str)
{
    while(*str)
    {
        lcddata(*str);
        str++;
    }
}

void lcd_init(void)
{
    lcdcmd(0x02);
    lcdcmd(0x28);
    lcdcmd(0x0e);
    lcdcmd(0x01);
}

void uart_init()
{
 TMOD=0x20;
 SCON=0x50;
 TH1=0xfd;
 TR1=1;
}
char rxdata()
{
  while(!RI);
    ch=SBUF;    
    RI=0;
    return ch;
}
//hexadecimal to binary
 int hextobin(char hex[6]) {
    for( i=0;i<6;i++){

        switch (hex[i]){
            case '0':  strcat(bin,"0000")  ; break;
            case '1':  strcat(bin,"0001")  ; break;
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
		c=0;
		i=9;
		while(bin[i]!='\0'){
			temp[c]=bin[i];
			c++;
			++i;
		}
		temp[c]='\0';
		i=0;
    return temp;
}


int bintocard(char n[]){
    dec = 0;
    i=0;
    base = 16384;
    while(n[i] != '\0' ) {
        dec += (n[i]-48)*(base);
        base = base/2;
        i++;
    }
    return dec;
}




void main()
{
    buzzer=1;
    uart_init();
    lcd_init();
    lcdstring("  RFID Based    ");
    lcdcmd(0xc0);
    lcdstring("Attendance Systm"); 
    delay(400);
    while(1)
    {
        lcdcmd(1);
        lcdstring("Place Your Card:");
        lcdcmd(0xc0);
        i=0;
        for(i=0;i<12;i++)
        rfid[i]=rxdata();
        rfid[i]='\0';
        lcdcmd(1);
        lcdstring("Your ID No. is:");
        lcdcmd(0xc0);
				i=0;
        for(i=7;i<12;i++)
        lcddata(rfid[i]);
        delay(2000);
				lcdcmd(0xc0);
			//input maker
			  c=0;
			  i=6;
				while(rfid[i]!='\0'){
				input[c]=rfid[i];
				c++;
				++i;
				}
				input[c]='\0';
				i=0;
				lcdstring(input);//done
				//function calling
				output=hextobin(input);
				lcdcmd(0xc0);
				decimaloutput = bintocard(output);
				lcdstring(decimaloutput);

			if(strncmp(rfid,"160066A5EC39",12)==0)
        {
            count1++;
            lcdcmd(1);
            lcdstring(" Attendance ");
            lcdcmd(0xc0);
            lcdstring(" Registered");
            delay(200);
            lcdcmd(1);
            lcdstring(" Student1 ");
            lcdcmd(0xc0);
            lcdstring("Attnd. No.: ");
            sprintf(result, "%d", count1);
            lcdstring(result);
            
            m1=1;
            m2=0;
            delay(300);
            m1=0;
            m2=0;
            delay(200);
            m1=0;
            m2=1;
            delay(300);
            m1=0;
            m2=0;
        }
        
        
        else 
        {
           lcdcmd(1);
           lcdstring("Invalid Card");
           buzzer=0;
           delay(300);
           buzzer=1;
        }
  }
}