#include <msp430x14x.h>
#include <stdio.h>
#include "conver.h"
#include "OLED.h"
//#include "uart.h"

extern unsigned char num,key_num;
extern unsigned char Num_wei,Fvalue,D_fh;
extern int Dvalue;
extern void delay_ms(unsigned long ms); 
unsigned char set_wei(unsigned char temp_wei)
{
  unsigned char temp1;
  temp1=temp_wei;
    if(key_num==5)
  {
    temp1++;
    if(temp1>5)
    {
      temp1=0;
    }
  }
  return temp1;
}

unsigned char set_fvalue(unsigned char Fvalue )
{
  unsigned char temp,Val_Fshi,Val_Fge;;
  Val_Fshi=Fvalue/10;
  Val_Fge=Fvalue%10;
  
 if(key_num==1)
  {
   switch(Num_wei)
   {
    case 0:
      Val_Fge++;
      if(Val_Fge>9)
      {
        Val_Fge=0;
      }
    break;
    
    case 1:
      Val_Fshi++;
      if(Val_Fshi>6)
      {
        Val_Fshi=0;
      }
    break;
   }
   
  } 
   temp=Val_Fge+Val_Fshi*10;
   return temp;

}

int set_Dvalue(int Dvalue)
{
  unsigned char Val_Dbai,Val_Dshi,Val_Dge,D_fh;
  int temp;
  
  temp=Dvalue;
  if(temp<0)
  {
    temp=-temp;
    D_fh=1;
  }
  else
  {
    D_fh=0;
  }
  Val_Dbai=temp/100;
  Val_Dshi=temp/10%10;
  Val_Dge=temp%10; 

  if(key_num==1)
  {
   switch(Num_wei)
   {
      case 2:
        Val_Dge++;
        if(Val_Dge>9)
        {
          Val_Dge=0;
        }
      break;  
      
     case 3:
        Val_Dshi++;
        if(Val_Dshi>9)
        {
          Val_Dshi=0;
        }
      break; 
      
     case 4:
        Val_Dbai++;
        if(Val_Dbai>3)
        {
          Val_Dbai=0;
        }
      break;     
      
     case 5:
      if(D_fh==0)
        {
         D_fh=1;
        }
      else
        {
          D_fh=0;
        }
      break;      
   }
 }
 
  temp=Val_Dge+Val_Dshi*10+Val_Dbai*100;
  
  if(D_fh==1)
  {
    temp=-temp;
  }
  
  return temp;
}



void set_FValue()
{
  unsigned char Val_Fshi,Val_Fge;
  unsigned char Val_Dbai,Val_Dshi,Val_Dge;
  
 // SET_f=Fvalue;
  Val_Fshi=Fvalue/10;
  Val_Fge=Fvalue%10;
  
  if(Dvalue<0)
  {
    Dvalue=-Dvalue;
    D_fh=1;
  }
  else
  {
    D_fh=0;
  }
  
  Val_Dbai=Dvalue/100;
  Val_Dshi=Dvalue/10%10;
  Val_Dge=Dvalue%10;
  
  
  
/*  if(key_num==5)
  {
    Num_wei++;
    if(Num_wei>5)
    {
      Num_wei=0;
    }
  }*/
  
  if(key_num==1)
  {
   switch(Num_wei)
   {
    case 0:
      Val_Fge++;
      if(Val_Fge>9)
      {
        Val_Fge=0;
      }
    break;
    
    case 1:
      Val_Fshi++;
      if(Val_Fshi>6)
      {
        Val_Fshi=0;
      }
    break;
    
    case 2:
      Val_Dge++;
      if(Val_Dge>9)
      {
        Val_Dge=0;
      }
    break;  
    
   case 3:
      Val_Dshi++;
      if(Val_Dshi>9)
      {
        Val_Dshi=0;
      }
    break; 
    
   case 4:
      Val_Dbai++;
      if(Val_Dbai>3)
      {
        Val_Dbai=0;
      }
    break;     
    
   case 5:
    if(D_fh==0)
      {
       D_fh=1;
      }
    else
      {
        D_fh=0;
      }
    break;      
   }
 }
 
  Fvalue=Val_Fge+Val_Fshi*10;
  Dvalue=Val_Dge+Val_Dshi*10+Val_Dbai*100;
  
  if(D_fh==1)
  {
    Dvalue=-Dvalue;
  }

} 
  
void SETXS_F(unsigned char Fvalue)
{
  unsigned char temp;
  temp=Fvalue;
  
  if(num<50)
  {
    OLED_ShowNum(42,3,temp,2,16);
    OLED_ShowChar(58,3,'$',16);
  }
  else
  {
   switch(Num_wei)
     {
      case 0:
        OLED_ShowChar(50,3,' ',16);
      break;
      
      case 1:
        OLED_ShowChar(42,3,' ',16);
      break; 
     }
  }  
}

void SETXS_D(int Dvalue)
{
  int temp;
  temp=Dvalue;

  if(num<50)
   {
     if(temp<0)
     {
       temp=-temp; 
       OLED_ShowChar(2,3,'-',16);
     }
     else
     {
       OLED_ShowChar(2,3,' ',16);
     }
     
     OLED_ShowNum(10,3,temp,3,16);
     OLED_ShowChar(34,3,'!',16);
   }

   else
    {
     switch(Num_wei)
       {
        case 2:
          OLED_ShowChar(26,3,' ',16);
        break;  
        
       case 3:
          OLED_ShowChar(18,3,' ',16);
        break; 
        
       case 4:
          OLED_ShowChar(10,3,' ',16);
        break;     
        
       case 5:
          OLED_ShowChar(2,3,' ',16);
       break;      
       }
    }   
}



void SETXS_FF()
{
 
  if(num<50)
   {
     if(Dvalue<0)
     {
       Dvalue=-Dvalue; 
       OLED_ShowChar(2,3,'-',16);
     }
     else
     {
       OLED_ShowChar(2,3,' ',16);
     }
     
     OLED_ShowNum(10,3,Dvalue,3,16);
     OLED_ShowNum(42,3,Fvalue,2,16);
     
     OLED_ShowChar(34,3,'!',16);
     OLED_ShowChar(58,3,'$',16);
     

   }
  else
  {
   switch(Num_wei)
     {
      case 0:
        OLED_ShowChar(50,3,' ',16);
      break;
      
      case 1:
        OLED_ShowChar(42,3,' ',16);
      break;
      
      case 2:
        OLED_ShowChar(26,3,' ',16);
      break;  
      
     case 3:
        OLED_ShowChar(18,3,' ',16);
      break; 
      
     case 4:
        OLED_ShowChar(10,3,' ',16);
      break;     
      
     case 5:
        OLED_ShowChar(2,3,' ',16);
     break;      
     }   
     
  }
  

}

void set_enter()
{
    OLED_ShowChar(90,3,' ',16);
    OLED_ShowChar(98,3,' ',16);
    OLED_ShowChar(106,3,' ',16);
    OLED_ShowChar(114,3,' ',16);
    
    OLED_ShowChar(98,3,'O',16);//O
    OLED_ShowChar(106,3,'K',16);//K
      
    delay_ms(1000);
      
    OLED_ShowChar(90,3,' ',16);
    OLED_ShowChar(106,3,' ',16);
    OLED_ShowCHinese(90,3,36);//х╥
    OLED_ShowCHinese(106,3,37);//хо 

}
