void description(char *query,struct metadata **table)
{
    strsep(&query," "); //skip desc command

    char *table_name=strsep(&query," ");

    struct metadata *data=get_metadata(table_name,table);
    if(data==NULL)
    {
        printf("Table Not Found\n");
        return ;
    }

    printf("\n\n-------------------Table Name : %s ---------Primary Key : %s--------------------\n\n",data->table_name,data->primary_key);

    int i;
    printf("\tAttributes \t Data_Type \t Size \t\n");
    for(i=0;i<data->no_of_cols;i++)
    {
        printf("\t%10s\t%10s\t%5d\t\n",data->attributes[i],data->attr_datatype[i],data->attr_datatype_size[i]);
    }
    printf("\n-----------------------------------------------------------------------------\n");
}
