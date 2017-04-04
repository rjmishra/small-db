 /* 
 *
 *	Author : Ranjan Mishra, Nishant Nikam, Aniruddha Biswas
 *	Date   : 17th March 2016
 *	Desc : Functions implementation for the database structure 
 *	
 */	


 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 #include<string.h>
 #include"cs2015-database-header.h"
 

 
 dbMetadata *getDBMetaData(char *tableName){
 	FILE *fp;
 	dbMetadata *dbInfo;

 	dbInfo = (dbMetadata*) malloc(sizeof(dbMetadata));
 	fp = fopen(tableName, "r");

 	if(!fp){
 		perror("\nNo such table");
 		exit(-1);
 	}

 	if(fread(dbInfo, sizeof(dbMetadata), 1, fp)==0){
 		perror("\nError accessing file!");
 		exit(-1);
 	}
 	fclose(fp);
	return dbInfo;
 }


 void addDBMetaData(char *tableName, int numberOfColumns){
 	
 	dbMetadata *db;
 	FILE *fp;
 	int tempTime;
	db = (dbMetadata *) malloc(sizeof(dbMetadata)); 	
 	//magic number is AB
 	db->magicNumber[0]='A';
 	db->magicNumber[1]='B';

	// 	printf("\nIn addDBMetaData name of table is : %s and size is : %d\n", tableName, strlen(tableName));

 	/*version of the database system	
 	version is initially 1.0
 	4 bits for 1: 0001 and 4 bits for 0:0000
 	resultant byte:00010000
 	*/
 	db->version = 16;

 	db->dbMetadataSize = DBMSIZE;

 	// time of creation of table
 	time_t secs= time(NULL);
	struct tm *myTm = localtime(&secs);
 	tempTime = myTm->tm_mday;

 	//DD
	db->dbCreateTime[1]=tempTime%10;
	db->dbCreateTime[0]=tempTime/10;

	//MM-month
	tempTime= myTm->tm_mon + 1;
	db->dbCreateTime[3]=tempTime%10;
	db->dbCreateTime[2]=tempTime/10;
	
	// YYYY
	tempTime= myTm->tm_year+1900;
	db->dbCreateTime[7]=tempTime%10;
	
	tempTime = tempTime/10;
	db->dbCreateTime[6]=tempTime%10;
	
	tempTime = tempTime/10;
	db->dbCreateTime[5]=tempTime%10;
	
	tempTime = tempTime/10;
	db->dbCreateTime[4]=tempTime;

	//HH
	tempTime = myTm->tm_hour;
	db->dbCreateTime[9]=tempTime%10;
	db->dbCreateTime[8]=tempTime/10;

	//MM--Minutes
	tempTime = myTm->tm_min;
	db->dbCreateTime[11]=tempTime%10;
	db->dbCreateTime[10]=tempTime/10;

	//SS 
	tempTime = myTm->tm_sec;
	db->dbCreateTime[13]=tempTime%10;
	db->dbCreateTime[12]=tempTime/10;

	//number of columns initialized with value 0
 	db->numberOfColumns=numberOfColumns;
 	
 	//column metadata size
 	db->columnMetadataSize = COLUMNSIZE;
 	
 	for(int i=0;i<8;i++){
 		db->numberOfRows[i]=0;		// number of rows initialized with 0
 		db->futureReserved[i]=0;		// bytes reserved for future uses 
 	}

 	fp = fopen(tableName, "w");
 	if(!fp){
 		perror("\nError creating table, please try again!");
 		exit(-1);
 	}
 	
 	if(fwrite(db, sizeof(dbMetadata), 1, fp)<=0){
 		perror("\nError creating table, please try again!");
 		exit(-1);
 	}

 	fclose(fp);
 }


 int getNumberOfColumns(dbMetadata *db){
 	return db->numberOfColumns;
 }


 long long unsigned getNumberOfRows(dbMetadata *db){
 	long long unsigned numberOfRows = 0;
 	long long unsigned a = 1;
 	for(int i=0;i<8;i++){
 		numberOfRows += db->numberOfRows[i] * a;
 		a = a*256;
 	}

 	return numberOfRows;
 }
 
 void printdbCreateTime(dbMetadata *db){
 	printf("\nTable Creation Time(DD:MM:YYYY:HH:MM:SS)\n");
 	printf("%d%d:", db->dbCreateTime[0],db->dbCreateTime[1]);
 	printf("%d%d:", db->dbCreateTime[2],db->dbCreateTime[3]);
 	printf("%d%d%d%d:",db->dbCreateTime[4],db->dbCreateTime[5],db->dbCreateTime[6],db->dbCreateTime[7]);
 	printf("%d%d:", db->dbCreateTime[8],db->dbCreateTime[9]);
 	printf("%d%d:", db->dbCreateTime[10],db->dbCreateTime[11]);
 	printf("%d%d\n", db->dbCreateTime[12],db->dbCreateTime[13]);
 }

 void printVersion(dbMetadata *db){
 	char temp;
 	//temp = 240;
 	printf("Version: %d.", db->version/VERSION_UP);
 	temp = 15;
 	printf("%d", temp & db->version);

 }



 columnMetadata *getColumnMetaData(char *columnName, char *tableName){

 	FILE *fp;
 	//char buffer[512];
 	dbMetadata *db;
 	columnMetadata *col;
 	fp = fopen(tableName, "r");
 	int numberOfColumns;
 	int status = 0;

 	db = (dbMetadata*) malloc(sizeof(dbMetadata));
 	col = (columnMetadata*) malloc(sizeof(columnMetadata));



 	if(!fp){
 		perror("\nNo such table!");
 		exit(-1);
 	}

 	if(fread(db, sizeof(dbMetadata), 1, fp)==0){
 		perror("\nNo such table!");
 		exit(-1);
 	}
 	
 	numberOfColumns = db->numberOfColumns;

 	while(numberOfColumns > 0){
 		fread(col, sizeof(columnMetadata), 1, fp);
 		printf("\nColumn:%s\n",col->columnName);
 		if(strcmp(columnName, col->columnName)==0){
 			return col;
 		}
 		numberOfColumns--;
 	}

 	return NULL;
 	
 }

 
 int createTable(char *def){
 	/* The def which will be accepted will be of the following form
	
		CREATE TABLE EMPLOYEE
			EMPLOYEE_ID INT,
			SALARY FLOAT(12, 5),
			NAME CHAR(20),
			DATE_OF_JOINING DATE,
			SWIPE_TIME TIME,
			CURRENT_STATUS BOOL;
	*/

	// extract the table name
	int index=1;
	int status = 1;
	char *temp;
	char *tableName;
	char *columnInfo;
	int numberOfColumns=0;


	temp = def;
	while(*temp){
		if(*temp == '('){
			while(*temp != ')') temp++;
		}
		else if(*temp == ','){
			numberOfColumns++;
		}
		else if(*temp==';') break;
		temp++;
	}


	printf("\nNumber of columns are :%d\n", numberOfColumns);

	while(*def != ' ') def++;
	def++;
	while(*def != ' ') def++;

	tableName = ++def;

	while(*def != '\n'){
		def++;
	}

	*def = '\0';

	//printf("\nIn createTable name of table is : %s and size is : %d\n", tableName, strlen(tableName));
	addDBMetaData(tableName, ++numberOfColumns);
	
	while(status){
		columnInfo = def;
		while(*def != ',' && *def != ';'){
			def++;
			if(*def == '('){
				while(*def != ')') def++;
			}
			else if(*def ==';'){
				*def = '\0';
				addColumnMetaData(tableName, ++columnInfo, index);		
				def++;
				status = 0;
				break;
			}
		}
		
		*def = '\0';
		addColumnMetaData(tableName, ++columnInfo, index);
		def++;
		index++;
	}

	return 1;
 }



 void addColumnMetaData(char *tableName, char* columnInfo, int index){
 	columnMetadata *column;
 	column = (columnMetadata*) malloc(sizeof(columnMetadata));
 	int prec;
 	int acc;
 	int dataType=0;
 	char *columnName;
 	char *datatype;
 	FILE *fp;
 	columnName = columnInfo;

 	column->index = index;

 	while(*columnInfo != ' ') columnInfo++;
 	*columnInfo = '\0';
 	columnInfo++;
 	

 	datatype = columnInfo;

 	if(*datatype == 'F'){
 		sscanf(columnInfo, "*%s(%d,%d)", &prec, &acc);
 		dataType = FLOAT;
 		column->size = prec * 8 + acc;
 	}
 	if(*datatype == 'C'){
 		sscanf(columnInfo, "*%s(%d)", prec);
 		dataType = CHAR;
 		column->size = prec;
 	}
 	if(*datatype == 'B'){
 		dataType = BOOL;
 		column->size = 0;
 	}
 	if(*datatype == 'D'){
 		dataType = DATE;
 		column->size = 0;
 	}
 	if(*datatype == 'T'){
 		dataType = TIME;
 		//printf("%c\n\n\n\n", *datatype);
 		column->size = 0;
	}
	if(*datatype =='I'){
		dataType = INT;
		column->size = 0;
	}
	
	column->columnInfo = dataType;
	strcpy(column->columnName, columnName);
	for(int i=0;i<5;i++){
		column->constraints[i]='A';		//raw values
	}

	fp = fopen(tableName, "ab");

	fwrite(column, sizeof(columnMetadata), 1, fp);
	//printf("\nThe value of columnInfo byte is:%d\n",column->columnInfo);
	//printf("New Column has been added :%s and datatype is :%d\n", columnName, dataType);

	fclose(fp);
 }



 int isDeleted(columnMetadata *column){
 	if(column->columnInfo && DIRTY){
 		return 1;
 	}
 	return 0;
 }

 int isPrimaryIndex(columnMetadata *column){
 	if(column->columnInfo && PK){
 		return 1;
 	}
 	return 0;
 }
