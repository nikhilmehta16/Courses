import ply.lex as lex
import sys
from texttable import Texttable

RESERVED = {
    'program' : 'PROGRAM',
    'var' : 'VAR',
    'begin' : 'BEGIN',
    'function' : 'FUNCTION',
    'integer' : 'INTEGER',
    'real' : 'REAL',
    'end' : 'END'
}

tokens = list(RESERVED.values()) + ['ID','FLOAT','NUMERIC', 'ASSIGN']

literals = [':',';','+','-','*','/','.',',']

t_ignore = ' \t'

t_ASSIGN = r':='

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9!@#$]*'
    t.type = RESERVED.get(t.value.lower(), 'ID')
    return t

def t_FLOAT(t):
    r'[+-]?(\d+(\.\d*)?|\.\d+)([eE][+-]?\d+)?'
    return t

def t_NUMERIC(t):
    r'[0-9]+'
    return t

def t_newline(t):
    r'\n+'
    global lines
    t.lexer.lineno += len(t.value)
    lines += len(t.value)

def t_SINGLE_LINE_COMMENT(t):
    r'\{.*\}'
    global lines
    t.lexer.lineno += t.value.count('\n')
    lines += t.value.count('\n')

def t_MULTIPLE_LINE_COMMENT(t):
    r'(\(\*(.|\n)*?\*\))'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


def t_eof(t):
    return None

def find_column(data, token):
    line_start = data.rfind('\n', 0, token.lexpos) + 1
    return (token.lexpos - line_start) + 1



fp = open(sys.argv[1], 'r')
lines = 0
data = fp.read()
lexer = lex.lex()
lexer.input(data)

t = Texttable()
t.set_cols_dtype(["t", "t", "t", "t"])

output_list = list()
output_list.append(["Token","Lexeme","Line#","Column#"])

while True:
    tok = lexer.token()
    if not tok: 
        break
    output_list.append([tok.type, tok.value, tok.lineno, find_column(data, tok)])

t.add_rows(output_list)
print(t.draw())