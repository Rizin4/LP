%{
    int c = 0;
    void printToken(const char* tokenType) {
        printf("%s => %s\n", yytext, tokenType);
    }
%}

directive #.*
keyword int|float|char|double|while|for|do|if|break|continue|void|switch|case|long|struct|const|typedef|return|else|goto|union
identifier [a-zA-Z][a-zA-Z0-9]*
invalidtokens [0-9]+[a-zA-Z]+
separator [;,(){}\[\]]
string \"[^\"]*\"
number [0-9]+
operator \|\||\&\&|\+|\-|\*|\/|\%|\=|\=\=|\!\=|\<|\<=|\>|>=|\&
multiLine_comments "/*"([^*]|(\*+[^*/]))*\*+"/"  
singleLine_coments "//".* 
space [ \t\n]

%%

{directive} { printToken("preprocessor directive"); }
{keyword} { printToken("keyword"); }
{separator} { printToken("separator"); }
{identifier} { printToken("identifier"); c++; }
{invalidtokens} { printToken("invalid token"); }
{string} { printToken("string"); }
{number} { printToken("number"); }
{operator} { printToken("operator"); }
{multiLine_comments} { /* Ignore multiline comments */ }
{singleLine_coments} { /* Ignore single-line comments */ }
{space} { /* Ignore spaces and tabs */ }

%%

int main() {
    FILE* file;
    file = fopen("in.c", "r");
    if (!file) {
        printf("Unable to open file");
        exit(0);
    }
    yyin = file;
    yylex();
    printf("Number of identifiers: %d\n", c);
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
