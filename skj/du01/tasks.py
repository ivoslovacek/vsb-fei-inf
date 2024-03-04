import itertools


def fizzbuzz(num):
    """
    Return 'Fizz' if `num` is divisible by 3, 'Buzz' if `num` is divisible by 5, 'FizzBuzz' if `num` is divisible both by 3 and 5.
    If `num` isn't divisible neither by 3 nor by 5, return `num`.
    Example:
        fizzbuzz(3) # Fizz
        fizzbuzz(5) # Buzz
        fizzbuzz(15) # FizzBuzz
        fizzbuzz(8) # 8
    """
    result = "Fizz" if num % 3 == 0 else ""
    result += "Buzz" if num % 5 == 0 else ""
    if result == "":
        return num
    else:
        return result


def fibonacci(n):
    """
    Return the `n`-th Fibonacci number (counting from 0).
    Example:
        fibonacci(0) == 0
        fibonacci(1) == 1
        fibonacci(2) == 1
        fibonacci(3) == 2
        fibonacci(4) == 3
    """

    if n == 0:
        return 0

    if n == 1:
        return 1

    last = 0
    current = 1
    i = 2

    while i <= n:
        current += last
        last = current - last
        i += 1

    return current


def dot_product(a: list, b):
    """
    Calculate the dot product of `a` and `b`.
    Assume that `a` and `b` have same length.
    Hint:
        lookup `zip` function
    Example:
        dot_product([1, 2, 3], [0, 3, 4]) == 1*0 + 2*3 + 3*4 == 18
    """

    return sum([x * y for x, y in zip(a, b)])


def redact(data, chars):
    """
    Return `data` with all characters from `chars` replaced by the character 'x'.
    Characters are case sensitive.
    Example:
        redact("Hello world!", "lo")        # Hexxx wxrxd!
        redact("Secret message", "mse")     # Sxcrxt xxxxagx
    """

    return "".join(["x" if x in chars else x for x in data])


def count_words(data):
    """
    Return a dictionary that maps word -> number of occurences in `data`.
    Words are separated by spaces (' ').
    Characters are case sensitive.

    Hint:
        "hi there".split(" ") -> ["hi", "there"]

    Example:
        count_words('this car is my favourite what car is this')
        {
            'this': 2,
            'car': 2,
            'is': 2,
            'my': 1,
            'favourite': 1,
            'what': 1
        }
    """

    result = {}

    if data == "":
        return result

    for word in data.split(" "):
        if word in result:
            result[word] += 1
        else:
            result[word] = 1

    return result


def bonus_fizzbuzz(num):
    """
    Implement the `fizzbuzz` function.
    `if`, match-case and cycles are not allowed.
    """

    result = ("Fizz") * (num % 3 == 0) + ("Buzz") * (num % 5 == 0)
    return result or num


def bonus_utf8(cp):
    """
    Encode `cp` (a Unicode code point) into 1-4 UTF-8 bytes - you should know this from `Základy číslicových systémů (ZDS)`.
    Example:
        bonus_utf8(0x01) == [0x01]
        bonus_utf8(0x1F601) == [0xF0, 0x9F, 0x98, 0x81]
    """

    if cp < 0x007F:
        return bytes([cp])

    elif cp <= 0x7FF:
        result = []
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b11000000 | cp)
        return bytes(result)
    elif cp <= 0xFFFF:
        result = []
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b11100000 | cp)
        return bytes(result)
    else:
        result = []
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b10000000 | (cp & 0b00111111))
        cp >>= 6
        result.insert(0, 0b11110000 | cp)
        return bytes(result)
