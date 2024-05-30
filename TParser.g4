parser grammar TParser;
options { tokenVocab=TLexer; }

input
    : (validStatements (NL?))+ EOF
    ;

validStatements: 
    rUsrVar EQ oPlus #SetValue
    | PRINT oPlus #Print
    | CALCULATE oPlus int int int #Calculate
    ;

rUsrVar:
    USERVAR;

oPlus
    : oPlus PLUS  oMult # PlusOp
    | oPlus MINUS oMult # BinaryMinusOp
    | oMult # ToOMul
    ;

oMult
    : oMult MULT leaf # MultOp
    | leaf # toLeaf
    ;

leaf
    : MINUS oPlus # UnaryMinusOp
    | POPEN oPlus PCLOSE # ParenthesisOp
    | mon #Monom
    | rUsrVar #GetValue
    ;

mon
    : int(pow)+ #FullMonom
    | int #MonomZeroPower
    | (pow)+ #MonomWithouCoefficient
    ;

rVar: VAR;

pow
    : rVar POW int 
    ;

int: INT #ConvertToInt;