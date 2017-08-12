// parse the insert query
void parse_insert_query(char *query,struct metadata **table)
{
    char *table_name=NULL;
    strsep(&query," ");
    strsep(&query," ");
    table_name=strsep(&query," ");
    struct metadata *temp=get_metadata(table_name,table);


    if(temp==NULL)
    {
        printf("No table found\n");
        return ;
    }

    printf("Metadata got %s %d\n",temp->table_name,temp->no_of_cols);


    // checking primary_key constraint added or not
    int index=0;
    int is_exist_pk=0;
    if(strcmp(temp->primary_key,"null")!=0)
    {
        int is_exist_pk=1;
        printf("Primary_key present\n");
        index=get_index_primarykey(temp);
        if(index==-1)
        {
            printf("Index not found\n");
             index=create_index(temp);
        }
        else
        {
            printf("Index found\n");
        }

    }
    // creating local structure
    struct data
    {
        char string_data[temp->tot_char][max_user_input];
        int integer_data[temp->tot_int];
        float float_data[temp->tot_float];
        double double_data[temp->tot_double];

    }user_data;


    //clear garbage value in user_data
    int i=0;
    for(i=0;i<temp->tot_char;i++)
    {
        user_data.string_data[i][0]='\0';
    }

    char *dataset[temp->no_of_cols*2];
    strsep(&query," "); // skip 'values'
    strsep(&query," "); // skip '(' bracket
    int ittr=0;
    // copying user data into dataset
    while(ittr<((temp->no_of_cols*2)-1))
    {
        dataset[ittr]=strsep(&query," ");
        ittr++;
    }


    char *end_of_query=NULL;
    end_of_query=strsep(&query," ");
    if(strcmp(end_of_query,")")!=0) // chect last arg should be ')' bracket
    {
        printf("Total arguments passed was incorrect\n");
        return ;
    }
    ittr=0;
    int j=0;



    int data=0,k=0;
    int jump=0;


    if(temp->primary_key_col!=0)
    {
        jump=temp->primary_key_col*2;
    }
  /*  printf("Value = %d\n",atoi(dataset[jump]));
    printf("primary key col %d\n",temp->primary_key_col);
    printf(" off  %d\n",jump);*/
    if(temp->attr_datatype[temp->primary_key_col][0]=='c')
    {

        while(dataset[jump][k]!='\0')
        {
            data+=dataset[jump][k];
            k++;
        }

    }
    if(temp->attr_datatype[temp->primary_key_col][0]=='c')
    {
        if(check_string_constraint(data,dataset[jump])<0)
        {
            printf("Violation of primary key constraint\n");
            return;
        }
    }
    else if(temp->attr_datatype[temp->primary_key_col][0]=='i')
    {
        if(check_int_constraint(atoi(dataset[jump]),atoi(dataset[jump]))<0)
        {
            printf("Violation of primary key constraint\n");
            return;
        }
    }
    else if(temp->attr_datatype[temp->primary_key_col][0]=='f')
    {
        //printf("%d %f\n",atoi(dataset[jump]),atof(dataset[jump]));
        if(check_float_constraint(atoi(dataset[jump]),atof(dataset[jump]))<0)
        {
            printf("Violation of primary key constraint\n");
            return;
        }
    }
    else
    {
        if(check_double_constraint(atoi(dataset[jump]),atof(dataset[jump]))<0)
        {
            printf("Violation of primary key constraint\n");
            return;
        }
    }


    int u_int=0,u_float=0,u_double=0,u_string=0;    // to keep track of user data

    while(ittr<temp->no_of_cols)
    {

        if(temp->attr_datatype[ittr][0]=='i')   //if integer is datatype
        {
            if(u_int<temp->tot_int)
            {
                user_data.integer_data[u_int]=atoi(dataset[j]);
                u_int++;
                j=j+2;
            }
            else
            {
                printf("Error 1\n");
            }
        }
        else if(temp->attr_datatype[ittr][0]=='f')
        {
            if(u_float<temp->tot_float)
            {
                user_data.float_data[u_float]=atof(dataset[j]);
                u_float++;
                j=j+2;
            }
            else
            {
                printf("Error 2\n");
            }
        }
        else if(temp->attr_datatype[ittr][0]=='d')
        {
            if(u_double<temp->tot_double)
            {
                user_data.double_data[u_double]=atof(dataset[j]);
                u_double++;
                j=j+2;
            }
            else
            {
                printf("Error 3\n");
            }
        }
        else
        {
            if(u_string<temp->tot_char)
            {
                if(strlen(dataset[j])>255)
                {
                    printf("Error max string length is 255 characters\n");
                    return;
                }
                strcpy(user_data.string_data[u_string],dataset[j]);
                u_string++;
                j=j+2;
            }
            else
            {
                printf("Error 4\n");
            }
        }
        ittr++;
    }

    if(u_int!=temp->tot_int || u_float!=temp->tot_float || u_double!=temp->tot_double || u_string!=temp->tot_char)
    {
        printf("Arguments error\n");
        return ;
    }

    char path[100]="tables/";
    strcat(path,table_name);
    FILE *fp=fopen(path,"a");
    int lock=flock(fileno(fp),LOCK_EX); // lock a file
    if(fp==NULL)
    {
        printf("Error opening file to insert data\n");
        return ;
    }

    fwrite(&user_data,sizeof(user_data),1,fp);
    int unlock=flock(fileno(fp),LOCK_UN);   // unlock a file
    fclose(fp);
    printf("Data inserted successfully\n");
    return ;
}
