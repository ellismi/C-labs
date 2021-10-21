%{
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int xz();
double Sqrt (double ytg);
void help();

  typedef struct Cimlob 
   {
    char *norem; short type;
    union {
         double bol;
         double (*ipir)();
         }y;
    struct Cimlob *kekt;
  } Cimlob;

Cimlob *symlist = 0;

static struct {
char *norem;
double gobl; } 
Const[]=
 {
   "RAD",57.2958,
   "E", 2.718281828459,
   "LNPI", 1.144729886,
   "PI", 3.1415926536,
   "LNT", 2.302585093,
   "LGPI", 0.497149873,
   "LGE", 0.434294482,
   "PI3", 31.006276680,
   "E2", 7.389056099,
    0,0
 };
 
static struct {
    char *norem;
   double (*func)(); } 
Funcs[]=
     {
      "ch", cosh,
      "th", tanh,
      "abs",fabs,
      "tan",tan,
      "sqrt",Sqrt,
      "ln", log,
      "sh", sinh,
      "cos",cos,
      "sin",sin,
	    "lg", log10,
	    "j0", j0,
	    "j1", j1,
	    "jn", jn,
	    "y0", y0,
	    "y1", y1,
	    "yn", yn,
      "fmax", fmax,
      "hypot", hypot,

       0,0
     };
%}

%union    {   
           double bol;
           Cimlob *cim;
          };

%token <cim> VAR FUNC UNDF 
%type  <bol> expr assign
%type  <bol> prog
%token <bol> NUM
%left  '*' '/'
%right '^'
%left  '+' '-'
%right '='
%left UNMIN

%%

prog: 
  '\n'             { printf("!\n"); }
| expr '\n'        { $$=$1; printf("=>%lf\n",$$);  }
| prog expr '\n'   { $$=$2; printf("->%lf\n",$$);  }
; 
assign: VAR '=' expr        {  $$ = $1->y.bol=$3; $1->type=VAR; }
;
expr:    NUM                {  $$ = $1; }
      |  VAR                {  $$ = $1->y.bol; }
      |  FUNC               {  $$ = ($1->y.ipir)(); }
      |  FUNC '(' expr ')'  {  $$ = (($1->y.ipir)($3)); }
      |  FUNC '(' expr',' expr ')'  { if ($3 - (int)$3 == 0.) ($$ = ($1->y.ipir)((int)($3-($3 - (int)$3)), $5));
                                      else ($$ = ($1->y.ipir)($3, $5)); }
      |  expr '+' expr      { $$ = $1+$3; }
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

Cimlob *install(char *qw, short qt, double qdd)
{
  Cimlob *pop;
   pop = (Cimlob *) malloc(sizeof(Cimlob));
   pop->norem = (char *)malloc(strlen(qw)+1);    
   strcpy(pop->norem,qw); 
   pop->type = qt; pop->y.bol=qdd; pop->kekt=symlist;
   symlist=pop; 
   return pop;
}

Cimlob *lookup(char *qw)
{
  Cimlob *pop;
  for (pop=symlist; pop!=(Cimlob *)0; pop=pop->kekt)
    if (strcmp(pop->norem,qw)==0) 
    { 
      return pop;
    }
    return 0;
}

Init()
{
  int popi; Cimlob *qw;
  
   for(popi=0; Const[popi].norem; popi++) 
   install(Const[popi].norem,VAR,Const[popi].gobl);
   for(popi=0; Funcs[popi].norem; popi++)
   {
    qw=install(Funcs[popi].norem,FUNC,0.0); qw->y.ipir=Funcs[popi].func;
   };
}

 xz()
{
  int iiiiic;
   Cimlob *qw; 
   char sbuf[100], *p=sbuf;
  while((iiiiic=getchar())==' ');
 if (iiiiic==EOF) return 0;
 if(isalpha(iiiiic))
 {
     do 
      { *p++=iiiiic; } 
     while (((iiiiic=getchar())!=EOF) && isalnum(iiiiic));
    ungetc(iiiiic,stdin); *p='\0';
    if(strcmp(sbuf,"exit") == 0)
    { 
      printf("Goodbye"); 
      exit(EXIT_SUCCESS);
    }
    if(strcmp(sbuf,"help") == 0) help();
    if ((qw=lookup(sbuf))==0) 
                 qw=install(sbuf,UNDF,0.0);
   weterfd.cim=qw;
   return ((qw->type==UNDF) ? VAR : qw->type);
 }
 if (iiiiic=='.' || isdigit(iiiiic))
    { 
      ungetc(iiiiic,stdin); scanf("%lf",(double *)&weterfd);
     return NUM;
   };
  return iiiiic;
}

double Sqrt(double ytg)
{
 if (ytg<0.0) { yyerror(" Sqrt from negative number. "); return (0.0); };
 return sqrt(ytg);
}

void help()
{
  Cimlob *qw;
  int popi;
  printf("Program use(+,-,*,/,^)\nProgram has constants: ");
  for(popi=0; Const[popi].norem; popi++)
  { 
    printf("%qw, ", Const[popi].norem);
  }
  printf("\nProgram has functions: ");
  for(popi=0; Funcs[popi].norem; popi++)
   {
    printf("%qw, ", Funcs[popi].norem);
   }
   printf("\nCreate your change\nExample: a = 0\na");
}

yyerror(char *qw)
 {
   printf("Error: %qw\n",qw);
 }

int main()
 {    
    Init();
    yyparse();
    return 0;
 }

