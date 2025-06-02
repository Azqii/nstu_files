from .dto import Token, TokenType, ParsedStringResult
from .exceptions import SyntaxException


class SyntaxAnalyzer:
    def __init__(self, tokens: list[Token]):
        self.tokens = tokens
        self.pos = 0

    def parse(self) -> ParsedStringResult:
        try:
            result = self._parse_s()
        except SyntaxException as e:
            if token := self._peek():
                error_text = f"Ошибка синтаксиса: {str(e)} у токена {token}."
            else:
                error_text = f"Ошибка синтаксиса: {str(e)} в конце строки."
            raise SyntaxError(error_text)
        return result

    def _peek(self) -> Token | None:
        if self.pos < len(self.tokens):
            return self.tokens[self.pos]
        return None

    def _match(self, expected_type: TokenType) -> Token | None:
        token = self._peek()
        if token and token.type is expected_type:
            self.pos += 1
            return token
        return None

    def _parse_s(self) -> ParsedStringResult:
        """<S> -> <Type> [ <Kind> ] '::' <VarsList> <End>"""
        type_ = self._parse_type()
        kind = self._parse_kind()

        if not self._match(TokenType.DOUBLE_COLON):
            raise SyntaxException("Ожидалось '::'")

        vars_list = self._parse_vars_list()

        if not self._match(TokenType.END):
            raise SyntaxException("Ожидались ';' или '\\n'")

        return ParsedStringResult(
            type=type_,
            kind=kind,
            vars_list=vars_list
        )

    def _parse_type(self) -> str:
        """<Type> -> 'integer' | 'complex'"""
        type_token = self._match(TokenType.TYPE)
        if not type_token:
            raise SyntaxException("Ожидалось ключевое слово типа: integer или complex")
        return type_token.value

    def _parse_kind(self) -> int | None:
        """<Kind> -> '(' <Number> | ( 'kind' '=' <Number> ) ')'"""
        if not self._match(TokenType.LBRACE):
            return None
        if self._match(TokenType.KIND) and not self._match(TokenType.EQUALS):
            raise SyntaxException("Ожидался символ '='")
        kind = self._parse_number()
        if not self._match(TokenType.RBRACE):
            raise SyntaxException("Ожидалась закрывающая скобка ')'")
        return kind

    def _parse_vars_list(self) -> list[str]:
        """<VarsList> -> <VarName> { ',' <VarName> }"""
        vars_list = [self._parse_var_name()]
        while self._match(TokenType.COMMA):
            vars_list.append(self._parse_var_name())
        return vars_list

    def _parse_var_name(self) -> str:
        """<VarName> -> <Character> { <Character> | <Digit> }"""
        var_token = self._match(TokenType.VAR_NAME)
        if not var_token:
            raise SyntaxException("Ожидалось имя переменной")
        return var_token.value

    def _parse_number(self) -> int:
        """<Number> -> <Digit> { <Digit> }"""
        number_token = self._match(TokenType.NUMBER)
        if not number_token:
            raise SyntaxException("Ожидалось число")
        return int(number_token.value)
