void display()
{
    FILE *fp=fopen("meta/metadata","r");

    while(fread(&meta,sizeof(meta),1,fp))
    {
        printf("\n\n-------------------Table Name : %s ---------Primary Key : %s--------------------\n\n",meta.table_name,meta.primary_key);

        int i;
        printf("\tAttributes \t Data_Type \t Size \t\n");
        for(i=0;i<meta.no_of_cols;i++)
        {
            printf("\t%10s\t%10s\t%5d\t\n",meta.attributes[i],meta.attr_datatype[i],meta.attr_datatype_size[i]);
        }
        printf("\n-----------------------------------------------------------------------------\n");
    }

    fclose(fp);
}
