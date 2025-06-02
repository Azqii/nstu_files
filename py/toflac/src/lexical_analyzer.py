import re

from .dto import TokenType, Token
from .exceptions import TokenMismatchException


class LexicalAnalyzer:
    def __init__(self, text: str):
        self.text = text

        # Регулярные выражения для лексем
        self.token_specs = [
            (TokenType.TYPE.value, r"integer|INTEGER|complex|COMPLEX"),
            (TokenType.LBRACE.value, r"\("),
            (TokenType.RBRACE.value, r"\)"),
            (TokenType.KIND.value, r"kind|KIND"),
            (TokenType.EQUALS.value, r"="),
            (TokenType.NUMBER.value, r"\d+"),
            (TokenType.DOUBLE_COLON.value, r"::"),
            (TokenType.VAR_NAME.value, r"[a-zA-Z][a-zA-Z0-9]*"),
            (TokenType.COMMA.value, r","),
            (TokenType.END.value, r";|\n"),
            (TokenType.WHITESPACE.value, r"[ \t]+"),
            (TokenType.MISMATCH.value, r"."),
        ]
        self.token_regex = '|'.join(f'(?P<{group_name}>{value})' for group_name, value in self.token_specs)

    def tokenize(self) -> list[Token]:
        tokens = []
        for match in re.finditer(self.token_regex, self.text):
            group_name = match.lastgroup
            value = match.group()
            if group_name == TokenType.WHITESPACE.value:
                continue
            elif group_name == TokenType.MISMATCH.value:
                raise TokenMismatchException(f"Неопознанный токен: {value} на позиции {match.start()}")
            tokens.append(Token(type=TokenType(group_name), value=value))
        return tokens
