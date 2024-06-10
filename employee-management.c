/* Employee management system
 * It will store new employee details, edit existing employee details
 * Search existing employee details and delete resigned employee details */
#include <stdio.h>
#include <stdlib.h>

/* Macro */
#define MAX_LIMIT 20

/* Structure declaration */
typedef struct Employee
{
    unsigned int emp_id;
    char emp_name[MAX_LIMIT];
    char emp_designation[MAX_LIMIT];
    char emp_department[MAX_LIMIT];  
}emp;

int main()
{
    /* Constant declaration */
    /* Old file name and new file name */
    const char SOURCE_FILENAME[] = "d:/emp.dat";
    const char TARGET_FILENAME[] = "d:/temp.dat";
    
    /* Variable declaration */
    unsigned short int choice = 10;
    unsigned short int record_number = 0;
    unsigned short int is_found = 0;
    unsigned int empid;
    long int return_value = 0;
    long int error_number = 0;
    
    /* Source and target file pointers declaration */ 
    FILE *sfptr, *tfptr;
    
    /* Structure instance creation */
    emp e;
    
    while(choice != 0)
    {
        /* create and display menu */
        printf("\n");
        printf("+-----------------------------------+\n");
        printf("|     Employee Management System    |\n");
        printf("+-----------------------------------+\n");
        printf("| 1 -> Add   2 -> Search  3 -> List |\n");
        printf("| 4 -> Edit  5 -> Delete  6 -> Exit |\n");
        printf("+-----------------------------------+\n\n");
        
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:  /* Add */
                /* open file for append mode */
                sfptr = fopen(SOURCE_FILENAME,"ab");
                if (sfptr == NULL)
                {
                    printf("%s can not open for appending\n",SOURCE_FILENAME);
                    exit(0);
                }
                
                /* to accept space in input, use gets or fgets instead of scanf
                 * gets function is removed from C11 onwards, hence use fgets only 
                 * or scanf with %[^\n]s or scanf with %[^\n]%*c */
                printf("Enter employee id          : ");
                scanf("%i",&e.emp_id);
                printf("Enter employee name        : ");
                getchar();
                scanf("%[^\n]s",e.emp_name);
                /* fgets(e.emp_name, MAX_LIMIT, stdin); */         
                printf("Enter employee designation : ");
                getchar();
                scanf("%[^\n]s",e.emp_designation);
                /* fgets(e.emp_designation, MAX_LIMIT, stdin); */
                printf("Enter employee department  : ");
                getchar();
                scanf("%[^\n]s",e.emp_department);
                /* fgets(e.emp_department, MAX_LIMIT, stdin); */

                /* Append record to source file */
                return_value = fwrite(&e,sizeof(e),1,sfptr);
                
                if(return_value > 0)
                {
                    printf("Emp id %d details written successfully\n",e.emp_id);
                }
                else
                {
                    printf("Emp id %d details did not write to file\n",e.emp_id);
                }
                
                /* Close the source file */
                fclose(sfptr);
                
                break;                
            case 2:  /* Search */
                /* open file for read mode */
                sfptr = fopen(SOURCE_FILENAME,"rb");
                if (sfptr == NULL)
                {
                    printf("%s can not open for reading\n",SOURCE_FILENAME);
                    exit(0);
                }
                
                printf("Enter employee id to be searched : ");
                scanf("%d",&empid);
                
                /* reset record_number and is_found flag */
                record_number = 0;
                is_found = 0;
                
                while(1)
                {
                    fread(&e,sizeof(e),1,sfptr);
                    /* break the loop once it reaches end of the file */
                    if(feof(sfptr) ) 
                    { 
                        break ;
                    }
                    
                    record_number++;
                    
                    if(e.emp_id == empid)
                    {
                        is_found = 1;
                        break;
                    }
                }
                
                if(is_found == 1)
                {
                    printf("Emp id %d is found in record : %d\n",empid,record_number);
                    printf("+-----+--------------------+--------------------+-------------------+\n");
                    printf("|Id   |Name                |Designation         |Department         |\n");
                    printf("+-----+--------------------+--------------------+-------------------+\n");                    
                    printf("|%-5i",e.emp_id);
                    printf("|%-20s",e.emp_name);
                    printf("|%-20s",e.emp_designation);
                    printf("|%-19s|\n",e.emp_department);
                    printf("+-----+--------------------+--------------------+-------------------+\n");
                }
                else
                {
                    printf("Emp id %d is not found\n",empid);
                }
                
                /* Close the source file */
                fclose(sfptr);
                
                break;
            case 3:  /* List */
                /* open file for read mode */
                sfptr = fopen(SOURCE_FILENAME,"rb");
                if (sfptr == NULL)
                {
                    printf("%s can not open for reading\n",SOURCE_FILENAME);
                    exit(0);
                }
                printf("+-----+--------------------+--------------------+-------------------+\n");
                printf("|Id   |Name                |Designation         |Department         |\n");
                printf("+-----+--------------------+--------------------+-------------------+\n");
                while(1)
                {
                    fread(&e,sizeof(e),1,sfptr);
                    /* break the loop once it reaches end of the file */
                    if(feof(sfptr)) 
                    { 
                        break ;
                    }
                            
                    printf("|%-5i",e.emp_id);
                    printf("|%-20s",e.emp_name);
                    printf("|%-20s",e.emp_designation);
                    printf("|%-19s|\n",e.emp_department);                
                }
                printf("+-----+--------------------+--------------------+-------------------+\n");
                
                /* Close the source file */
                fclose(sfptr);
                
                break;
            case 4:  /* Edit */
                /* open source file for read mode */
                sfptr = fopen(SOURCE_FILENAME,"rb");
                if (sfptr == NULL)
                {
                    printf("%s can not open for reading\n",SOURCE_FILENAME);
                    exit(0);
                }

                /* open target file for write mode */
                tfptr = fopen(TARGET_FILENAME,"wb");
                if (tfptr == NULL)
                {
                    printf("%s can not open for writing\n",TARGET_FILENAME);
                    exit(0);
                }          
                                
                printf("Enter employee id to be modified : ");
                scanf("%d",&empid);
                
                /* reset record_number and is_found flag */
                record_number = 0;
                is_found = 0;
                
                while(1)
                {
                    /* read from source file */
                    fread(&e,sizeof(e),1,sfptr);
                    
                    /* break the loop once it reaches end of the file */
                    if(feof(sfptr) ) 
                    { 
                        break ;
                    }
                    
                    record_number++;
                    
                    if(e.emp_id == empid)
                    {
                        is_found = 1;
                        printf("Enter new employee name        : ");
                        getchar();
                        scanf("%[^\n]s",e.emp_name);        
                        printf("Enter new employee designation : ");
                        getchar();
                        scanf("%[^\n]s",e.emp_designation);
                        printf("Enter new employee department  : ");
                        getchar();
                        scanf("%[^\n]s",e.emp_department);
                        
                        /* write updated data into target file */
                        return_value = fwrite(&e,sizeof(e),1,tfptr);
                        if(return_value <= 0)
                        {
                            error_number = -1;
                            printf("Record did not write into %s\n",TARGET_FILENAME);
                        }
                    }
                    else
                    {
                        /* write existing data into target file */
                        return_value = fwrite(&e,sizeof(e),1,tfptr);
                        if(return_value <= 0)
                        {
                            error_number = -1;
                            printf("Record did not write into %s\n",TARGET_FILENAME);
                        }
                    }
                }
                
                /* Close the source and target file */
                fclose(sfptr);
                fclose(tfptr);
                
                /* Delete source file and rename target file to source file */
                remove(SOURCE_FILENAME);
                rename(TARGET_FILENAME,SOURCE_FILENAME);
          
                if(is_found == 1 && error_number == 0)
                {
                    printf("Emp id %d found at record number %d & updated successfully\n",empid,record_number);
                }
                else
                {
                    printf("Emp id %d is not found\n",empid);
                }
                break;                
            case 5:  /* Delete */
                /* open source file for read mode */
                sfptr = fopen(SOURCE_FILENAME,"rb");
                if (sfptr == NULL)
                {
                    printf("%s can not open for reading\n",SOURCE_FILENAME);
                    exit(0);
                }

                /* open target file for write mode */
                tfptr = fopen(TARGET_FILENAME,"wb");
                if (tfptr == NULL)
                {
                    printf("%s can not open for writing\n",TARGET_FILENAME);
                    exit(0);
                }          
                                
                printf("Enter employee id to be deleted : ");
                scanf("%d",&empid);
                
                /* reset record_number and is_found flag */
                record_number = 0;
                is_found = 0;
                
                while(1)
                {
                    /* read from source file */
                    fread(&e,sizeof(e),1,sfptr);
                    
                    /* break the loop once it reaches end of the file */
                    if(feof(sfptr) ) 
                    { 
                        break ;
                    }
                    
                    record_number++;
                    
                    if(e.emp_id == empid)
                    {
                        is_found = 1;
                    }
                    else
                    {
                        /* write existing data into target file */
                        return_value = fwrite(&e,sizeof(e),1,tfptr);
                        if(return_value <= 0)
                        {
                            error_number = -1;
                            printf("Record did not write into %s\n",TARGET_FILENAME);
                        }
                    }
                }
                
                /* Close the source and target file */
                fclose(sfptr);
                fclose(tfptr);
                
                /* Delete source file and rename target file to source file */
                remove(SOURCE_FILENAME);
                rename(TARGET_FILENAME,SOURCE_FILENAME);

                if(is_found == 1 && error_number == 0)
                {
                    printf("Emp id %d found at record number %d & deleted successfully\n",empid,record_number);
                }
                {
                    printf("Emp id %d is not found\n",empid);
                }          
                break;    
            default: /* Exit */
                printf("Thank you for using our software\n");
                exit(0);
        }
    }
    return 0;
}
