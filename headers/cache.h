// global array to cache data
struct cache ch;

void init_cache()
{
    ch.num_of_calls_to_table=0;
    ch.ptr_to_index=NULL;
    return ;
}

int get_index_primarykey(struct metadata *mdata)
{
    if(strcmp(mdata->table_name,ch.table_name)==0)
    {
        return 0;
    }
    return -1;
}




