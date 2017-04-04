 /* 
 *
 *	Authors : Ranjan Mishra, Nishant Nikam, Aniruddha Biswas
 *	Date   : 17th March 2016
 *	Desc : testing the database implementation till now
 *	
 */	

 #define MAX_DDL_LENGTH 10000


 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include"cs2015-database.h"


 int main(int argc, char *argv[]){
 	
 	FILE *fp;

 	char ddl[MAX_DDL_LENGTH];
	int ch;
	char dlChoice;
	char *ddlFile;
	char tableName[1024];

	char columnName[30];




	do{


		printf("\n\n############################---MENU---###########################");
		printf("\n\n\t1. CREATE NEW TABLE");
		printf("\n\t2. DROP EXISTING TABLE");
		printf("\n\t3. ADD PRIMARY KEYS");
		printf("\n\t4. VIEW TABLE STRUCTURE");

	


		printf("\n\tYour Choice(-1 to exit): ");
		scanf("%d", &ch);

		printf("\n\n##################################################################\n");


		switch(ch){
			case 1: 
				printf("\n\tD: DDL as File Input");
				printf("\n\tC: DDL as console input");
				
				printf("\n\tPlease enter your choice(D/C): ");

				getchar();
				scanf("%c", &dlChoice);




				if(dlChoice == 'D'){
					printf("\n\tPlease enter the DDL file name: ");
					scanf("%s", ddlFile);
					
					fp = fopen(ddlFile, "rb");
					if(!fp){
						printf("\n\tError while opening file, please check!");
						break;
					}
					
					fread(ddl, sizeof(char), MAX_DDL_LENGTH, fp);

					if(!createTable(ddl)){
						printf("\n\tTable created succesfully!");
					}

					else
						printf("\n\tError occured while creating table!");
					

					
				}

				else if(dlChoice == 'C'){
					int i=0;
					char ch;
					getchar();
					while((ch = getchar()) != ';'){
						ddl[i]=ch;
						i++;
					}
					ddl[i++]=';';
					ddl[i]='\0';
					

					if(!createTable(ddl)){
						printf("\n\tTable created succesfully!");
					}

					else
						printf("\n\tError occured while creating table!");
					

				}

				else
					break;			
			break;

			case 2: 
				printf("\n\tPlease enter table name: ");
				scanf("%s", tableName);

				if(dropMyTable(tableName)){
					printf("\n\tError removing table %s", tableName);
					break;
				}

				printf("\n\tTable %s dropped succesfully", tableName);


			break;


			case 3:
				printf("\n\tPlease enter table name: ");
				scanf("%s", tableName);
				printf("\n\tPlease enter column name: ");
				scanf("%s", columnName);
				int status=0;

				status = addPrimarKey(tableName, columnName);

				if(status ==0 ){
					
					printf("\n\tPrimary key added to table %s on the column %s", tableName, columnName);


				}
				else if(status == 1){
					
					printf("\n\tNo column named %s in the table %s\n", columnName, tableName);
				}
					

			break;

			case 4: 
				printf("\n\tPlease enter table name: ");
				scanf("%s", tableName);

				showTableStructure(tableName);
			break;

			default :
			
			break;
				
		}

	}while(ch !=-1);




 /*	if(argc < 2){
 		dbMetadata *db = getDBMetaData("STUDENT");
	 	printVersion(db);
 		printdbCreateTime(db);
 		columnMetadata *column = getColumnMetaData("F_NAME", "STUDENT");

 		if(column){ 	
 			printf("IS PK :%d\n", isPrimaryIndex(column));
 			printf("IS DEL:%d\n", isDeleted(column));
 		}
 		else
 			printf("No such column exists\n");

 		return 0;
 	}

 	fp = fopen(argv[1], "rb");
 	fread(ddl, sizeof(char), 1024, fp);
 	fclose(fp);
 	createTable(ddl);
 	*/
 	return 0;
 	

 }