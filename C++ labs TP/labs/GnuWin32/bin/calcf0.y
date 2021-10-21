%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int yylex();
double Sqrt (double x);

  typedef struct Symbol 
   {
    char *name; short type;
    union {
         double val;
         double (*ptr)();
         }u;
    struct Symbol *next;
  } Symbol;

Symbol *symlist =0;

static struct {
char *name;
double cval; } Const[]=
 {
   "PI", 3.1415926536,
   "E", 2.718281828459,
   "RAD",57.2958,
   0,0
 };
static struct {
    char *name;
   double (*func)(); } 
Funcs[]=
     {
      "sin",sin,
      "cos",cos,
      "tan",tan,
      "sqrt",Sqrt,
      "abs",fabs,
       0,0
     };
%}

%union    {   
           double val;
           Symbol *sym;
          };

%token <val> NUM
%token <sym> VAR FUNC UNDF 
%type  <val> expr assign
%type  <val> prog
%right '='
%left  '+' '-'
%left  '*' '/'
%right '^'
%left UNMIN

%%

prog: 
  '\n'             { printf("!\n"); }
| expr '\n'        { $$=$1; printf("=>%lf\n",$$);  }
| prog expr '\n'   { $$=$2; printf("->%lf\n",$$);  }
; 
assign: VAR '=' expr        {  $$ = $1->u.val=$3; $1->type=VAR; }
;
expr:    NUM                {  $$ = $1; }
      |  VAR                { $$ = $1->u.val; }
      |  FUNC '(' expr ')'  {  $$ = (($1->u.ptr)($3)); }
      |   expr '+' expr     { $$ = $1+$3; }
      |  expr '-' expr      { $$ = $1 - $3; }
      |  expr '*' expr      { $$ = $1*$3; }
      |  expr '/' expr      { if ($3!=0) $$ = $1/$3; 
                              else { printf(" Zero divide\n"); $$=$1; }
                            }
      |  expr '^' expr      { $$ = pow($1,$3); }
      | '-' expr %prec UNMIN { $$ = -$2; }
      | assign
      | '(' expr ')'        { $$ = $2; }
      ;

%%

Symbol *install(char *s, short t, double d)
{
  Symbol *sp;
   sp = (Symbol *) malloc(sizeof(Symbol));
   sp->name = (char *)malloc(strlen(s)+1);    
   strcpy(sp->name,s); 
   sp->type = t; sp->u.val=d; sp->next=symlist;
   symlist=sp; 
   return sp;
}

Symbol *lookup(char *s)
{
  Symbol *sp;
  for (sp=symlist; sp!=(Symbol *)0; sp=sp->next)
    if (strcmp(sp->name,s)==0) 
    { 
      return sp;
    }
    return 0;
}

Init()
{
  int i; Symbol *s;
  
   for(i=0; Const[i].name; i++) 
   install(Const[i].name,VAR,Const[i].cval);
   for(i=0; Funcs[i].name; i++)
   {
    s=install(Funcs[i].name,FUNC,0.0); s->u.ptr=Funcs[i].func;
   };
}

 yylex()
{

  int c;
   Symbol *s; 
   char sbuf[100], *p=sbuf;
  while((c=getchar())==' ');
 if (c==EOF) return 0;
 if(isalpha(c))
 {
     do 
      { *p++=c; } 
     while (((c=getchar())!=EOF) && isalnum(c));
   ungetc(c,stdin); *p='\0';
    if ((s=lookup(sbuf))==0) 
                 s=install(sbuf,UNDF,0.0);
   yylval.sym=s;
   return ((s->type==UNDF) ? VAR : s->type);
 }
 if (c=='.' || isdigit(c))
    { 
      ungetc(c,stdin); scanf("%lf",(double *)&yylval);
     return NUM;
   };
  return c;
}

double Sqrt(double x)
{
 if (x<0.0) { yyerror(" Sqrt from negative number. "); return (0.0); };
 return sqrt(x);
}

yyerror(char *s)
 {
   printf("Error: %s\n",s);
 }

int main()
 {    Init();
      yyparse();
      return 0;
 }

