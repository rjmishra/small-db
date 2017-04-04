# Project to develop small database system in C
Project aims to develop small database system in C. It is only for educational purpose.

We have created following structure to be followed for database file to store data

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
  
  Based on the above we developed program in C, to create, drop and update the tables.
