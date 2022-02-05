#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//README -> MENTIONED AS COMMENTS

//Temporary Array (Not Required) -> Just for Passing
int Nul[1]={0};

//PC -> INT
int PC;

//Rest All Variables are in HEXADECIMAL
int ac[10];
int mar[10];
int Stor[10];
char decode;
int rightaddress[3];

/*
Left Instruction 00000 -> NOP
Instruction 1111111111 -> exit(Halt)
*/

//Memory Instructions
int M1[10]={0x0,0xA,0x0,0x0,0xB,0x0,0x5,0x0,0x0,0xC};
int M2[10]={0x0,0x0,0x0,0x0,0x0,0x2,0x1,0x0,0x0,0xD};
int M3[10]={0x0,0xA,0x0,0x0,0xC,0x0,0x5,0x0,0x0,0xD};
int M4[10]={0x0,0x0,0x0,0x0,0x0,0x2,0x1,0x0,0x0,0xB};
int M5[10]={0x0,0xA,0x0,0x0,0xB,0x0,0x6,0x0,0x0,0xD};
int M6[10]={0x0,0x0,0x0,0x0,0x0,0x2,0x1,0x0,0x0,0xC};
int M7[10]={0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
//Memory Data
int M11[10]={0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x6};
int M12[10]={0x8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x4};
int M13[10]={0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};//Halt

int msb(int arr[]);
int hex_dec(int arr[],int n);
void dec_to_hex(int result);

void Memory(int i, int mar[]);
void MBR(int flag, int M[]);
void IBR(int rhs[]);
void IR_decode(int op_code[]);
void ALC(char c,int M[]);
void MAR(int i, int PC, int address[]);

//Returns 1 if msb is 0(positive no.) else -1 if msb is 1(negative no.)
int msb(int arr[])
{
    int x = (arr[0]/8);
    if(x==0)
        return 1;
    else
        return -1;
}

//Hexadecimal to Decimal
int hex_dec(int arr[],int n)
{
    int value=0;
    for(int i=0;i<n;i++)
    {
        value = value*16 + arr[i];
    }
    return value;

}

//Dec to Hexadecimal
void dec_to_hex(int result)
{
    //1st bit is signed bit
    //39 bits -> Operation
    if(result>=0)
    {
        if(ac[0]>=8)
            ac[0] -= 8;
        int quotient,remainder;
        quotient = result;
        char hexadecimalnum[10];
        int i, j;
        i=0;
        j=9;
        while (quotient != 0)
        {
            remainder = quotient % 16;
            if (remainder < 10)
                hexadecimalnum[j--] = 48 + remainder;
            else
                hexadecimalnum[j--] = 55 + remainder;
            quotient = quotient / 16;
        }
        for(int k=j;k>=0;k--)
        {  
            hexadecimalnum[k]=0;
        }

        int k=0;
        for(;k<10;k++)
        {
            switch(hexadecimalnum[k])
            {
                case '0':
                {
                    ac[k]=0x0;
                    break;
                }
                case '1':
                {
                    ac[k]=0x1;
                    break;
                }
                case '2':
                {
                    ac[k]=0x2;
                    break;
                }
                case '3':
                {
                    ac[k]=0x3;
                    break;
                }
                case '4':
                {
                    ac[k]=0x4;
                    break;
                }
                case '5':
                {
                    ac[k]=0x5;
                    break;
                }
                case '6':
                {
                    ac[k]=0x6;
                    break;
                }
                case '7':
                {
                    ac[k]=0x7;
                    break;
                }
                case '8':
                {
                    ac[k]=0x8;
                    break;
                }
                case '9':
                {
                    ac[k]=0x9;
                    break;
                }
                case 'A':
                {
                    ac[k]=0xA;
                    break;
                }
                case 'B':
                {
                    ac[k]=0xB;
                    break;
                }
                case 'C':
                {
                    ac[k]=0xC;
                    break;
                }
                case 'D':
                {
                    ac[k]=0xD;
                    break;
                }
                case 'E':
                {
                    ac[k]=0xE;
                    break;
                }
                case 'F':
                {
                    ac[k]=0xF;
                    break;
                }
            }
        }
    }
    else if(result < 0)
    {
        if(ac[0]>=8)
            ac[0] -= 8;
        int quotient,remainder;
        quotient = -result;
        char hexadecimalnum[10];
        int i, j;
        i=0;
        j=9;
        while (quotient != 0)
        {
            remainder = quotient % 16;
            if (remainder < 10)
                hexadecimalnum[j--] = 48 + remainder;
            else
                hexadecimalnum[j--] = 55 + remainder;
            quotient = quotient / 16;
            }
        for(int k=j;k>=0;k--)
        {  
            hexadecimalnum[k]=0;
        }


        int k=0;
        for(;k<10;k++)
        {
            switch(hexadecimalnum[k])
            {
                case '0':
                {
                    ac[k]=0x0;
                    break;
                }
                case '1':
                {
                    ac[k]=0x1;
                    break;
                }
                case '2':
                {
                    ac[k]=0x2;
                    break;
                }
                case '3':
                {
                    ac[k]=0x3;
                    break;
                }
                case '4':
                {
                    ac[k]=0x4;
                    break;
                }
                case '5':
                {
                    ac[k]=0x5;
                    break;
                }
                case '6':
                {
                    ac[k]=0x6;
                    break;
                }
                case '7':
                {
                    ac[k]=0x7;
                    break;
                }
                case '8':
                {
                    ac[k]=0x8;
                    break;
                }
                case '9':
                {
                    ac[k]=0x9;
                    break;
                }
                case 'A':
                {
                    ac[k]=0xA;
                    break;
                }
                case 'B':
                {
                    ac[k]=0xB;
                    break;
                }
                case 'C':
                {
                    ac[k]=0xC;
                    break;
                }
                case 'D':
                {
                    ac[k]=0xD;
                    break;
                }
                case 'E':
                {
                    ac[k]=0xE;
                    break;
                }
                case 'F':
                {
                    ac[k]=0xF;
                    break;
                }
            }
        }
        ac[0] += 8;
    }
}

//Memory
//Only int array MAR will go
void Memory(int i, int mar[])
{
    //PC is always greater than 0
    //0 ownwards there r instructions in memory
    //from x onwards we r storing data in memory
    //x=10
    //PC is stored in mar[0]
    int n;
    if(i==0)
    {
        n=PC;
    }
        
    //Instruction Fetch
    else if(i==1)
    {
        int temp[3];
        for(int j=0;j<3;j++)
            temp[j]=mar[j];
        n = hex_dec(temp,3);
    }

    
    //STORE
    else if(i==2)
    {
        int temp[3];
        for(int j=0;j<3;j++)
            temp[j]=mar[j];
        n = hex_dec(temp,3);
    }
  
    switch(n)
    {
        //Instruction
        case 1:
        {
            MBR(0,M1);
            break;
        }
        case 2:
        {
            MBR(0,M2);
            break;
        }
        case 3:
        {
            MBR(0,M3);
            break;
        }
        case 4:
        {
            MBR(0,M4);
            break;
        }
        case 5:
        {
            MBR(0,M5);
            break;
        }
        case 6:
        {
            MBR(0,M6);
            break;
        }
        case 7:
        {
            MBR(0,M7);
            break;
        }
            
        //Data
        //if i==2 -> Store
        case 11:
        {
            if(i != 2)
                MBR(1,M11);
            else
                MBR(5,M11);
            break;
        }
        case 12:
        {
            if(i != 2)
                MBR(1,M12);
            else
                MBR(5,M12);
            break;

        }
        case 13:
        {
            if(i != 2)
                MBR(1,M13);
            else
                MBR(5,M13);
            break;

        }
    }
	
}


/*
 If memory is accesses (obv it will by MAR) then the values gets stored in MBR
 Values are stored in MBR if
 1.Fetching Instruction
 MBR <-- M[MAR] (2 times this instr may occur) -> To store Left instruction or Data
 2.Storing Value in Memory
 MBR <-- AC
 
 Passing
 1.To store Left instruction
 IBR <-- MBR[20:39]
 IR <-- MBR[0:7]
 MAR <-- MBR[8:19]
 2.To perform Operation
 i. Load = AC <-- MBR
 ii. Add = AC<- AC+ MBR
 iii. Store = MBR <-- AC
              M[MAR] <--MBR
 */
void MBR(int flag, int M[])
{
    //General
    int mbr[10];
    for(int i=0;i<10;i++)
        mbr[i]=M[i];
    
    //Store
    if(flag==4)
    {
        for(int i=0;i<10;i++)
            Stor[i]=M[i];
        
        Memory(2,mar);
    }
    if(flag == 5)
    {
        for(int i=0;i<10;i++)
            M[i]=Stor[i];
    }

    //Data
    if(flag==1)
    {
        ALC('X',M);
    }

    //Check Halt
    int x=0;
    for(int i=0;i<10;i++)
    {
        if(M[i]==0x1)
        {
            x++;
        }
    }
    if(x==10)
    {
        printf("PROGRAM ENDED\n");
        exit(0);
    }

    //Check NOP
    if(flag != 1){
    x=0;
    for(int i=0;i<5;i++)
    {
        if(M[i]==0x0)
        {
            x++;
        }
    }
    if(x==5)
    {
        flag=3;
        int temp_op[2];
        for(int i=0,j=5;i<2;i++,j++)
            temp_op[i]=M[j];
        IR_decode(temp_op);
        if(decode == 'S')
            flag = 3;
        else 
            flag = 6;
    }}

    //NOP
    if(flag==3)
    {
        int add[3];
        for(int i=0,j=7;i<3;i++,j++)
            add[i]=M[j];
        MAR(2,0,add);
        int op_code[2];
        for(int i=0,j=5;i<2;i++,j++)
            op_code[i]=M[j];
        IR_decode(op_code);
    }
    
	if(flag==0)
	{
        int rhs[5];
        for(int i=0,j=5;i<5;i++,j++)
            rhs[i]=M[j];
        int lhs_op[2];
        for(int i=0;i<2;i++)
            lhs_op[i]=M[i];
        IR_decode(lhs_op);
        if(decode=='S')
        {
            flag = 2;
        }
        else
        {
            int lhs_ad[3];
            for(int i=0,j=2;i<3;i++,j++)
                lhs_ad[i]=M[j];
            MAR(1,0,lhs_ad);
            IBR(rhs);    
        }
        
	}

    if(flag==2)
    {
        int add[3];
        for(int i=0,j=7;i<3;i++,j++)
            add[i]=M[j];
        MAR(2,0,add);
        for(int u=0;u<3;u++)
            rightaddress[u]=mar[u];
        int op_code[2];
        for(int i=0,j=5;i<2;i++,j++)
            op_code[i]=M[j];
        IR_decode(op_code);
        
    }

    if(flag==6)
    {
        int temp_ra[5];
        for(int i=0,j=5;i<5;i++,j++)
            temp_ra[i]=M[j];
        IBR(temp_ra);
    }
	
}

//If Right Instruction is Present
void IBR(int rhs[])
{
    int ibr[5];
    for(int i=0;i<5;i++)
        ibr[i]=rhs[i];
    printf("IBR = ");
    for(int i=0;i<5;i++)
        printf("%X",ibr[i]);
    printf(" ");
	int opcode[2];
	for(int i=0;i<2;i++)
		opcode[i]=ibr[i];
	IR_decode(opcode);
    if(decode != 'S')
    {
        for(int i=2,j=0;i<5;j++,i++)
            rightaddress[j]=ibr[i];
        MAR(1, 0, rightaddress);    
    }
}

//Decode and then pass to Arithmetic Logic Circuit
void IR_decode(int op_code[])
{
    printf("opcode = ");
    for(int w=0;w<2;w++)
    {
        printf("%X",op_code[w]);       
    }   
    printf(" ");
	int i=0;
    //Decode OP Code
    int load[2]={0x0,0xA};
    int add[2]={0x0,0x5};
    int store[2]={0x2,0x1};
    int sub[2]={0x0,0x6};
	for(i=0;i<2;i++)
	{
		if(op_code[i]==load[i])
			continue;
		else
			break;
	}
	if(i==2)
    {
        ALC('L',Nul);
    }
		
      
    //ADD
    for(i=0;i<2;i++)
    {
        if(op_code[i]==add[i])
            continue;
        else
            break;
    }
    if(i==2)
    {
        ALC('A',Nul);
    }
        
       
    //STORE
    for(i=0;i<2;i++)
    {
        if(op_code[i]==store[i])
            continue;
        else
            break;
    }
    if(i==2)
    {
        ALC('S',Nul);
    }
	
    //SUB
    for(i=0;i<2;i++)
    {
        if(op_code[i]==sub[i])
            continue;
        else
            break;
    }
    if(i==2)
    {
        //M for Minus
        ALC('M',Nul);
    }
    // same for other opcodes
}

//Arithmetic Logic Circuit
//Operations are performed in this block
void ALC(char c,int M[])
{
    //LOAD
	if(c=='L')
        decode='L';
    if(decode =='L' && c=='X')
    {
        for(int i=0;i<10;i++)
        {
            ac[i]=M[i];
        }
    }
        
    //ADD
    if(c=='A')
        decode='A';
    if(decode =='A' && c=='X')
    {
        int result;
        result = msb(ac)*hex_dec(ac,10) + msb(M)*hex_dec(M,10);
        dec_to_hex(result);
    }

    //SUB
    if(c=='M')
        decode='M';
    if(decode =='M' && c=='X')
    {
        int result;
        result = msb(ac)*hex_dec(ac,10) - msb(M)*hex_dec(M,10);
        dec_to_hex(result);
    }
    
    //STORE
    
    if(c=='S')
    {
        MBR(4,ac);
        decode = 'S';
    }

}

/*
 Values get stored in MAR if
 IF NOP is NOT Present
 1. MAR <-- PC
 2. MAR <-- MBR[8:19]
 3. MAR <-- IBR[8:19]
 IF NOP is present
 MAR <-- MBR[29:39]
 
 Values are passed when
 For Left only
 Instruction Fetch
 Memory < -- MAR
 MBR <-- M[MAR]
 Once again for Data Fetch
 Memory < -- MAR
 MBR <-- M[MAR]
 
 MAR ALWAYS goes to Memory and stores value in MBR
 */
void MAR(int i, int PC, int address[])
{
    //i is to check whether PC is there or add is there in MAR
    // i = 0 -> PC
    // i = 1 -> Address
    
	if(i==0)
    {
        mar[0]=PC;
        Memory(i, mar);
    }
    
    //for add or load
	else if(i==1)
    {
        for(int i=0;i<3;i++)
            mar[i]=address[i];
		Memory(i, mar);
    }
    //for store
    else if(i==2)
    {
        for(int i=0;i<3;i++)
            mar[i]=address[i];
    }
    printf("MAR = ");
    for(int j=0;j<3;j++)
    {
        printf("%X",mar[j]);
    }
    printf(" ");
}

int main()
{
    //n is no. of times PC willl be incremented
	int n=7;
	PC=1;
    for(int i=1;i<=n;i++)
    {
        printf("\nPC = %d\n",PC);
        MAR(0, PC, Nul); 
        PC++;
        printf("AC = ");
        for(int j=0;j<10;j++)
        {
            printf("%X",ac[j]);
        }
        printf(" ");
        printf("\n");
        printf("M(11) = ");
        for(int i=0;i<10;i++)
        {
            printf("%X", M11[i]);
        }
        printf("\n");
        printf("M(12) = ");
        for(int i=0;i<10;i++)
        {
            printf("%X", M12[i]);
        }
        printf("\n");
        printf("M(13) = ");
        for(int i=0;i<10;i++)
        {
            printf("%X", M13[i]);
        }
    }
    printf("\n");
    return 0;
}
	

