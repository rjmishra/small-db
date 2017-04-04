/* 
 *
 *	Author : Ranjan Mishra, Nishant Nikam, Aniruddha Biswas
 *	Date   : 17th March 2016
 *	
 *	
 *	
	The file layout will be 

	DB Metadata
	-------------------------------------------------------------------------
	|2 	BYTES  	MAGIC NUMBER(AB)                                         
	|1 	BYTE 	VERSION                                                  
	|1 	BYTE  	DB Metadata Size(36)                                     
	|14 BYTES  	DATABASE CREATE TIME (DDMMYYYYHHMMSS)                    
	|1 	BYTE 	NUMBER OF COLUMNS                                        
	|1 	BYTE 	COLUMN METADATA SIZE(VALUE=38)                           
	|8 	BYTES	NUMBER OF ROWS                                          
	|8 	BYTES	RESERVED FOR FUTURE                                      
	------------------------------------------------------------------------- 
	Column Metadata
	-------------------------------------------------------------------------
	|1 BYTES 	INDEX
	|1 BYTE 	COLUMN INFORMATION
	|30 BYTES	COLUMN NAME-case insensitive
	|1 BYTES 	SIZE 				
	|5 BYTES	CONSTRAINTS(future implementation)
	-------------------------------------------------------------------------
								-
								-
								-
								-
	------------------------------------------------------------------------- 
	|Column Metadata 				
	-------------------------------------------------------------------------
	|Data 									
	|	
	|	
	|
	|
	-
	-
	-
	-
    |													
	-------------------------------------------------------------------------

	

	
	VERSION(1 BYTE)
	Versioning will be permitted as x.y where x,y are integers
	first 4 bits will represent x and last 4 bits, y.
	e.g 1.4 will be stored as 00010100

	Following datatypes will be permitted
	0-BOOL
	1-DATE
	2-TIME
	3-INT
	4-FLOAT(m,n)
	5-CHAR(N)
	
	COLUMN INFO(1 BYTE)
	Column information byte will be made up following bits
	bit 0 : primary key(0-false 1-true)
	bit 1 :	dirty bit(0-exits in table 1-deleted)
	bit 2-4	datatype (0-bool,..,4-char)
	bit 5-7 reserved for future implementation

	For floating numbers FLOAT(m,n)
	The SIZE BYTE will store m,n. First 5 bits will be used for m,
	and last 3 bits for n. e.g. FLOAT(4,5): 00100101 


 */

#ifndef _CS2015_DATABASE_HEADER_

#define _CS2015_DATABASE_HEADER_

#define BOOL 0					//00000000
#define DATE 8					//00001000
#define TIME 16					//00010000
#define INT 24					//00011000
#define FLOAT 32				//00100000
#define CHAR 40					//00101000
#define MASK 56					//00111000

#define PK 128					//10000000
#define DIRTY 64				//01000000
#define RESERVED 0 				//00000000

#define DBMSIZE 36
#define COLUMNSIZE 38
#define VERSION_UP 16


// structure def for the db metadata


 typedef struct dbMetaInfo{
 	char magicNumber[2];	
 	char version;
 	char dbMetadataSize;
 	char dbCreateTime[14];
 	char numberOfColumns;
 	char columnMetadataSize;
 	char numberOfRows[8];
 	char futureReserved[8];
 }dbMetadata;

 


 //structure def for column metadata

 typedef struct columnMetaInfo{
 	char index;
 	char columnInfo;
 	char columnName[30];
 	char size;
 	char constraints[5];
 }columnMetadata;


/* Necessary functions which will be useful throughout 
 */


 dbMetadata *getDBMetaData(char *tableName);
 void addDBMetaData(char *tableName, int numberOfColumns);

 int getNumberOfColumns(dbMetadata *db);
 long long unsigned getNumberOfRows(dbMetadata *db);
 void printdbCreateTime(dbMetadata *db);
 void printVersion(dbMetadata *db);



 columnMetadata *getColumnMetaData(char *columnName, char *tableName);
 void addColumnMetaData(char *tableName, char* columnInfo, int index);

 int isDeleted(columnMetadata *column);
 int isPrimaryIndex(columnMetadata *column);
 int createTable(char *def);


#endif
