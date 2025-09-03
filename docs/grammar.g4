pipeline:
            command (PIPE command)+ AMP? EOF
        ;

command:
            string+
        ;

string: var_string | WORD | SQSTRING;

var_string: OUT_AS_VAL WORD;