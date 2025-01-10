/**********************************************************************************************************************************
			MEMORY MANAGEMENT FUNCTIONS AND VARIABLES DECLARATION
			WRITTEN BY: MISHFAD S V
			SR no : 09159
			ECE DEPT
*********************************************************************************************************************************/

#define MAX_MEMORY_SIZE 1024*1024*1024  // DEFINE MAXIMUM SIZE 1GB

#define MAX_CHUNK_SIZE 512		// MAXIMUM CHUNK SIZE 512 BYTES

#define MIN_CHUNK_SIZE 16		// MINIMUM CHUNK SIZE 16 BYTES

#define OVERHEAD_SIZE (sizeof(int)+sizeof(int *))   //OVERHEAD SIZE 


extern int *free_head;

/* INITIALISES THE MEMORY, ALLOCATES FROM HEAP
   PARAMETERS: (NO OF BYTES, CHUNK SIZE)
   RETURNS 1 IF ERROR, ELSE RETURNS 0 */
int mem_init(int, int);		


/*ALLOCATES MEMORY TO APPLICATION
  PARAMETER : NO OF BYTES
  RETURNS POINTER TO STARTING ADDRESS OF ALLOCATED MEMORY, NULL IF ERROR */
void * mem_alloc(int );


/*
  FREE UP THE CHUNK OF MEMORY
  PARAMETER : ADDRESS OF EXISTING NODE
  RETURN    : 1-ERROR 0-SUCCESS
*/
int mem_free(void *);


/*
  SHOWS THE MEMORY SNAPSHOT
*/
void mem_dump(void);

/*
  DEALLOCATES THE HEAP
  RETURNS 1: ERROR, 0:SUCCESS
*/
int mem_exit(void);



// function to draw a line
void line(char);

