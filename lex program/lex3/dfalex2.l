%{

}%

%s B C D DEAD

%%
<INITIAL>a BEGIN B;
<INITIAL>b BEGIN INITIAL;
<INITIAL>c BEGIN INITIAL;
<INITIAL>[^abc\n]* BEGIN DEAD;
<INITIAL>\n BEGIN INITIAL; {printf("Not accepted");}

<B>a BEGIN B;
<B>b BEGIN C;
<B>c BEGIN INITIAL;
<B>[^abc\n]* BEGIN DEAD;
<B>\n BEGIN INITIAL; {printf("Not accepted");}

<C>a BEGIN B;
<C>b BEGIN INITIAL;
<C>c BEGIN D;
<C>[^abc\n]* BEGIN DEAD;
<C>\n BEGIN INITIAL; {printf("Not accepted");}

<D>a BEGIN B;
<D>b BEGIN INITIAL;
<D>c BEGIN INITIAL;
<D>[^abc\n]* BEGIN DEAD;
<D>\n BEGIN INITIAL; {printf("Accepted");}

<DEAD>[^\n] BEGIN DEAD; 
<DEAD>\n BEGIN INITIAL; {printf("Invalid\n");} 

%%

int main(){
    printf("Enter string: ");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}