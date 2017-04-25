// This functions parse the 'create' table query
void parse_create_query(char *query,struct metadata **table)
{
    char *temp;
    char *table_name;
    char fieldset[max_cols];
    strsep(&query," "); // skip 'create' keyword in query
    strsep(&query," "); // skip 'table' keyword in query
    table_name=strsep(&query," ");      // copy the table_name
    if(check_table_exist(table_name,table)>0)   // search matadata with table_name to check table exist or not
    {
        printf("Table already exist\n");
        return;
    }
    strsep(&query," "); // skip '(' character

    // extract all the fields given by user
    while((temp=strsep(&query," "))!=NULL)
    {
        strcat(fieldset,temp);
        strcat(fieldset," ");
    }


    //printf("%s\n",fieldset);

    if(generate_fieldsets(table_name,fieldset)>0)   // call to generate_fieldsets() function
    {
        printf("Table created successfully\n");
    }
    else
    {
        printf("Failed in creating table\n");
    }
}


//  This function copies the parameters passes by user to fieldset
int generate_fieldsets(char *table_name,char *data)
{
    char fieldsets[max_cols][length_attributes];

    int i=0,total_attr=0,j=0;
    char temp[100];
    char primary_data[length_attributes];
    strcpy(primary_data,"null");


    int track_pk=0;
    int set_primary_key=0;  // check not more than 1 primary_key is specified
    int pk_col=-1; //        // copy to which column primary_key constraint is applied
    // copy arguments till the end of query
    for(i=0;data[i]!=')' && data[i+1]!=';' ;i++)
    {
        if(data[i]==',')
        {
            track_pk++;
            if(total_attr%3!=0) // copy null if no constraints are specified
            {
                while((total_attr%3)!=0)
                {
                    strcpy(fieldsets[total_attr],"null");
                    total_attr++;
                }
            }
        }
        else if(data[i]==' ')
        {
            if(j!=0)
            {
                temp[j]='\0';
                strcpy(fieldsets[total_attr],temp);
                if((strcmp(temp,"primary_key"))==0) // checks not more than 1 primary_key is specified
                {
                    if(set_primary_key==0)
                    {
                        strcpy(primary_data,fieldsets[total_attr-2]);
                        set_primary_key=1;
                        pk_col=track_pk;

                    }
                    else
                    {
                        printf("Error : More than two attributes have primary key\n");
                        return -1;
                    }


                }
                j=0;
                total_attr++;
            }

        }
        else
        {
            temp[j++]=data[i];
        }
    }
    if(total_attr%3!=0)
    {
        while((total_attr%3)!=0)
        {
            strcpy(fieldsets[total_attr],"null");
            total_attr++;
        }
    }
    /*for(i=0;i<total_attr;i++)
    {
        printf("%s\n",fieldsets[i]);
    }
    printf("primary key -> %s\n",primary_data);
    */
    if(create_metadata(table_name,fieldsets,primary_data,total_attr,pk_col)>0) // creating table_metadata
    {
        return 1;
    }
    else
    {
        return -1;
    }
}


int create_metadata(char *table_name,char fieldsets[][length_attributes],char *primary_data ,int total_attr,int pk_col)
{
    if(total_attr%3!=0)
    {
        printf("%d\n",total_attr);
        printf("Error : invalid attributes\n");
        return -1;
    }
    total_attr/=3;
    int i=0,j=0;

    //initialize the values
    strcpy(meta.table_name,table_name);
    strcpy(meta.primary_key,primary_data);
    meta.no_of_cols=total_attr;
    meta.ptr=NULL;
    meta.tot_int=0;
    meta.tot_float=0;
    meta.tot_double=0;
    meta.tot_char=0;
    meta.primary_key_col=pk_col;
    while(j<total_attr)
    {
        strcpy(meta.attributes[j],fieldsets[i]);
        if(fieldsets[i+1][0]=='c')
        {
            strcpy(meta.attr_datatype[j],"char");
        }
        else
        {
            strcpy(meta.attr_datatype[j],fieldsets[i+1]);
        }

        if(fieldsets[i+1][0]=='i')
        {
            meta.attr_datatype_size[j]=sizeof(int);
            meta.tot_int++;
        }
        else if(fieldsets[i+1][0]=='f')
        {
            meta.attr_datatype_size[j]=sizeof(float);
            meta.tot_float++;
        }
        else if(fieldsets[i+1][0]=='d')
        {
            meta.attr_datatype_size[j]=sizeof(double);
            meta.tot_double++;
        }
        else
        {
            meta.attr_datatype_size[j]=255;

            meta.tot_char++;
        }
        j++;
        i+=3;
        printf("%d\t %d\t %s\n",i,j,fieldsets[i]);
    }


    FILE *fp=NULL;
    if((fp=fopen("meta/metadata","a+"))==NULL)  // Open metadata file
    {
        printf("Error in opening metadata\n");
        return -1;
    }
    //printf("%s\n%s\n%s\n",meta.attributes[0],meta.attributes[3],meta.attributes[6]);
    fwrite(&meta,sizeof(meta),1,fp);    // write to metadata
    fclose(fp);                         // close the file


    // Below code creates a table with specified name
    char path[50]="tables/";
    strcat(path,table_name);
    printf("%s\n",path);;
    fp=fopen(path,"w");
    if(fp==NULL)
    {
        printf("Failed in creating table\n");
        return -1;
    }
    fclose(fp);
    return 1;

}
