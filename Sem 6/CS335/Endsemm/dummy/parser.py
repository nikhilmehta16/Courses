import ply.yacc as yacc
import sys
from lexer import tokens, lines

symbol_table = {}
emit_array = []

class Node:
    def __init__(self, name = '', type = '', var_list=[], value= '',code=''):
        self.name = name
        self.type = type
        self.var_list = var_list
        self.value = value
        self.code = code
        pass

def p_translation_unit(p):
    '''
    translation_unit : PROGRAM ID ';' VAR declaration_list BEGIN expression_list END '.'
    '''
    

def p_declaration_list(p):
    '''
    declaration_list : declaration_list declaration 
                        | declaration
    '''



def p_declaration(p):
    '''
    declaration : variable_list ':' type ';'
    '''
    for id in p[1].var_list:
        symbol_table[id] = {}
        symbol_table[id]['type'] = p[3].type
        print(f"\t{p[3].type} {id};")
    #print(symbol_table)

def p_variable_list(p):
    '''
    variable_list : variable_list ',' ID 
                    | ID
    '''
    if len(p) == 2:
        p[0] = Node(name = 'variable_list', var_list=[p[1]])
    else:
        p[0] = p[1]
        p[0].var_list.append(p[3])

def p_type(p):
    '''
    type : INTEGER 
            | REAL
    '''
    p[0] = Node(name = 'type', type=p[1])
    if p[1] == "INTEGER":
        p[0].type = "int"
    else:
        p[0].type = "float"

def p_expression_list(p):
    '''
    expression_list : expression_list expression 
                    | expression
    '''
    


def p_expression(p):
    '''
    expression : ID ASSIGN additive_expression ';' 
    '''
    if p[1] not in symbol_table.keys():
        print("COMPILATION ERROR: ID NOT DECLARED at line no ", p.lineno(1) - lines)
    print(f"\t{p[1]}={p[3].code};")

def p_additive_expression(p):
    '''
    additive_expression : multiplicative_expression '+' multiplicative_expression 
                | multiplicative_expression 
    '''
    if len(p) == 2:
        p[0] = Node(code=p[1].code)
    else:
        p[0] = p[1]
        p[0].code = p[0].code+"+" + p[3].code

def p_multiplicative_expression(p):
    '''
    multiplicative_expression : unary_expression '*' unary_expression 
                                | unary_expression
    '''
    if len(p) == 2:
        p[0] = Node(code=p[1].code)
    else:
        p[0] = p[1]
        p[0].code = p[0].code+"*" + p[3].code

def p_unary_expression(p):
    '''
    unary_expression : ID 
                        | NUMERIC
                        | FLOAT
    '''
    p[0] = Node(code=p[1])
    

def p_error(p):
    print("syntax error!")

print("int main(){")
parser = yacc.yacc()

fp = open(sys.argv[1], 'r')
data = fp.read()
# print("data", data)
result = parser.parse(data)
print("\treturn 0;")
print("}")