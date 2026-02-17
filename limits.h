////////////////////////////////////////
// limit, permission and other macros //
////////////////////////////////////////

// maximum file size allowed in bytes
#define MAXFILESIZE 1024

// maximum number of files allowed to be opened
#define MAXOPENFILES 20

// max inodes, enough for simulation
#define MAXINODE 5

// permissions
#define READ 1
#define WRITE 2
#define EXECUTE 4

// success
#define EXECUTE_SUCCESS 0

// file type
#define REGULARFILE 1
#define SPECIALFILE 2