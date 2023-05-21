grammar SysY;

import CommonLex;

compUnit : (decl | funcDef)* EOF;

decl : constDecl | varDecl;

constDecl : 'const' bType constDef (',' constDef)* ';' ;

bType: 'int' | 'float';

constDef : Identifier ('[' constExp ']')* '=' constInitVal;

constInitVal
    : constExp # scalarConstInitVal
    | '{' (constInitVal (',' constInitVal)* )? '}' # listConstInitVal
    ;

varDecl : bType varDef (',' varDef)* ';';

varDef
    : Identifier ('[' constExp ']')* # unInitVarDef
    | Identifier ('[' constExp ']')* '=' initVal # initVarDef
    ;

initVal
    : exp # scalarInitVal
    | '{' (initVal (',' initVal)* )? '}' # listInitVal
    ;

funcDef : funcType Identifier '(' (funcFparamList)? ')' block;

funcType : 'void' | 'int' | 'float' ;

funcFparamList : funcFparam (',' funcFparam)*;

funcFparam : bType Identifier ('[' ']' ('[' constExp ']')* )?;

block : '{' (blockItem)* '}';

blockItem : decl | stmt;

stmt
    : lVal '=' exp ';' # assignmentStmt
    | (exp)? ';' # expStmt
    | block # blockStmt
    | 'if' '(' cond ')' stmt # ifStmt
    | 'if' '(' cond ')' stmt 'else' stmt # ifElseStmt
    | 'while' '(' cond ')' stmt # whileStmt
    | 'break' ';' # breakStmt
    | 'continue' ';' # continueStmt
    | 'return' (exp)? ';' # returnStmt
    ;

exp : addExp;

cond : lOrExp;

lVal : Identifier ('[' exp ']')*;

rVal : Identifier ('[' exp ']')*;

primExp
    : '(' exp ')' # primParenExp
    | rVal # primRvalExp
    | number # primConstExp
    ;

number : IntLiteral | FloatLiteral;

unaryExp
    : primExp # unaryToPrimExp
    | Identifier '(' (funcRparamList)? ')' # unaryFuncCallExp
    | unaryOp unaryExp # unaryOpExp
    ;

unaryOp : '+' | '-' | '!';

funcRparamList : funcRparam (',' funcRparam)*;

funcRparam
    : exp # expAsRparam
    | STRING # stringAsRparam
    ;

mulExp
    : unaryExp # mulToUnaryExp
    | mulExp ('*' | '/' | '%') unaryExp # mulTwoExp
    ;

addExp
    : mulExp # addToMulExp
    | addExp ('+' | '-') mulExp # addTwoExp
    ;

relExp
    : addExp # relToAddExp
    | relExp ('<' | '>' | '<=' | '>=') addExp # relTwoExp
    ;

eqExp
    : relExp # eqToRelExp
    | eqExp ('==' | '!=') relExp # eqTwoExp
    ;

lAndExp
    : eqExp # lAndToEqExp
    | lAndExp '&&' eqExp # lAndTwoExp
    ;

lOrExp
    : lAndExp # lOrToLandExp
    | lOrExp '||' lAndExp # lOrTwoExp
    ;

constExp
    : addExp
    ;