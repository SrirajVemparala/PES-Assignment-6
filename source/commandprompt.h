/*Author: Raghu Sai Phani Sriraj Vemparala
 *
 * Reference: Lecture given by Professor.Lalit Pandit
 *
 *
 * Description: Includes Function definition of all the command processing functions
 */

/**************************************************************************************/
								/*FUNCTION DECLARATIONS*/
/**************************************************************************************/
/* Function: commandprompt()
 *
 * Param: NIL
 *
 * return: void
 *
 * Description: Start of command processing
 */
void commandprompt();

/* Function: trim()
 *
 * Param: *str(address of the string)
 *
 * return: void
 *
 * Description:Trim trailing and leading spaces from the string
 */
void trim(char *);

/* Function: strtodecimal()
 *
 * Param: char *s(address of the string),int addr_flag
 *
 * return: int(decimal value)
 *
 * Description:Convert string to decimal
 */
int strtodecimal(char*,int);

/* Function: hexdump()
 *
 * Param: int start_address,int length
 *
 * return: void
 *
 * Description:Output Hex Dump
 */
void hexdump(int ,int);

/* Function: authorcommand()
 *
 * Param: char*
 *
 * return: void
 *
 * Description: Check if author command received is correct. If it is correct then process the command
 */
void authorcommand(char *);

/* Function: dumpcommand()
 *
 * Param: char *command, char* address, char* length
 *
 * return: void
 *
 * Description: Provides the hex dump on receiving the dump command with proper address and length
 */
void dumpcommand(char*, char*, char*);


