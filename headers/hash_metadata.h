

struct metadata *ptr_to_memory;

void metadata_hashmap(struct metadata **table,struct metadata *root)
{
    int i=0;
    int hash_key=0;
    while(root->table_name[i]!='\0')
    {
        hash_key+=root->table_name[i];
        i++;
    }
    hash_key%=table_size;
    if(table[hash_key]==NULL)
    {
        table[hash_key]=root;
    }
    else
    {
        struct metadata *temp=table[hash_key];
        struct metadata *prev=NULL;
        while(temp!=NULL)
        {
            prev=temp;
            temp=temp->ptr;
        }
        prev->ptr=root;
    }

    return;

}

void create_metadata_hashmap(struct metadata **table)
{
    struct metadata *tb_data=(struct metadata *)malloc(sizeof(struct metadata)*max_tables);
    ptr_to_memory=tb_data;
    FILE *fp=fopen("meta/metadata","r");
    if(fp==NULL)
    {
        printf("Error opening file\n");
        FILE *fp=fopen("meta/metadata","w");
        fclose(fp);
        return ;
    }
    int tot_tables=0;
    while(fread(&tb_data[tot_tables],sizeof(tb_data[tot_tables]),1,fp))
    {

       // printf("----------------------------insert of %s\n",tb_data[tot_tables].table_name);
        metadata_hashmap(table,&tb_data[tot_tables]);
        tot_tables++;
    }
    fclose(fp);
    return;
}

int check_table_exist(char *table_name,struct metadata **table)
{
    int i=0;
    int hash_key=0;
    while(table_name[i])
    {
        hash_key+=table_name[i++];
    }
    hash_key%=table_size;
   // printf("Hash key index %d\n",hash_key);
    struct metadata *temp=table[hash_key];
    if(temp==NULL)
    {
     //    printf("Loss\n");
        return -1;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
            if((strcmp(temp->table_name,table_name))==0)
            {
                return 1;
            }
            temp=temp->ptr;
        }
    }
    return -1;
}


void show_table_name(struct metadata *table)
{
    if(table!=NULL)
    {
        printf("---> %s",table->table_name);
    }
    return;
}



void display_hashmap(struct metadata **table)
{
    int ittr=0;
    while(ittr<table_size)
    {
        printf("arr[ %d ] - ",ittr);
        show_table_name(table[ittr]);
        printf("\n");
        ittr++;
    }
    return;
}




void free_metada_hashmap()
{
    printf("Memory freed\n");
        free(ptr_to_memory);
}


struct metadata *get_metadata(char *table_name,struct metadata **table)
{
    int i=0;
    int hash_key=0;
    while(table_name[i])
    {
        hash_key+=table_name[i++];
    }
    hash_key%=table_size;
   // printf("Hash key index %d\n",hash_key);
    struct metadata *temp=table[hash_key];
    if(temp==NULL)
    {
     //    printf("Loss\n");
        return NULL;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
            if((strcmp(temp->table_name,table_name))==0)
            {
                return temp;
            }
            temp=temp->ptr;
        }
    }
    return NULL;
};
