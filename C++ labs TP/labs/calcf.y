%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int yylex();
double Sqrt (double x);
void help();
double fact(double x);

  typedef struct Symbol 
   {
    char *name; short type;
    union {
         double val;
         double (*ptr)();
         }u;
    struct Symbol *next;
  } Symbol;

Symbol *symlist = 0;

static struct {
char *name;
double cval; } Const[]=
 {
   "PI", 3.1415926536,
   "E", 2.718281828459,
   "RAD",57.2958,
   "LNT", 2.302585093,
   "LNPI", 1.144729886,
   "LGPI", 0.497149873,
   "LGE", 0.434294482,
   "PI3", 31.006276680,
   "E2", 7.389056099,
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
      "sh", sinh,
      "ch", cosh,
      "th", tanh,
      "ln", log,
	    "lg", log10,
	    "j0", j0,
	    "j1", j1,
	    "jn", jn,
	    "y0", y0,
	    "y1", y1,
	    "yn", yn,
      "help", help,
      "fact", fact,
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
%right '!'
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
      |  VAR                {  $$ = $1->u.val; }
      |  FUNC               {  $$ = ($1->u.ptr)(); }
      |  FUNC '(' expr ')'  {  $$ = (($1->u.ptr)($3)); }
      |  FUNC '(' expr',' expr ')'  { if ($3 - (int)$3 == 0.) ($$ = ($1->u.ptr)((int)($3-($3 - (int)$3)), $5));
                                      else ($$ = ($1->u.ptr)($3, $5)); }
      |  expr '+' expr      { $$ = $1+$3; }
      |  expr '-' expr      { $$ = $1 - $3; }
      |  expr '*' expr      { $$ = $1*$3; }
      |  expr '/' expr      { if ($3!=0) $$ = $1/$3; 
                              else { printf(" Zero divide\n"); $$=$1; }
                            }
      |  expr '^' expr      { $$ = pow($1,$3); }
      | '-' expr %prec UNMIN { $$ = -$2; }
      |  expr '!'           { $$ = fact($1);}
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
    if(strcmp(sbuf,"exit") == 0)
    { 
      printf("Goodbye\n"); 
      exit(EXIT_SUCCESS);
    }
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

double fact(double x){
  if(x<0.0) { yyerror("Factorial from negative number. "); return (0.0);}
  if(x==0.0) return (1.0);
  if(x==1.0) return (1.0);
  double res = 1;
  for(int i = 2; i <= (int)x; i++){
    res = res * i;
  }
  return res;
}

void help()
{
  Symbol *s;
  int i;
  printf("Program use(+,-,*,/,^)\nProgram has constants: ");
  for(i=0; Const[i].name; i++)
  { 
    printf("%s, ", Const[i].name);
  }
  printf("\nProgram has functions: ");
  for(i=0; Funcs[i].name; i++)
   {
    printf("%s, ", Funcs[i].name);
   }
   printf("\nYou can create your own variables in the program\nExample: a = 0");
   printf("\n a");
   printf("\n");
}

yyerror(char *s)
 {
   printf("Error: %s\n",s);
 }

int main()
 {    
    Init();
    yyparse();
    return 0;
 }

