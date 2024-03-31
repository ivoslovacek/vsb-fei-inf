import dataclasses
from typing import Callable, Generic, List, Optional, TypeVar


def cached(f):
    """
    Create a decorator that caches up to 3 function results, based on the same parameter values.

    When `f` is called with the same parameter values that are already in the cache, return the
    stored result associated with these parameter values. You can assume that `f` receives only
    positional arguments (you can ignore keyword arguments).

    When `f` is called with new parameter values, forget the oldest inserted result in the cache
    if the cache is already full.

    Example:
        @cached
        def fn(a, b):
            return a + b # imagine an expensive computation

        fn(1, 2) == 3 # computed
        fn(1, 2) == 3 # returned from cache, `a + b` is not executed
        fn(3, 4) == 7 # computed
        fn(3, 5) == 8 # computed
        fn(3, 6) == 9 # computed, (1, 2) was now forgotten
        fn(1, 2) == 3 # computed again, (3, 4) was now forgotten
    """
    cache = []
    result_cache = []

    def wrapper(*args):
        if args in cache:
            return result_cache[cache.index(args)]
        else:
            if len(cache) >= 3:
                cache.pop(0)
                result_cache.pop(0)

            result = f(*args)
            cache.append(args)
            result_cache.append(result)
            return result
    return wrapper


@cached
def fn(a, b):
    return a+b


T = TypeVar("T")


@dataclasses.dataclass
class ParseResult(Generic[T]):
    """
    Represents result of a parser invocation.
    If `value` is `None`, then the parsing was not successful.
    `rest` contains the rest of the input string if parsing was succesful.
    """
    value: Optional[T]
    rest: str

    @staticmethod
    def invalid(rest: str) -> "ParseResult":
        return ParseResult(value=None, rest=rest)

    def is_valid(self) -> bool:
        return self.value is not None


"""
Represents a parser: a function that takes a string as an input and returns a `ParseResult`.
"""
Parser = Callable[[str], ParseResult[T]]

"""
Below are functions that create new parsers.
They should serve as LEGO blocks that can be combined together to build more complicated parsers.
See tests for examples of usage.

Note that parsers are always applied to the beginning of the string:
```python
parser = parser_char("a")
parser("a")  # ParseResult(value="a", rest="")
parser("xa") # ParseResult(value=None, rest="xa")
```
"""


def parser_char(char: str) -> Parser[str]:
    """
    Return a parser that will parse a single character, `char`, from the beginning of the input
    string.

    Example:
        ```python
        parser_char("x")("x") => ParseResult(value="x", rest="")
        parser_char("x")("xa") => ParseResult(value="x", rest="a")
        parser_char("y")("xa") => ParseResult(value=None, rest="xa")
        ```
    """
    def fn(input: str):
        if input:
            if char == input[0]:
                str_list = [x for x in input]
                value = str_list.pop(0)
                rest = ''.join(str_list)
                return ParseResult(value=value, rest=rest)

        return ParseResult(value=None, rest=input)

    if len(char) != 1:
        raise ValueError
    else:
        return fn


def parser_repeat(parser: Parser[T]) -> Parser[List[T]]:
    """
    Return a parser that will invoke `parser` repeatedly, while it still matches something in the
    input.

    Example:
        ```python
        parser_a = parser_char("a")
        parser = parser_repeat(parser_a)
        parser("aaax") => ParseResult(value=["a", "a", "a"], rest="x")
        parser("xa") => ParseResult(value=[], rest="xa")
        ```
    """

    def fn(input: str):
        value_list = []

        current = parser(input)

        while current.value is not None:
            value_list.append(current.value)
            current = parser(current.rest)

        return ParseResult(value=value_list, rest=current.rest)

    return fn


def parser_seq(parsers: List[Parser]) -> Parser:
    """
    Create a parser that will apply the given `parsers` successively, one after the other.
    The result will be successful only if all parsers succeed.

    Example:
        ```python
        parser_a = parser_char("a")
        parser_b = parser_char("b")
        parser = parser_seq([parser_a, parser_b, parser_a])
        parser("abax") => ParseResult(value=["a", "b", "a"], rest="x")
        parser("ab") => ParseResult(value=None, rest="ab")
        ```
    """

    def fn(input: str):
        value = []
        rest = input

        for parser in parsers:
            current = parser(rest)
            if current.value is None:
                return ParseResult(value=None, rest=input)

            value.append(current.value)
            rest = current.rest

        return ParseResult(value=value, rest=rest)

    return fn


def parser_choice(parsers: List[Parser]) -> Parser:
    """
    Return a parser that will return the result of the first parser in `parsers` that matches something
    in the input.

    Example:
        ```python
        parser_a = parser_char("a")
        parser_b = parser_char("b")
        parser = parser_choice([parser_a, parser_b])
        parser("ax") => ParseResult(value="a", rest="x")
        parser("bx") => ParseResult(value="b", rest="x")
        parser("cx") => ParseResult(value=None, rest="cx")
        ```
    """

    def fn(input: str):
        for parser in parsers:
            current = parser(input)
            if current.value is not None:
                return ParseResult(value=current.value, rest=current.rest)

        return ParseResult(value=None, rest=input)

    return fn


R = TypeVar("R")


def parser_map(parser: Parser[R], map_fn: Callable[[R], Optional[T]]) -> Parser[T]:
    """
    Return a parser that will use `parser` to parse the input data, and if it is successful, it will
    apply `map_fn` to the parsed value.
    If `map_fn` returns `None`, then the parsing result will be invalid.

    Example:
        ```python
        parser_a = parser_char("a")
        parser = parser_map(parser_a, lambda x: x.upper())
        parser("ax") => ParseResult(value="A", rest="x")
        parser("bx") => ParseResult(value=None, rest="bx")

        parser = parser_map(parser_a, lambda x: None)
        parser("ax") => ParseResult(value=None, rest="ax")
        ```
    """

    def fn(input: str):
        parsed = parser(input)

        if parsed.value is None:
            return ParseResult(value=None, rest=input)

        mapped = map_fn(parsed.value)

        if mapped is not None:
            return ParseResult(value=mapped, rest=parsed.rest)
        else:
            return ParseResult(value=None, rest=input)

    return fn


def parser_matches(filter_fn: Callable[[str], bool]) -> Parser[str]:
    """
    Create a parser that will parse the first character from the input, if it is accepted by the
    given `filter_fn`.

    Example:
        ```python
        parser = parser_matches(lambda x: x in ("ab"))
        parser("ax") => ParseResult(value="a", rest="x")
        parser("bx") => ParseResult(value="b", rest="x")
        parser("cx") => ParseResult(value=None, rest="cx")
        parser("") => ParseResult(value=None, rest="")
        ```
    """
    def fn(input: str):
        if input:
            if filter_fn(input[0]):
                str_list = [x for x in input]
                value = str_list.pop(0)
                rest = ''.join(str_list)
                return ParseResult(value=value, rest=rest)

        return ParseResult(value=None, rest=input)

    return fn


# Use the functions above to implement the functions below.


def parser_string(string: str) -> Parser[str]:
    """
    Create a parser that will parse the given `string`.

    Example:
        ```python
        parser = parser_string("foo")
        parser("foox") => ParseResult(value="foo", rest="x")
        parser("fo") => ParseResult(value=None, rest="fo")
        ```
    """
    def fn(input: str):
        string_list = [x for x in string]

        value: str = ''
        rest: str = input

        for char in string_list:
            parsed = parser_matches(lambda x: x == char)(rest)
            if parsed.value is None:
                return ParseResult(value=None, rest=input)
            value += parsed.value
            rest = parsed.rest

        return ParseResult(value=value, rest=rest)

    return fn


def parser_int() -> Parser[int]:
    """
    Create a parser that will parse a non-negative integer (you don't have to deal with
    `-` at the beginning).

    Example:
        ```python
        parser = parser_int()
        parser("123x") => ParseResult(value=123, rest="x")
        parser("foo") => ParseResult(value=None, rest="foo")
        ```
    """

    def fn(input: str):
        if len(input) == 0:
            return ParseResult(value=None, rest=input)

        parser = parser_matches(lambda x: x.isdigit())
        current = parser(input)
        value = None if current.value is None else int(current.value)

        while current.value is not None:
            current = parser(current.rest)

            if current.value is not None:
                value *= 10
                value += int(current.value)

        return ParseResult(value=value, rest=current.rest)

    return fn
