#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<sys/time.h>


#include"headers/define.h"
#include"headers/structure.h"
#include"headers/create.h"
#include"headers/read_metadata.h"
#include"headers/hash_metadata.h"
#include"headers/cache.h"
#include"headers/index_primarykey.h"
#include"headers/insert.h"
#include"headers/desc.h"
#include"headers/select.h"

int check_query_type(char *query,struct metadata **table)
{
    char temp[100];
    int ittr=0;
    while(query[ittr]!=' ')
    {
        temp[ittr]=query[ittr];
        ittr++;
    }
    temp[ittr]='\0';
    if((strcmp(temp,"create"))==0)
    {
        parse_create_query(query,table);
    }
    else if((strcmp(temp,"show"))==0)
    {
        display();
    }
    else if((strcmp(temp,"insert"))==0)
    {
        parse_insert_query(query,table);
    }
    else if((strcmp(temp,"desc"))==0)
    {
        description(query,table);
    }
    else if((strcmp(temp,"select"))==0)
    {
        parse_select_query(query,table);
    }
    else
    {

    }
    return ;
}



int main()
{

    struct timeval t0,t1;
    float exec_time=0;

    struct metadata *table[table_size];
    int ittr;
    for(ittr=0;ittr<table_size;ittr++)
    {
        table[ittr]=NULL;
    }
    create_metadata_hashmap(table);
    init_cache();

    //display_hashmap(table);


    char *query = (char *)malloc(sizeof(char)*query_size);

    printf("MDE < ( 'q' to quit ) :  ");
    scanf("%[^\n]sizeof(query)s",query);


    gettimeofday(&t0,0);


    char temp[query_size+100];
    int i=0;
    int j=0;
    while(query[i])
    {
        if(query[i]=='(' || query[i]==')' || query[i]==',')
        {
            if(query[i-1]!=' ')
            {
                temp[j++]=' ';
            }
            temp[j++]=query[i++];
            if(query[i]!=' ')
            {
                temp[j++]=' ';
            }
        }
        else
        {
            temp[j++]=query[i++];
        }
    }
    temp[j]='\0';
    printf("%s\n",temp);
    check_query_type(temp,table);

    gettimeofday(&t1,0);
    exec_time=(t1.tv_sec-t0.tv_sec)*1000000.0f+(t1.tv_usec-t0.tv_usec)/1000000.0f;
    printf("\n\nResponce time -- %f us (microseconds)\n\n",exec_time);


    free(query);
    free(ptr_to_index);
    free_metada_hashmap();

    return 1;
}
