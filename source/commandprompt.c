/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Lecture given by Professor.Lalit Pandit
 * 			  https://javatutoring.com/c-program-trim-leading-and-trailing-white-space-characters-from-string/
 * 			  -for trimming trailing and leading zeros
 *
 *
 * Description: Includes Function definition of all the command processing functions
 */
#include "UARTcomm.h"
#include "circularbufferqueue.h"
#include "commandprompt.h"
#include "string.h"
#include "stdio.h"

#define MAX_CMDS 20
#define MAX_LENGTH 640
// receives command data from the user
char cmd;

/**************************************************************************************/
								/*FUNCTION DEFINITIONS*/
/**************************************************************************************/

/* Function: trim()
 *
 * Param: *str(address of the string)
 *
 * return: void
 *
 * Description:Trim trailing and leading spaces from the string
 */
void trim(char * str)
{
    int index, i;

    /*
     * Trim leading white spaces
     */
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    /* Shift all trailing characters to its left */
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL


    /*
     * Trim trailing white spaces
     */
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }

    /* Mark the next character to last non white space character as NULL */
    str[index + 1] = '\0';
}

/* Function: strtodecimal()
 *
 * Param: char *s(address of the string),int addr_flag
 *
 * return: int(decimal value)
 *
 * Description:Convert string to decimal
 */
int strtodecimal(char* s,int addr_flag)
{
	int hexflag =0;
	int numvalue = 0;
	int i=0;
	int base = 1;

	if(s[1] =='x')
	{
		hexflag = 1;
	}
	//If the value received is hex or if it is a start address then do operation from hex to decimal.
	if(hexflag ==1||addr_flag ==1)
	{
		for(i = strlen(s)-1; i>=0 ;i--)
		{
			if(s[i] >= '0' && s[i] <= '9')
			{
				numvalue += (s[i] - 48) * base;
				base *= 16;
			}
			else if(s[i] >= 'a' && s[i] <= 'f')
			{
				numvalue += (s[i] - 87) * base;
				base *= 16;
			}
		}
		return numvalue;
	}
	//Enter if the string is a decimal string.
	else
	{
		for(i = strlen(s)-1; i>=0 ;i--)
		{
			if(s[i] >= '0' && s[i] <= '9')
			{
				numvalue += (s[i] - 48) * base;
				base *= 10;
			}
		}
		return numvalue;
	}
}

/* Function: hexdump()
 *
 * Param: int start_address,int length
 *
 * return: void
 *
 * Description:Output Hex Dump
 */
void hexdump(int start_address,int length)
{
	    int rows_required = 1;
	    int data_count =  length;
	    while(data_count - 16 >=0)
	    {
	        data_count = data_count - 16;
	        rows_required++;// provides loop value for outer loop
	    }
	    data_count = length;
	    printf("\n\r");
	    //outer loop for printing address
	    for(uint16_t i = 0; i < rows_required ; i++)
	    {
	        if(data_count != 0)
	        {
	            //Prints the Address in AAA format
	            printf(" 0000_%04x    ",(start_address +16*i));
	        }
	        /*Loop for printing the data*/
	        for(uint16_t j = i*16; j < (16*(i+1)) ; j++)
	        {
	            if(data_count != 0)
	            {
	                //Prints 16 bytes of data
	                printf(" %02x    ", *((uint8_t*)start_address+j));
	                data_count--;
	            }
	        }
	       printf("\n\r");
	    }
}

/* Function: authorcommand()
 *
 * Param: char*
 *
 * return: void
 *
 * Description: Check if author command received is correct. If it is correct then process the command
 */
void authorcommand(char *argv)
{
	int cmp;
	// compare if the command received is author
	cmp =strcmp(argv,"author");
	printf("\n\r");
	//If valid command enter if
	if(cmp== 0)
	{
		printf("Raghu Sai Phani Sriraj Vemparala\n\r");
	}
	else
	{
		printf("Invalid Command\n\r");
	}
	printf("\n\r");
}

/* Function: helpcommand()
 *
 * Param: char*
 *
 * return: void
 *
 * Description: Check if help command received is correct. If it is correct then process the command
 */
void helpcommand(char *argv)
{
	int cmp;
	// compare if the command received is author
	cmp =strcmp(argv,"help");
	printf("\n\r");
	//If valid command enter if
	if(cmp== 0)
	{
		printf("The supported commands are:\n\r");
		printf("Command:Author\n\r");
		printf("Functionality: Prints Name of Author\n\r");
		printf("Command: Dump <Start_address> <Length>\n\r");
		printf("Functionality: It will provide values hex values from the memory starting from the start address till the length of bytes\n\r");
		printf("Command: Help\n\r");
		printf("Functionality: Help Menu that provides user info with commands available\n\r");
	}
	else
	{
		printf("Invalid Command\n\r");
	}
	printf("\n\r");
}

/* Function: dumpcommand()
 *
 * Param: char *command, char* address, char* length
 *
 * return: void
 *
 * Description: Provides the hex dump on receiving the dump command with proper address and length
 */
void dumpcommand(char* command, char* address, char* length)
{
	int i =0;
	int cmp;
	//To check that address is passed or length is passed to functions
	int address_flag = 1;
	int addr_dec_value=0;
	int length_dec_value=0;
	cmp =strcmp(command,"dump");
	printf("\n\r");
	if(cmp== 0)
	{
		/*Do Nothing*/
	}
	else
	{
		printf("Invalid Command\n\r");
		return;
	}
	//Check if the start address is valid or not
	for(i = 0; i<strlen(address);i++)
	{
		if(((address[i]>='a')&&(address[i]<='f'))||((address[i]>='0')&&(address[i]<='9')))
		{
			/*Do Nothing*/
		}
		else
		{
			printf("Invalid address\n\r");
			return;
		}
	}
	//decimal value of start address
	addr_dec_value = strtodecimal(address,address_flag);
	//decimal value of length
	length_dec_value = strtodecimal(length,0);
	if(length_dec_value > MAX_LENGTH)
	{
		printf("Exceeded Maximum Length of 640\n\r");
		return;
	}
	//hexdump
	hexdump(addr_dec_value, length_dec_value);
}

/* Function: commandprompt()
 *
 * Param: NIL
 *
 * return: void
 *
 * Description: Start of command processing
 */
void commandprompt()
{
	char *inputstr;
	char *endl;
	//To detect if space is pressed
	int space_flag =0;
	//Pointer array to char to store the string addresses
	char *argv[MAX_CMDS];
	int argc = 0;
		// find end of string

	char str[256];
	int i =0;
	printf("?");
	//get character from user
	cmd = getchar();
	//loop until ENTER character is pressed
	while(cmd!='\r')
	{
		//Convert capital alphabets to small alphabets
		if((cmd>= 'A') && (cmd <='Z'))
		{
			cmd = cmd + 32;
		}
		//If backspace is detected go back to previous character location
		if(cmd == 0x08)
		{
			i--;
			cmd = getchar();
		}
		else
		{
			str[i] = cmd;
			i++;
			cmd = getchar();
		}
	}
	str[i] = '\0';
	trim(str);//Remove trailing and leading spaces
	//obtain the end address of the string
	for (endl = str; *endl != '\0'; endl++);
	inputstr = str;
	memset(argv, 0, sizeof(argv));
	argv[argc] = inputstr;
	argc++;
	//Separate the strings followed by zeros
	for(inputstr=str;inputstr<=endl-1;inputstr++)
	{
		if(*inputstr==' ')
		{
			*inputstr = '\0';
			 space_flag = 1;
		}
		else
		{
			if(space_flag == 1)
			{
				argv[argc] = inputstr;
				argc++;
				space_flag = 0;
			}
		}
	}
	argv[argc] = '\0';
	/* Command processing start*/
	if(argc == 1)
	{
		if(*argv[0] == 'a')
		{
			authorcommand(argv[0]);//Author Command Function
		}
		else if(*argv[0] == 'h')
		{
			helpcommand(argv[0]);//Help Command Function
		}
	}
	else if(argc == 3)
	{
		dumpcommand(argv[0],argv[1],argv[2]);//Dump Command Function
	}
	else
	{
		printf("Invalid command");
		printf("\n\r");
	}
}
