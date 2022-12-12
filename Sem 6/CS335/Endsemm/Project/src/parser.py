import ply.yacc as yacc
from lex import tokens
import sys



def p_statement(p):
    '''statement : function_declaration
                 | function_call
                 | show_tiles_statement
                 | rotate_statement
                 | concat_statement
                 | return_statement
                 | assignment_statement
    '''

def p_primary_expression(p):
    '''primary_expression : ID
                          | '(' expression ')'
    '''

def p_parameter_list(p):
    '''parameter_list : parameter
                      | parameter_list ',' parameter
    '''

def p_statements(p):
    '''statements : statement
                  | statements statement
    '''

def p_block(p):
    '''block : '{' statements '}'
    '''

def p_argument(p):
    '''argument : string_const
    '''

def p_argument_list(p):
    '''argument_list : argument
                     | argument_list ',' argument
    '''

def p_function_declaration(p):
    '''function_declaration : FUN ID '(' parameter_list ')' block
    '''

def p_function_call(p):
    '''function_call : ID '(' argument_list ')'
    '''

def p_single_argument(p):
    '''single_argument : argument
    '''

def p_two_arguments(p):
    '''
    two_arguments : argument ',' argument
    '''

def p_show_tiles_statement(p):
    '''show_tiles_statement : SHOWTILES '(' single_argument ')'
    '''

def p_rotate_statement(p):
    '''rotate_statement : ROTATE '(' two_arguments ')'
    '''

def p_concat_statement(p):
    '''concat_statement : CONCAT '(' two_arguments ')'
    '''

def p_return_statement(p):
    '''return_statement : RETURN '(' argument ')'
    '''

def p_assignment_statement(p):
    '''assignment_statement : ID '=' argument
    '''




isError = False

parser = yacc.yacc(start='translation_unit', outputdir="./tmp")

if "__main__" == __name__:
    if len(sys.argv) == 1:
        print("Please provide a file name")
        sys.exit(1)

    try:
        file = open(sys.argv[1], 'r')
    except:
        print("File not found")
        sys.exit(1)

    data = file.read()
    result = parser.parse(data)
