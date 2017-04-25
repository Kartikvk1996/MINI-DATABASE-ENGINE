%{
  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>
%}

%token CREATE DROP INSERT DELETE UPDATE SELECT FROM TABLE VALUES SPACE VAR EOQ NUM


%%

start:body EOQ {printf("Query successfully parsed\n"); exit(0);}

body:create
;

//--------------------------CREATE---------------------------
create:CREATE TABLE VAR '('fields')'
;

fields:single  fields
|multiple  fields
;

single:VAR declaration constraint
;

multiple:VAR declaration constraint','
;

declaration:VAR'('NUM')'
|VAR
;

constraint:VAR constraint
|
;
//--------------------------------------------------------------------





%%

int yyerror(char *msg)
{
  printf("Invalid syntax\n");
  exit(0);
}

int main()
{
  printf("MYDATABASE : ");
  yyparse();
  return 0;
}
