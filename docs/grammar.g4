pipeline:
            command (PIPE command)+ AMP? EOF
        ;

command:
            string+
        ;

string: UQSTRING | SQSTRING;