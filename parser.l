%{
  #include<stdio.h>
  #include"parser.tab.h"
%}

%%
"create"  {return CREATE;}
"drop"    {return DROP;}
"select"  {return SELECT;}
"insert"  {return INSERT;}
"update"  {return UPDATE;}
"delete"  {return DELETE;}
"values"  {return VALUES;}
"from"    {return FROM;}
"table"   {return TABLE;}
" "       {return SPACE;}
";"       {return EOQ;}
[0-9]*    {return NUM;}
[a-zA-Z0-9]* {return VAR;}
.         {return yytext[0];}
%%

int yywrap()
{
  return 1;
}
