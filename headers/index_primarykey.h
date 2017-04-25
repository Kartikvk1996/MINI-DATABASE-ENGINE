struct index_pk *ptr_to_index=NULL;

struct index_pk *tb[100];


int check_int_constraint(int key,int value)
{
    //printf("Call to integer constraint key=%d value=%d\n",key,value);
    int i=0;
    int hash_key=key;
    hash_key%=100;
    //printf("Hash key %d\n",hash_key);

   // printf("Hash key index %d\n",hash_key);
    struct index_pk *temp=ch.ptr_to_index[hash_key];
    if(temp==NULL)
    {
     //    printf("Miss\n");
        return 1;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
           // printf("%d   %d \n",temp->i_data,value);
            if(temp->i_data==value)
            {
                return -1;
            }

            temp=temp->ptr;
        }
    }
    return 1;
}

int check_float_constraint(int key,float value)
{
    int i=0;
    int hash_key=key;
    hash_key%=table_size;
   // printf("Hash key index %d\n",hash_key);
    struct index_pk *temp=ch.ptr_to_index[hash_key];
    if(temp==NULL)
    {
     //    printf("Miss\n");
        return 1;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
            if(temp->f_data==value)
            {
                return -1;
            }

            temp=temp->ptr;
        }
    }
    return 1;
}

int check_double_constraint(int key,double value)
{
    int i=0;
    int hash_key=key;
    hash_key%=table_size;
   // printf("Hash key index %d\n",hash_key);
    struct index_pk *temp=ch.ptr_to_index[hash_key];
    if(temp==NULL)
    {
     //    printf("Miss\n");
        return 1;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
            if(temp->d_data==value)
            {
                return -1;
            }

            temp=temp->ptr;
        }
    }
    return 1;
}

int check_string_constraint(int key,char *value)
{
    int i=0;
    int hash_key=key;
    hash_key%=table_size;
   // printf("Hash key index %d\n",hash_key);
    struct index_pk *temp=ch.ptr_to_index[hash_key];
    if(temp==NULL)
    {
     //    printf("Miss\n");
        return 1;
    }
    else
    {
      //  printf("Hit\n");
        while(temp!=NULL)
        {
            if((strcmp(temp->c_data,value))==0)
            {
                return -1;
            }
            temp=temp->ptr;
        }
    }
    return 1;
}

void insertion_into_index(int data,struct index_pk *root,int datatype)
{

    int i=0;
    int hash_key=data;

    hash_key%=100;

    if(tb[hash_key]==NULL)
    {
        tb[hash_key]=root;
    }
    else
    {
        struct index_pk *temp=tb[hash_key];
        struct index_pk *prev=NULL;
        while(temp!=NULL)
        {
            prev=temp;
            temp=temp->ptr;
        }
        //printf(" %d attached to end",root->i_data);
        prev->ptr=root;
    }
    return;

}

void delete_pk_index(int pos)
{
    free(ptr_to_index);
    strcpy(ch.table_name,"null");
    return;
}

int create_index(struct metadata *mdata)
{
    if(ptr_to_index!=NULL)
    {
        free(ptr_to_index);
        ptr_to_index=NULL;
    }


    struct index_pk *index_table=(struct index_pk *)malloc(sizeof(struct index_pk)*1000);
    ptr_to_index=index_table;
    char path[25]="tables/";
    strcat(path,mdata->table_name);
    FILE *fp=fopen(path,"r");
    if(fp==NULL)
    {
        printf("Error opening file to create index\n");
        return ;
    }

    struct data
    {
        char string_data[mdata->tot_char][max_user_input];
        int integer_data[mdata->tot_int];
        float float_data[mdata->tot_float];
        double double_data[mdata->tot_double];

    }user_data;

    int offset=0;
    int col=0,i=0,f=0,c=0,d=0;
    while(col<mdata->no_of_cols)
    {
        if(strcmp(mdata->attributes[col],mdata->primary_key)==0)
        {
            break;
        }
        else
        {
            if(mdata->attr_datatype[col][0]=='i')
            {
                i++;
            }
            else if(mdata->attr_datatype[col][0]=='f')
            {
                f++;
            }
            else if(mdata->attr_datatype[col][0]=='d')
            {
                d++;
            }
            else
            {
                c++;
            }
        }
        col++;
    }

    char datatype=mdata->attr_datatype[col][0];
    int total_rows=0;
    int ittr=0,val=0;


    while(fread(&user_data,sizeof(user_data),1,fp))
    {
        if(datatype=='c')
        {
            while(user_data.string_data[c][ittr]!='\0')
            {
                val+=user_data.string_data[c][ittr];
                ittr++;
            }
            index_table[total_rows].dt=1;
            strcpy(index_table[total_rows].c_data,user_data.string_data[c]);
            insertion_into_index(val,&index_table[total_rows],1);
        }
        else if(datatype=='i')
        {
            index_table[total_rows].dt=2;
            index_table[total_rows].i_data=user_data.integer_data[i];
            insertion_into_index(user_data.integer_data[i],&index_table[total_rows],2);
        }
        else if(datatype=='f')
        {
            index_table[total_rows].dt=3;
            index_table[total_rows].f_data=user_data.float_data[f];
            insertion_into_index(user_data.float_data[f]/1,&index_table[total_rows],3);
        }
        else
        {
            index_table[total_rows].dt=4;
            index_table[total_rows].d_data=user_data.float_data[d];
            insertion_into_index(user_data.double_data[d]/1,&index_table[total_rows],4);
        }
        total_rows++;
    }

    printf("Index created\n");

    index_table=realloc(index_table,sizeof(struct index_pk)*total_rows)   ;

    ch.ptr_to_index=tb;
    strcpy(ch.table_name,mdata->table_name);
    return 1;

};



/*
int free_cache(struct cache *ch)
{
    int ittr=1;
    int min=ch[0].num_of_calls_to_table;
    int pos=0;
    while(ittr<cache_size-1)
    {
        if(min>ch[ittr].num_of_calls_to_table)
        {
            min=ch[ittr].num_of_calls_to_table;
            pos=ittr;
        }
        ittr++;
    }

    free_cache_();
    return pos;
}


void free_cache_()
{

}
*/

