// parse the select query
void parse_select_query(char *query,struct metadata **table)
{
    char *fields_to_select;
    char *table_name;
    strsep(&query," ");     // skip 'select' command
    fields_to_select=strsep(&query," ");
    if(fields_to_select[0]=='*')
    {
        strsep(&query," "); // skip 'from' command
        table_name=strsep(&query," ");
        struct metadata *table_data=get_metadata(table_name,table); // pass table_name and hashtable as parameter
        if(table_data==NULL)
        {
            printf("Table not found\n");
            return;
        }
        else
        {
            char path[100]="tables/";
            strcat(path,table_name);
            FILE *fp=fopen(path,"r");
            if(fp==NULL)
            {
                printf("Error in reading file\n");
                return;
            }

            struct data
            {
                char string_data[table_data->tot_char][max_user_input];
                int integer_data[table_data->tot_int];
                float float_data[table_data->tot_float];
                double double_data[table_data->tot_double];
            }user_data;


            int tot_int=0,tot_float=0,tot_double=0,tot_char=0,tot_col=0;


            printf("\n\n-------------------Table Name : %s ---------Primary Key : %s--------------------\n\n",table_data->table_name,table_data->primary_key);

            int i;
            printf("\t");
            for(i=0;i<table_data->no_of_cols;i++)
            {
                printf("%10s\t",table_data->attributes[i]);
            }
            printf("\n");

            while(fread(&user_data,sizeof(user_data),1,fp))
            {
                while(tot_col<table_data->no_of_cols)
                {
                    if(table_data->attr_datatype[tot_col][0]=='i')
                    {
                        tot_col++;
                        printf("\t%10d\t",user_data.integer_data[tot_int++]);
                    }
                    else if(table_data->attr_datatype[tot_col][0]=='f')
                    {
                        tot_col++;
                        printf("\t%10f\t",user_data.float_data[tot_float++]);
                    }
                    else if(table_data->attr_datatype[tot_col][0]=='d')
                    {
                        tot_col++;
                        printf("\t%10f\t",user_data.double_data[tot_double++]);
                    }
                    else
                    {
                        printf("\t%10s\t",user_data.string_data[tot_char++]);
                        tot_col++;
                    }
                }
                tot_int=0,tot_float=0,tot_double=0,tot_char=0,tot_col=0;
                printf("\n");
            }
            printf("----------------------------------------------------------------------------------\n");
            fclose(fp);
            return;
        }
    }
}
