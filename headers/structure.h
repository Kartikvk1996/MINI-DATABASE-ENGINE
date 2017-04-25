#define size 63
struct metadata
{
    char table_name[size];
    char attributes[10][length_attributes];
    char attr_datatype[10][10];
    int attr_datatype_size[10];
    char primary_key[size];
    int primary_key_col;
    int no_of_cols;
    int tot_int;
    int tot_float;
    int tot_double;
    int tot_char;
    struct metadata *ptr;
}meta;


// dt=1 for char
//  2 - int
//  3 - float
//  4 - double;
struct index_pk
{
    int dt;
    char c_data[max_user_input];
    int i_data;
    float f_data;
    double d_data;
    struct index_pk *ptr;
};


struct cache
{
    char table_name[max_user_input];
    int num_of_calls_to_table;
    struct index_pk **ptr_to_index;

};



