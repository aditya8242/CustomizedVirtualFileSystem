#include "cvfs.h"

int main()
{
	char str[80] = {'\0'};
	char Command[5][20] = {{'\0'}};
	char InputBuffer[MAXFILESIZE] = {'\0'};

	char *EmptyBuffer = NULL;
	
	int iCount = 0;

	int iRet = 0;
	
	StartAuxillaryDataInitialization();

	printf("---------------------------------------------------------\n");
	printf("----------Marvellous CVFS started successfully!----------\n");
	printf("---------------------------------------------------------\n");

	// infinite listening shell
	while(1)
	{
		fflush(stdin);

		strcpy(str,"");

		printf("\n[Marvellous CVFS]$ ");
		fgets(str, sizeof(str), stdin);
		
		iCount = sscanf(str, "%s %s %s %s %s", Command[0], Command[1], Command[2], Command[3], Command[4]);

		fflush(stdin);

		if(iCount == 1)
		{
			// [Marvellous CVFS]$ exit
			if(strcmp("exit", Command[0]) == 0)
			{
				printf("Exiting application...\n");
				printf("Deallocating all resources\n");	// todo
				
				break;
			}
			// [Marvellous CVFS]$ ls
			else if(strcmp("ls", Command[0]) == 0)
			{
				lsFile();
			}
			// [Marvellous CVFS]$ help
			else if(strcmp("help", Command[0]) == 0)
			{
				DisplayHelp();
			}
			// [Marvellous CVFS]$ clear
			else if(strcmp("clear", Command[0]) == 0)
			{
				// conditional preprocessing
				#ifdef _WIN32
					system("cls");
				#else
					system("clear");
				#endif
			}
		}	// end of if 1
		else if(iCount == 2)
		{
			// [Marvellous CVFS]$ man ls
			if(strcmp("man", Command[0]) == 0)
			{
				DisplayManPage(Command[1]);
			}

			// [Marvellous CVFS]$ unlink demo.txt
			if(strcmp("unlink", Command[0]) == 0)
			{
				iRet = UnlinkFile(Command[1]);

				if(iRet == ERR_INVALID_PARAMETER)
				{
					printf("Error: Invalid parameter!\n");
				}

				if(iRet == ERR_FILE_NOT_EXIST)
				{
					printf("Error: Unable to delete. No such file!\n");
				}

				if(iRet == EXECUTE_SUCCESS)
				{
					printf("File successfully deleted.\n");
				}
			}
			//	[Marvellous CVFS]$ write 2
			else if(strcmp("write", Command[0]) == 0)
			{
				printf("Enter the data that you want to write: ");
				fgets(InputBuffer, MAXFILESIZE, stdin);
																// -1 to remove \0
				iRet = WriteFile(atoi(Command[1]), InputBuffer, strlen(InputBuffer)-1);

				if(iRet == ERR_INVALID_PARAMETER)
				{
					printf("Error: Invalid parameters.\n");
				}
				else if(iRet == ERR_FILE_NOT_EXIST)
				{
					printf("Error: There is no such file.\n");
				}
				else if(iRet == ERR_PERMISSION_DENIED)
				{
					printf("Error: Unable to write. No priveleges.\n");
				}
				else if(iRet == ERR_INSUFFICIENT_SPACE)
				{
					printf("Error: Unable to write. No space.\n");
				}
				else
				{
					printf("%d bytes gets successfully written.\n", iRet);
				}
			}
			else
			{
				printf("There is no such command.\n");
			}

		}	// end of else if 2
		else if(iCount == 3)
		{
			// [Marvellous CVFS]$ creat Ganesh.txt 3
			if(strcmp("creat", Command[0]) == 0)
			{
				iRet = CreateFile(Command[1], atoi(Command[2]));

				if(iRet == ERR_INVALID_PARAMETER)
				{
					printf("Error: Unable to create the file as parameters are invalid!\n");
					printf("Please refer man page.\n");
				}

				if(iRet == ERR_NO_INODES)
				{
					printf("Error: Unable to create file as there is no Inode.\n");
				}

				if(iRet == ERR_FILE_ALREADY_EXIST)
				{
					printf("Error: Unable to create file. File is already present!\n");
				}

				if(iRet == ERR_MAX_FILES_OPEN)
				{
					printf("Error: Unable to create file.\n");
					printf("Max opened files limit reached.\n");
				}

				printf("File gets successfully created with FD %d\n", iRet);
			}
			//	[Marvellous CVFS]$ read 3 10
			else if(strcmp("read", Command[0]) == 0)
			{
				EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));	// might need for \0

				iRet = ReadFile(atoi(Command[1]), EmptyBuffer, atoi(Command[2]));

				if(iRet == ERR_INVALID_PARAMETER)
				{
					printf("Error: Invalid parameter.\n");
				}
				else if(iRet == ERR_FILE_NOT_EXIST)
				{
					printf("Error: No such file exists.\n");
				}
				else if(iRet == ERR_PERMISSION_DENIED)
				{
					printf("Error: Not enough privileges.\n");
				}
				else if(iRet == ERR_INSUFFICIENT_DATA)
				{
					printf("Error: Insufficient data.\n");
				}
				else
				{
					printf("Read operation successful.\n");
					printf("Data from file is\n%s\n", EmptyBuffer);

					free(EmptyBuffer);
				}

			}
			else
			{
				printf("No such command.\n");
			}
		}	// end of else if 3
		else if(iCount == 4)
		{
			
		}	// end of else if 4
		else if(strcmp(str, "\n") == 0)
		{
			continue;
		}
		else
		{
			printf("Command not found\n");
			printf("Please refer help command for more information\n");
		}	// end of else

	}	// end of while

	return 0;
}