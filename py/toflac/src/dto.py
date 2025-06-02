from enum import Enum
from dataclasses import dataclass


class TokenType(Enum):
    TYPE = "TYPE"
    LBRACE = "LBRACE"
    RBRACE = "RBRACE"
    KIND = "KIND"
    EQUALS = "EQUALS"
    NUMBER = "NUMBER"
    DOUBLE_COLON = "DOUBLE_COLON"
    VAR_NAME = "VARIABLE_NAME"
    COMMA = "COMMA"
    END = "END"
    WHITESPACE = "WHITESPACE"
    MISMATCH = "MISMATCH"


@dataclass
class Token:
    type: TokenType
    value: str


@dataclass
class ParsedStringResult:
    type: str
    kind: int | None
    vars_list: list[str]
