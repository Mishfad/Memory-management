
/*********************************************************************************************
                                     MEMORY MANAGEMENT PROGRAM
					  WRITTEN BY
					  MISHFAD S V
					  SR no: 09159
					  ECE DEPARTMENT
*********************************************************************************************/
 
#include<stdio.h>
#include<malloc.h>
#include<stdint.h>

#include"memory.h"

//extern int *used_head;

 int main()
  {
     int app_mem_size,mem_size,c=8, *app_addr=NULL,free_addr;
//   void *free_addr;
   char menu;
   while((c%8!=0)||(c<16))
    {
     printf("\nEnter the size to be allocated from heap : ");
     scanf("%d",&mem_size);
     printf("\nEnter chunk size as multiple of 8 greater than 16 :");
     scanf("%d",&c);
     
     if(mem_size % c!=0)
     mem_size=mem_size + c - (mem_size % c);

     printf("\nPassing values are : ");
     printf("%d  %d", mem_size, c);
    } 

   if(mem_init(mem_size,c))
     {
      printf("\n Sorry, Error while creating memory from heap!!\n Exiting...");
      return 1;
     }
 
   while(1)
    {
     printf("\n******************************************************************");
     printf("\n\t \t \t\t MENU");
     printf("\n******************************************************************");
     printf("\n 1: ALLOCATES MEMORY TO APPLICATION ");
     printf("\n 2: FREE THE MEMORY ALLOCATED TO APPLICATION");
     printf("\n 3: MEMORY SNAPSHOT  ");
     printf("\n q: quit ");
     printf("\n f: force quit ");
     printf("\nEnter your option : ");
     scanf("%c", &menu);
 
    switch(menu)
     {
      case '1':
          {
            printf("\n\nENTER THE SIZE OF THE MEMORY TO BE ALLOTED AS A MULTIPLE OF %d: ",c);
            scanf("%u",&app_mem_size);
            app_addr=(int *)mem_alloc(app_mem_size);
            if(app_addr==NULL)
             {
              printf("\nERROR WHILE CREATING!!!MEMORY FULL!! \n");
             // return 1;
             }
       break;

          } //END OF CASE 1
      case '2' :
          {
           printf("\nEnter the address of location to be freed : ");
           scanf("%d",&free_addr);
           app_addr=(void *)free_addr;
           if(mem_free(app_addr))
            printf("\\nError while deleting!!!");
           else
             printf("\nGiven Location Deleted!!!");
           
           break;
          }
      case '3' :
          {
           mem_dump();
           break;
          }
      case 'q':
          {
          if(mem_exit())
            printf("\n**************Memory is occupied!!please free them first*********************");
          else
            {
            printf("\n****************Memory freed!!!**********************\n");
             return 0;
            }
           break;
          }
      case 'f':
               {
                 printf("\nExiting!!!\n");
                 return 0;
               }
      case '\n':break;
      default: 
       {
        printf("\n\n##################PLEASE ENTER AN OPTION FROM MENU!!! #######################\n\n");
        break;
       }

     }//END OF SWITCH*/

    }// END OF WHILE(1)

   return 0;
    
  }

