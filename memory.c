/*******************************************************************************************************************
					FUNCTION AND VARIABLE DEFINITIONS
					WRITTEN BY: MISHFAD S V
					SR no:  09159
					ECE DEPT
					IISc
***********************************************************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdint.h>

#include "memory.h"
/*******************************************************************************************************************************************/
/*  VARIABLE DECLARATIONS
**********************************/
  struct node
    {
     int size;		// stores the size of block
     struct node *next;	// pointer to the next block
     char data[0];		// starting address for data
    }*free_node=NULL,*used_node=NULL, *check_free_node=NULL, *tmp_check_free_node=NULL;

//TO STORE STARTING AND ENDING ADDRESS OF DATA IN THE HEAP
int *data_start;
int *data_end;

//DECLARATION OF HEADS
int *used_head;
int *free_head; 

//DECLARATION OF END OF FREE LIST
int *free_end;

int chunk=0;

/*****************************************************************************************************************
 FUNCTION TO INITIALISE THE MEMORY
 PARAMETERS: (NO OF BYTES, CHUNK SIZE)
 RETURNS 1 IF ERROR, ELSE RETURNS 0 */

/************************************************/

int mem_init(int no_of_bytes, int chunk_size)
 {

#ifdef DEBUG3
#define DEBUG2
printf("\n\nCreates the Memory by taking from HEAP and makes ready for Applications\n"); 
#endif

#ifdef DEBUG2 
#define DEBUG1 
//printf("\nerror-0 : Entered memory size or chunk value is invalid!!\n");
//printf("\nerror-1 : (no of bytes + overhead) > maximum size !!\n");
#endif


#ifdef DEBUG1 
#define DEBUG0 
printf("\nparameters: memory size to be allocated for application,chunk size\n");
printf("\nPassed values are : (%d, %d)\n",no_of_bytes, chunk_size);
#endif

#ifdef DEBUG0
printf("\nInside mem_init() function\n");
#endif 


 chunk=chunk_size;

  if((no_of_bytes>MAX_MEMORY_SIZE)||(no_of_bytes == 0)||(chunk_size > MAX_CHUNK_SIZE) || (chunk_size < MIN_CHUNK_SIZE))
   {
    printf("\n error-0 : please check the values entered!!");
    return 1;
   } // IF CLOSED

  //if no of bytes not divisible by chunk size, then round it to the next divisible number

  if(no_of_bytes % chunk_size!=0)
   no_of_bytes=no_of_bytes + chunk_size - (no_of_bytes % chunk_size);

  //INCLUDE SIZE OF OVERHEAD
    no_of_bytes=no_of_bytes+2*(OVERHEAD_SIZE);

    if(no_of_bytes>MAX_MEMORY_SIZE)
     {
       printf("\n error-1 : (no of bytes + overhead) > maximum size !!");
	   return 1;
     }// close if

   //ALLOCATE MEMORY FROM HEAP
    used_node=(struct node*) malloc(no_of_bytes);

    if((used_node==NULL)) // IF MEMORY IS NOT ALLOCATED
     {
      printf("\nerror 2: memory not allocated!!!");
      return 1;
     }

    used_node->size=0;	// INITIALLY MEMORY IS EMPTY, AND IT POINTS TO NOTHING
    used_node->next=NULL;

    data_start= (int *)( ((uintptr_t)used_node) + 2*OVERHEAD_SIZE); // STARTING LOCATION OF DATA IN THE HEAP
    data_end= (int *)( ((uintptr_t) used_node) + no_of_bytes-1);      // ENDING LOCATION OF DATA

    //INITIALISE HEADS
    line('*');
    printf("\n \n\t\t ##### MEMORY INITIATION SUCCESS!!!### \n");
    line('*');

    used_head=(int *)used_node;			//HEAD OF FIRST USED NODE
    free_head=(int *)((uintptr_t)used_head+OVERHEAD_SIZE); //HEAD OF FIRST FREE NODE

    //INITIALISE FREE NODE
    free_node=(struct node*) used_node->data;  //NEXT ADDRESS AFTER USED DATA OVERHEAD
    free_node->size=0;				//NO DATA
    free_node->next=(struct node*) free_node->data;//

//MOVE THE FREE NODE LOCATION AFTER USED AND FREE HEAD
    free_node=free_node->next;
    free_node->size=((uintptr_t)data_end-(uintptr_t)data_start - OVERHEAD_SIZE+1);
    free_node->next=NULL;

#ifdef DEBUG3
printf("\nused head is                           : %d\n",(uintptr_t)used_head);
printf("\nfree head is                           : %d",(uintptr_t)free_head);
printf("\nData start                             : %d",(uintptr_t)data_start+OVERHEAD_SIZE);
printf("\nData end                               : %d",(uintptr_t)data_end);
printf("\nSize available for storage             : %d",free_node->size);
#endif    

#ifdef DEBUG2
printf("\nMemory of size %d allocated from %u \n", no_of_bytes-2*(OVERHEAD_SIZE), (uintptr_t)used_node);
printf("\nAvailable storage location starts from : %d",(uintptr_t)free_node);
printf("\nSize available for storage             : %d",free_node->size);
#endif
    return 0;

 } // mem_init() CLOSED*/

/***************************************END OF mem_init()*************************************************


*******************************************************************************
  FUNCTION TO ALLOCATE MEMORY TO APPLICATION
  PARAMETER : NO OF BYTES
  RETURNS POINTER TO STARTING ADDRESS OF ALLOCATED MEMORY, NULL IF ERROR */

/*******************************************************************************/
 void * mem_alloc(int n) // n- NO OF BYTES
  {
// ********************declaration of variables*********************************
    void *addr=NULL; // variable to be returned
    int alloting_node_size,remaining_size;
    int *tmpfree_next,*tmpused_next;
    struct node *tmp1, *tmpfree_node;

//*******************************************************************************

#ifdef DEBUG0
printf("\nInside mem_alloc function!!!\n");
printf("\nFunction to allocate required memory to applications\n");
#endif
#ifdef DEBUG1
printf("\nParameter     : allocating size n\n");
printf("\nPassed value : (%d)\n",n);
#endif
    if(n % chunk!=0)
     n=n + chunk - n%chunk;

     used_node=(struct node *) used_head;
     free_node=(struct node *) free_head;
// LOOP TO FIND FREE BLOCK OF SUFFICIENT LENGTH
    
     while(free_node->next!=NULL)
      {
        tmp1=free_node;
        free_node=free_node->next; // GO TO NEXT LOCATION
        tmpfree_node=free_node;
        tmpfree_next=(int *)free_node->next;//BACKUP ADDRESS OF NEXT FREE LOCATION
#ifdef DEBUG3
        printf("\nAddresss pointed by free_node : %d\n",(uintptr_t)tmpfree_next);
#endif
        alloting_node_size=free_node->size;
//        printf("\nSize of tmp free : %d",tmpfree->size);
        if(free_node->size >= n) // if block of exactly same length found
          {
            addr= (void *) free_node->data; // RETURNING ADDRESS OF DATA

//MOVE USED LIST TO THE LAST LOCATION

            while(used_node->next!=NULL)
              used_node=used_node->next;

            tmpused_next=(int *)used_node->next;//BACKUP THE ADDRESS POINTED BY USEDNODE ie NULL TO AN INTEGR PTR 
	    used_node->next=free_node; // ADDS SELECTED NODE TO THE END OF USED LIST
            free_node->next=NULL;   // 
            free_node->size=n;	       //MODIFY SIZE OF NEW NODE

            remaining_size=alloting_node_size-tmpfree_node->size-OVERHEAD_SIZE;// REMAINING SIZE IN CURRENT NODE
            printf("\n ****New Memory Allocated !!****\n");
#ifdef DEBUG2
printf("\nStarting address      : %d ",(uintptr_t)used_node->next);
printf("\nStarting Data address : %d ",(uintptr_t)addr);
#endif
#ifdef DEBUG3
printf("\nAllocated size        : %d",free_node->size);
printf("\nEnding Address        : %d",(uintptr_t)addr+free_node->size);
#endif

//CHECK IF THERE IS ATLEAST ONE CHUNK SIZE AFTER OVERHEAD IN THE REMAINING
	    if(alloting_node_size >= n+OVERHEAD_SIZE+chunk)
             {
#ifdef DEBUG3
printf("\nRemaining Size in the node = %d",(uintptr_t)addr + alloting_node_size-((uintptr_t)used_node->next+OVERHEAD_SIZE + free_node->size)); //calculate remaining size in the allocated node
#endif
              free_node=(struct node *)( (uintptr_t)tmpfree_node + n+OVERHEAD_SIZE); // CREATE NEW BLOCK
#ifdef DEBUG2
printf("\nallotd node total size = %d",alloting_node_size);
printf("\nnew address            = %d",(uintptr_t)free_node);
#endif
              free_node->next=(struct node*)tmpfree_next;
              tmp1->next=free_node;
              free_node->size=remaining_size;
             }
// IF NOT PRESENT, LINK PREVIOUS FREE NODE TO NEXT FREE NODE
            else
             {
#ifdef DEBUG3
printf("\nnot enough size to create one more free location");
#endif
              tmp1->next=tmpfree_node->next; //MODIFY FREE LIST
             }
             return addr; // EXIT LOOP IF MEMORY ALLOCATED  
          }//CLOSE if(free_node->size >= n)
      }  //close while
     return NULL;
  }
/***********************************************END OF mem_alloc()*************************************************/



/****************************************************************
  FUNCTION TO FREE UP THE CHUNK OF MEMORY ALLOTED TO APPLICATION
  PARAMETER : ADDRESS OF EXISTING NODE
  RETURN    : 1-ERROR 0-SUCCESS
*****************************************************************/
int mem_free(void *free_addr)
 {

#ifdef DEBUG0
printf("\nInside mem_free function!!!\n");
printf("\nFunction to free the memory given to applications\n");
#endif
#ifdef DEBUG1
printf("\nParameter     : freeing address\n");
printf("\nPassed value  : (%d)\n",(uintptr_t)free_addr);
#endif

//MOVE TO BEGINNING OF USED AND FREE LIST
    used_node=(struct node *) used_head;
    free_node=(struct node *) free_head;

    int left=0,right=0;// 1:MERGED 
    struct node *tmpfree_node,*temp_check_free_node;
    struct node *freeing_node= (struct node *)((uintptr_t)free_addr);
    printf("\nAddress of freeing node : %u",(uintptr_t)freeing_node);

//FIND THE LAST OF FREE LIST
     if(free_node->next==NULL)
       free_end=(int *)free_node; //TAKE CARE OF THE CASE WHEN MEMORY OVERFLOW OCCUR

     while(free_node->next!=NULL)
       free_node=free_node->next; 
       free_end=(int *)free_node;

//TRAVERSE THROUGH USED LIST TO THE LOCATION TO BE FREED
    while((used_node->next != freeing_node)&&(used_node->next!=NULL))
       used_node=used_node->next;

    if(used_node->next==NULL) // IF NODE NOT FOUND, RETURN ERROR
     {
       printf("\nNODE NOT FOUND \n");
#ifdef DEBUG3
printf("\nExiting function mem_free\n");
#endif

       return 1;
     }

    else // IF NODE FOUND
     {
#ifdef DEBUG2
printf("\nBefore freeing check whether merging is possible with an existing free block by checking for free block to the left and right side of the freeing block \n");
#endif

      used_node->next=freeing_node->next; //MODIFY USED LIST
      free_node=(struct node *) free_head;
      while(free_node!=NULL)  //TRAVERSE THROUGH FREE LIST TO CHECK WHETHER MERGING POSSIBLE
       {

                //CHECKS IF LEFT SIDE {free_node} OF (FREEING LOCATION{freeing_node}) IS ALREADY FREE 
                //ADD SIZE OF FREEING LOCATION TO THE SIZE OF FREE NODE ON LEFT SIDE AND MERGE THEM

         if(( ( (struct node *)((uintptr_t)free_node+free_node->size+OVERHEAD_SIZE ))==freeing_node) ) //IF LEFT FREE
           {
            if( (uintptr_t)free_node==(uintptr_t) free_head) //JUST TO AVOID MERGING WHEN FREEING NODE IS FIRST DATA NODE
               {
                tmpfree_node=free_node;
                free_node=free_node->next;
                continue;
               }
               free_node->size=(free_node->size) + (freeing_node->size) + OVERHEAD_SIZE;
               printf("\nLeft is merged ");
               printf("\nSize after merging : %d",free_node->size);
               left=1; // SET MERGING FLAG TO SAY MERGING DONE WITH LEFT SIDE
               continue; // SKIP THE REMAINING FOR A LOOP
             
           } // CLOSE if CHECKING LEFT SIDE 
//NO NEED TO MODIFY THE ADDRESS!!

//CHECK IF RIGHT SIDE IS FREE
         if(( (struct node *)((uintptr_t)freeing_node + (freeing_node->size) + OVERHEAD_SIZE)==free_node) )
          {
            if(left==1)  // IF LEFTSIDE ALREADY MERGED
             {
                printf("\nleft is already merged!! ");

                tmpfree_node->next=free_node->next; //MODIFY ADDRESS
                tmpfree_node->size=tmpfree_node->size+free_node->size+OVERHEAD_SIZE;//MODIFY SIZE

                printf("\nSize after merging : %d",tmpfree_node->size);
             }// end if(left==1)

//POINT USEDNODE WHICH POINTED TO FREE NODE) TO NODE WHICH IS POINTED BY FREEING NODE
//IF MERGED WITH LEFT, NO NEED TO MODIFY THE ADDRESS
            
            else if(left==0)//IF LEFT NOT MERGED
             {
               freeing_node->size=((freeing_node->size) + (free_node->size) + OVERHEAD_SIZE);
               printf("\nleft is not merged!! ");
//MAKE A LINK FROM NEW FREE TO ADDR POINTED BY FREE LOCATN ON RIGHT SIDE
               freeing_node->next=free_node->next; 
               tmpfree_node->next=freeing_node; // PREV NODE IN FREE LIST POINTS to new freed address

             }//END else if(left==0)

            right=1; //RIGHT HAS MERGED
            printf("\nRight is merged!!! ");

//CHECK IF THIS RIGHT MERGED NODE IS LAST
           if(free_node->next==NULL && (uintptr_t)free_node!=(uintptr_t)free_head) //check if last node points to NULL
                free_end=(int *)tmpfree_node->next; //THEN MODIFY free_end;

          } //close if for checking right

           tmpfree_node=free_node;
           free_node=free_node->next;
       }// closewhile(free_node->next!=NULL)  //TRAVERSE THROUGH FREE LIST
//IF MERGING NOT DONE, MOVE FREED LOCATION TO FREED LIST, SORTING ACCORDING TO ADDRESS
       if(left==0 && right==0) 
         {
#ifdef DEBUG3
printf("\nIf merging not possible, add the freeing node to the free list sorted in increasing order of address\n");
#endif

//TRAVERSE THROUGH FREE LIST AND CHECK IF FREEING NODE COMES IN BETWEEN ANY
         check_free_node= (struct node *)free_head;
         while(check_free_node->next!=NULL )
          {
           tmp_check_free_node=check_free_node;
           check_free_node=check_free_node->next;
   
//IF FREEING NODE address COMES BEFORE ANY FREE NODE, MOVE FREEING NODE TO JUST ABOVE THAT NODE
          if( (uintptr_t)check_free_node > (uintptr_t)freeing_node)
            {
             tmp_check_free_node->next=freeing_node;
             freeing_node->next=check_free_node;
            }
           printf("\njust freed!! no merging ");
#ifdef DEBUG2
           printf("\nHere merging is not possible. So the block is freed and added to free list\n");
           printf("\nSize of freed location : %d", (uintptr_t)freeing_node->size);
#endif
         } //end of while(check_free_node->next!=NULL)
       

//IF FREEING NODE IS THE LAST BLOCK, THEN MODIFY FREE LIST AND FREE END
        if((uintptr_t)freeing_node > (uintptr_t)free_end)
           {
             free_node=(struct node *)free_end;
             free_node->next=freeing_node;
             if(((uintptr_t)free_end==(uintptr_t)free_head)) //CONSIDERING MEMORY OVERFLOW
               freeing_node->next=NULL;
           }   
       } //END OF if(merge==0)

//check if same block is pointed more than once;
          free_node=(struct node *)free_head;
          while(free_node->next!=NULL)
           {
            check_free_node=(struct node *)free_head;
            free_node=free_node->next;
            while(check_free_node->next!=NULL)
             {
               temp_check_free_node=check_free_node;
               check_free_node=check_free_node->next;
//IF CHECKFREENODE LIES IN FREE_NODE
               if( ((uintptr_t)free_node <(uintptr_t)check_free_node) && ( ((uintptr_t)free_node +free_node->size)>(uintptr_t)check_free_node) )
                  temp_check_free_node->next = free_node;
             } // while(check_free_node->next!=NULL)
           }//  while(free_node->next!=NULL)
     }  //else OF IF(NODE NOT FOUND)
#ifdef DEBUG3
printf("\nExiting function mem_free\n");
#endif
     return 0;
 } //end of mem_free()
/*************************************************END OF mem_free()***********************************************/


/********************************
  DEALLOCATES THE MEMORY 
  RETURNS 1: ERROR, 0:SUCCESS
*********************************/

int mem_exit(void)
{
#ifdef DEBUG0
printf("\nInside mem_exit function!!!\n");
printf("\nFunction to exit deallocating memory taken from heap if no application is using memory\n");
#endif
#ifdef DEBUG1
printf("\nParameter     : nothing n\n");
#endif

 used_node=(struct node *) used_head;
 if(used_node->next!=NULL)
  { 
#ifdef DEBUG0
printf("\nSome applications is using Memory. Cannot be freed!!!\n");
#endif
   return 1;
  }
 else
  { 
#ifdef DEBUG0
printf("\nExiting...\n");
#endif
    free(used_node);
    return 0;
   }

} //END OF mem_exit()

/******************************************************************************************************************/

/******************************************
  FUNCTION TO SHOW THE MEMORY SNAPSHOT
  PARAMETER NULL
  RETURN 
*******************************************/
void mem_dump(void)
 { 
#ifdef DEBUG0
printf("\nInside the function mem_dump\n");
#endif

#ifdef DEBUG1
printf("\nParameters : Nothing\n");
#endif

 	 int i=0;
         line('*');
         printf("\n\t\t\tMEMORY SNAPSHOT\n\n");
         line('*');
	 printf("\n  No\t         Size              Status   Starting Address   Ending Address\n");
	 used_node=(struct node *) used_head;
	 free_node=(struct node *) free_head;
#ifdef DEBUG2
printf("\nShowing Free list...\n");
#endif
	 while((uintptr_t)free_node->next!=0)
	 {
		 free_node=free_node->next;
		 i++;
		 printf("\n %3u %15u \t \t   FREE      %6d   %14d",i,free_node->size,(uintptr_t)free_node,(uintptr_t)free_node+free_node->size-1);
	 }
#ifdef DEBUG2
printf("\nShowing Used list...\n");
#endif
	 while((uintptr_t)used_node->next!=0)
	 {
		 used_node=used_node->next;
		 i++;
		 printf("\n %3u %15u  \t \t ALLOCATED   %d   %14d",i,used_node->size,(uintptr_t)used_node,(uintptr_t)used_node+used_node->size-1);
	 }
#ifdef DEBUG3
printf("\nExiting function mem_dump\n");
#endif
 }//end mem_dump()


void line(char c)
 {
  int i;
  printf("\n");
  for(i=0;i<65;i++)
    printf("%c",c);
 }

