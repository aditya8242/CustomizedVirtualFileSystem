// required header files

#include<stdio.h>		// basic I/O
#include<stdlib.h>		// malloc()
#include<unistd.h>		// file I/O
#include<stdbool.h>		// boolean
#include<string.h>		// string functions
#include "limits.h"		// limits
#include "structs.h"	// user defined structures
#include "err.h"		// error handling macros

// function prototypes
void InitializeUAREA();
void InitializeSuperBlock();
void CreateDILB();
void StartAuxillaryDataInitialization();
void DisplayHelp();
void DisplayManPage(char Name[20]);
bool IsFileExist(char *);
int CreateFile(char *,int);
void lsFile();
int UnlinkFile(char *);
int WriteFile(int,char *,int);
int ReadFile(int,char *,int);
int StatFile(char *);