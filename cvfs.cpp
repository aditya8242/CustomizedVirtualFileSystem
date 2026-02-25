#include "cvfs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Global variables or objects used in the project
//
/////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA ureaobj;

PINODE head = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    InitializeUAREA
//    Description:      It is used to initialize UAREA members
//    Author:           Aditya Harishchandra Chavan
//    Date:             13/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void InitializeUAREA()
{
	strcpy(ureaobj.ProcessName, "MyExe");

	int i = 0;

	for(i = 0; i < MAXOPENFILES; i++)
	{
		ureaobj.UFDT[i] = NULL;
	}

	printf("CVFS: UAREA gets initialized successfully!\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    InitializeSuperBlock
//    Description:      It is used to initialize super block member    
//    Author:           Aditya Harishchandra Chavan
//    Date:             13/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void InitializeSuperBlock()
{
	superobj.TotalInodes = MAXINODE;
	superobj.FreeInodes = MAXINODE;

	printf("CVFS: Super block gets initialized successfully!\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    CreateDILB
//    Description:      It is used to linked list of inodes
//    Author:           Aditya Harishchandra Chavan
//    Date:             13/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
	int i = 0;

	PINODE newn = NULL;
	PINODE temp = head;

	for(i = 1; i <= MAXINODE; i++)
	{
		newn = (PINODE)malloc(sizeof(INODE));

		strcpy(newn->FileName, "\0");
		newn->InodeNumber = i;
		newn->FileSize = 0;
		newn->FileType = 0;
		newn->ActualFileSize = 0;
		newn->ReferenceCount = 0;
		newn->Permission = 0;
		newn->Buffer = NULL;
		newn->next = NULL;

		if(temp == NULL)	//	LL is empty
		{
			head = newn;
			temp = head;
		}
		else				// LL contains at least 1 node
		{
			temp->next = newn;
			temp = temp->next;
		}
	}

	printf("CVFS: DILB created successfully!\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    StartAuxillaryDataInitialization
//    Description:      It is used to call all such functions which are used to initialize
//						auxillary data
//    Author:           Aditya Harishchandra Chavan
//    Date:             13/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialization()
{
	strcpy(bootobj.Information, "Booting process of CVFS is done!\n");
	
	printf("%s", bootobj.Information);

	InitializeSuperBlock();

	CreateDILB();

	InitializeUAREA();

	printf("CVFS: Auxillary data initialized successfully!\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    DisplayHelp
//    Description:      It is used to display the help
//    Author:           Aditya Harishchandra Chavan
//    Date:             14/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
	printf("---------------------------------------------------------\n");
	printf("-----------------------CVFS help-------------------------\n");
	printf("---------------------------------------------------------\n");

	printf("man:    It is used to display the manual page\n");
	printf("clear:  It is used to clear the terminal\n");
	printf("creat:  It is used to create a new file\n");
	printf("write:  It is used to write data into the file\n");
	printf("read:   It is used to read the data from the file\n");
	printf("stat:   It is used to display the file information\n");
	printf("unlink: It is used to delete the file\n");
	printf("exit:   It is used to exit the application\n");

	printf("---------------------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    DisplayManPage
//    Description:      It is used to display the man page
//    Author:           Aditya Harishchandra Chavan
//    Date:             14/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayManPage(char Name[20])
{
	if(strcmp("ls", Name) == 0)
	{
		printf("About: Used to list names of all files\n");
		printf("Usage: ls\n");
	}
	else if(strcmp("man", Name) == 0)
	{
		printf("About: Used to display man page\n");
		printf("Usage: man [command]\n");
		printf("command: The command written as parameter\n");
	}
	else if(strcmp("exit", Name) == 0)
	{
		printf("About: Used to terminate the shell\n");
		printf("Usage: exit\n");
	}
	else if(strcmp("clear", Name) == 0)
	{
		printf("About: Used to clear the shell\n");
		printf("Usage: clear\n");
	}
	else if(strcmp("help", Name) == 0)
	{
		printf("About: Used to display help page\n");
		printf("Usage: help\n");
	}
	else if(strcmp("unlink", Name) == 0)
	{
		printf("About: Used to unlink/delete a file\n");
		printf("Usage: unlink [filename]\n");
	}
	else if(strcmp("write", Name) == 0)
	{
		printf("About: Used to write data in file\n");
		printf("Usage: write [fd] (file descriptor)\n");
	}
	else if(strcmp("creat", Name) == 0)
	{
		printf("About: Used to create a new file\n");
		printf("Usage: creat [filename] [permissions] (rwx)\n");
		printf("Returns file descriptor. Important for other operations.\n");
	}
	else if(strcmp("read", Name) == 0)
	{
		printf("About: Used to read data from a file\n");
		printf("Usage: read [file descriptor] [number of bytes to be read]\n");
	}
	else
	{
		printf("No manual entry for %s", Name);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    IsFileExist
//    Description:      It is used to check if file is already present or not
//    Input:			It accepts file name
//    Output:			It returns boolean
//    Author:           Aditya Harishchandra Chavan
//    Date:             16/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

bool IsFileExist
(
	char *name    // file name
)
{
	PINODE temp = head;

	bool bFlag = false;

	while(temp != NULL)
	{
		if((strcmp(name, temp->FileName) == 0) && (temp->FileType == REGULARFILE))
		{
			bFlag = true;
			break;
		}

		temp = temp->next;
	}

	return bFlag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    CreateFile
//    Description:      It is used to create new regular file
//    Input:			It accepts file name and permissions
//    Output:			It returns the file descriptor
//    Author:           Aditya Harishchandra Chavan
//    Date:             16/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile
(
	char *name,    // name of new file
	int permission // permission for that file   
)
{
	PINODE temp = head;
	int i = 0;

	printf("Total number of Inodes remaining: %d\n", superobj.FreeInodes);

	// if name not given
	if(NULL == name)
	{
		return ERR_INVALID_PARAMETER;
	}

	// if permission value is invalid
	// permission 1 is read
	// permission 2 is write
	// permission 3 is read + write
	if(permission < 1 || permission > 3)
	{
		return ERR_INVALID_PARAMETER;
	}

	// if inodes are full
	if(superobj.FreeInodes == 0)
	{
		return ERR_NO_INODES;
	}

	// if file is already present
	if(IsFileExist(name) == true)
	{
		return ERR_FILE_ALREADY_EXIST;
	}

	// search empty inode
	while(temp != NULL)
	{
		if(temp->FileType == 0)
		{
			break;
		}

		temp = temp->next;
	}

	// inode which doesn't have regular file type as 0, rare
	if(temp == NULL)
	{
		printf("There is no Inode.\n");
		return ERR_NO_INODES;
	}

	// search for empty UDFT entry
	// 0, 1, 2 are reserved just like the actual linux/unix
	for(i = 3; i < MAXOPENFILES; i++)
	{
		if(NULL == ureaobj.UFDT[i])
		{
			break;
		}
	}

	// UFDT is full
	if(i == MAXOPENFILES)
	{
		return ERR_MAX_FILES_OPEN;
	}

	// allocate memory for file table
	ureaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

	// initialize file table
	ureaobj.UFDT[i]->ReadOffset = 0;
	ureaobj.UFDT[i]->WriteOffset = 0;
	ureaobj.UFDT[i]->Mode = permission;

	// connect file table with inode
	ureaobj.UFDT[i]->ptrinode = temp;

	// initialize elements of inode
	// can use temp
	strcpy(ureaobj.UFDT[i]->ptrinode->FileName, name);
	ureaobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
	ureaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
	ureaobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
	ureaobj.UFDT[i]->ptrinode->ReferenceCount = 1;
	ureaobj.UFDT[i]->ptrinode->Permission = permission;

	// allocate memory for file data
	ureaobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);

	// important to decrease this
	superobj.FreeInodes--;

	return i;	// file descriptor
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    lsFile()
//    Description:      It is used to list all files
//    Author:           Aditya Harishchandra Chavan
//    Date:             16/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

// ls -l
void lsFile()
{
	PINODE temp = head;

	printf("---------------------------------------------------------\n");
	printf("------------------CVFS files information-----------------\n");
	printf("---------------------------------------------------------\n");

	// todo add header
	while(temp != NULL)
	{
		if(temp->FileType != 0)
		{
			printf("%d\t%s\t%d bytes\n", temp->InodeNumber, temp->FileName, temp->ActualFileSize);
		}

		temp = temp->next;
	}

	printf("---------------------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    UnlinkFile()
//    Description:      It is used to delete a file
//    Input:			File name
//    Author:           Aditya Harishchandra Chavan
//    Date:             22/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int UnlinkFile
(
	char *name
)
{
	int i = 0;

	if(NULL == name)
	{
		return ERR_INVALID_PARAMETER;
	}

	if(IsFileExist(name) == false)
	{
		return ERR_FILE_NOT_EXIST;
	}
	
	// travel the UFDT
	for(i = 0; i < MAXOPENFILES; i++)
	{
		if(ureaobj.UFDT[i] != NULL)
		{
			if(strcmp(ureaobj.UFDT[i]->ptrinode->FileName, name) == 0)
			{
				// deallocate memory of Buffer
				free(ureaobj.UFDT[i]->ptrinode->Buffer);

				// for later use, should be NULL
				ureaobj.UFDT[i]->ptrinode->Buffer = NULL;

				// reset all values of inode
				// do not deallocate memory of inode

				ureaobj.UFDT[i]->ptrinode->FileSize = 0;
				ureaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
				ureaobj.UFDT[i]->ptrinode->FileType = 0;
				ureaobj.UFDT[i]->ptrinode->ReferenceCount = 0;	// todo: might have to change this
				ureaobj.UFDT[i]->ptrinode->Permission = 0;		
				
				memset(ureaobj.UFDT[i]->ptrinode->FileName, '\0', sizeof(ureaobj.UFDT[i]->ptrinode->FileName));

				// deallocate memory of file table
				free(ureaobj.UFDT[i]);

				// set NULL to UDFT
				ureaobj.UFDT[i] = NULL;

				// free node increment
				superobj.FreeInodes++;

				// important to break
				break;
			}	//	end of if
		}	//	end of if
	}	//	end of for

	return EXECUTE_SUCCESS;
}	//	end of function

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    WriteFile()
//
//    Description:      It is used to write the data into the file
//    
// 	  Input:			File descriptor
//						Address of Buffer which contains data
//						Size of data that we want to write
//
//    Output:			Number of bytes successfully read
//
//    Author:           Aditya Harishchandra Chavan
//    Date:             22/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int WriteFile
(
	int fd,
	char *data,
	int size
)
{
	printf("File descriptor: %d\n", fd);
	printf("Data that we want to write: %s\n", data);
	printf("Size of data: %d\n", size);

	// invalid fd
	if(fd < 0 || fd > MAXOPENFILES)
	{
		return ERR_INVALID_PARAMETER;
	}

	// fd points to NULL
	if(ureaobj.UFDT[fd] == NULL)
	{
		return ERR_FILE_NOT_EXIST;
	}

	// no write permission
	if(ureaobj.UFDT[fd]->ptrinode->Permission < WRITE)
	{
		return ERR_PERMISSION_DENIED;
	}

	// insufficient space
	if(MAXFILESIZE - ureaobj.UFDT[fd]->WriteOffset < size)
	{
		return ERR_INSUFFICIENT_SPACE;
	}

	// write data into the file
	strncpy(ureaobj.UFDT[fd]->ptrinode->Buffer + ureaobj.UFDT[fd]->WriteOffset, data, size);

	// update write offset
	ureaobj.UFDT[fd]->WriteOffset = ureaobj.UFDT[fd]->WriteOffset + size;

	// update the actual file size
	ureaobj.UFDT[fd]->ptrinode->ActualFileSize = ureaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

	return size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Function Name:    ReadFile()
//
//    Description:      It is used to read the data into the file
//    
// 	  Input:			File descriptor
//						Address of empty buffer
//						Size of data that we want to read
//
//    Output:			Number of bytes successfully read
//
//    Author:           Aditya Harishchandra Chavan
//    Date:             22/01/2026  
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int ReadFile
(
	int fd,
	char *data,
	int size
)
{
	// invalid FD
	if(fd < 0 || fd > MAXOPENFILES)
	{
		return ERR_INVALID_PARAMETER;
	}

	// invalid parameter
	if(data == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// invalid size
	if(size <= 0)
	{
		return ERR_INVALID_PARAMETER;
	}

	// invalid fd
	if(ureaobj.UFDT[fd] == NULL)
	{
		return ERR_FILE_NOT_EXIST;
	}

	// invalid permission
	if(ureaobj.UFDT[fd]->ptrinode->Permission < READ)
	{
		return ERR_PERMISSION_DENIED;
	}

	// insufficient data
	if((MAXFILESIZE - ureaobj.UFDT[fd]->ReadOffset) < size)
	{
		return ERR_INSUFFICIENT_DATA;
	}

	// read the data
	strncpy(data, ureaobj.UFDT[fd]->ptrinode->Buffer + ureaobj.UFDT[fd]->ReadOffset, size);

	// update the read offset
	ureaobj.UFDT[fd]->ReadOffset = ureaobj.UFDT[fd]->ReadOffset + size;

	return size;
}