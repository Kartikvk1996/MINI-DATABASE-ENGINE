struct cache mcache[cache_size];    //cache sixe of 10;
int track_cache=0;

void init_cache()
{
    int i=0;
    while(i<cache_size)
    {
        mcache.ptr=NULL;
        i++;
    }
}

struct btreeNode *get_index_tree(char *table_name)
{
    int i=0;
    while(i<cache_size)
    {
        if(strcmp(mcache[i].table_name,table_name)==0)
        {
            return mcache.ptr;
        }
        i++;
    }
    if(add_to_cache(table_name)>0)
    {
        return mcache[track_cache].ptr;
    }
    else
    {
        return NULL;
    }
}

void add_to_cache(char *table_name)
{
    if(track_cache==(cache_size-1))
    {
        track_cache=0;
    }

    struct metadata *temp=get_metadata(teble_name);
    if(strcmp(temp->primary_key,NULL)==0)
    {
        return -1;
    }
    else
    {
        struct data
        {
            char string_data[temp->tot_char][max_user_input];
            int integer_data[temp->tot_int];
            float float_data[temp->tot_float];
            double double_data[temp->tot_double];
        }user_data;

        char path[30]="tables/";
        strcat(path,table_name);
        fp=fopen(path,"r");
        if(fp==NULL)
        {
            printf("Error in reading file while indexing\n");
            return -1;
        }

        int offset=0;
        int col=0,i=0,f=0,c=0,d=0;
        while(col<temp->no_of_cols)
        {
            if(strcmp(temp->attributes[i],temp->primary_key)==0)
            {
                if(temp->attr_datatype[i][0]=='i')
                {
                    i++;
                }
                else if(temp->attr_datatype[i][0]=='f')
                {
                    f++;
                }
                else if(temp->attr_datatype[i][0]=='d')
                {
                    d++;
                }
                else
                {
                    c++;
                }
                break;
            }
            else
            {
                if(temp->attr_datatype[i][0]=='i')
                {
                    i++;
                }
                else if(temp->attr_datatype[i][0]=='f')
                {
                    f++;
                }
                else if(temp->attr_datatype[i][0]=='d')
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

        char datatype=temp->attr_datatype[col][0];
        while(fread(&user_data,sizeof(user_data),1,fp))
        {
            if(datatype=='c')
            {
                insertion(user_data.string_data[c]);
            }
            else if(datatype=='i')
            {
                insertion_i(user_data.integer_data[i]);
            }
            else if(datatype=='f')
            {
                insertion_f(user_data.float_data[i]);
            }
            else
            {
                insertion_d(user_data.double_data[i]);
            }

        }

    }
}
