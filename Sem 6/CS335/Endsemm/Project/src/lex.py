import ply.lex as lex
from ply.lex import TOKEN
from tabulate import tabulate
import sys

isError = False


def error_func(msg, row, column):
    print(f'Error found in line number {row}, coumn number {column}: {msg}')
    global isError
    isError = True


def find_column(input, token):
    line_start_pos = input.rfind('\n', 0, token.lexpos) + 1
    return (token.lexpos - line_start_pos) + 1


reserved_keywords = {
    'fun': 'FUN',
    'showTiles': 'SHOWTILES',
    'rotate': 'ROTATE',
    'concat': 'CONCAT',
    'return': 'RETURN',
    
}

tokens = list(reserved_keywords.values()) + [
    'ID',            # identifier
    # 'WS',           # denotes whitespace

    'CHAR_CONST',
    # 'INT_CONST',
    'STRING_CONST',

]



literals = [';', ',',  '=', '(', ')','{','}']

letter = r'([a-zA-Z])'









string_const = r'(\"(\\.|[^\\"])*\")'


@TOKEN(string_const)
def t_STRING_CONST(t):
    t.type = 'STRING_CONST'
    return t




def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    pass


def t_ID(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved_keywords.get(t.value, 'ID')

    if t.type == 'ID':
        contents = {"line_num": t.lineno}
        t.value = {"lexeme": t.value, "attributes": contents}
    return t


t_ignore = ' \t'


def t_error(t):

    msg = "Illegal token found"
    error_func(msg, t.lineno, find_column(lexer.lexdata, t))


lexer = lex.lex()

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print("Please provide a file name")
        sys.exit(1)

    try:
        file = open(sys.argv[1], 'r')
    except:
        print("File not found")
        sys.exit(1)

    data = file.read()

    lexer.input(data)

    table = []
    for token in lexer:
        row = []
        row = [token.type, token.value, token.lineno, find_column(data, token)]
        table.append(row)

    if(not isError):
        print(tabulate(table, headers=['Token', 'Lexeme', 'Line', 'Column']))
