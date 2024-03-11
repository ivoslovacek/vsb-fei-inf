def is_palindrome(data):
    """
    Returns True if `data` is a palindrome and False otherwise.
    Hint:
        slicing is your friend, use it
    Example:
        is_palindrome('aba') == True
        is_palindrome('abc') == False
    """

    if data == '':
        return True

    data_list = [x for x in data]

    for (a, b) in zip(data_list, reversed(data_list)):
        if a != b:
            return False

    return True


def lex_compare(a, b):
    """
    Lexicographically compare `a` with `b` and return the smaller string.
    Implement the comparison yourself, do not use the `<` operator for comparing strings: )

    Example:
        lex_compare('a', 'b') == 'a'
        lex_compare('ahoj', 'buvol') == 'ahoj'
        lex_compare('ahoj', 'ahojky') == 'ahoj'
        lex_compare('dum', 'automobil') == 'automobil'
    """

    for (x, y) in zip(a, b):
        if x < y:
            return a
        elif y < x:
            return b

    if len(a) < len(b) or len(a) == len(b):
        return a
    else:
        return b


def count_successive(string):
    """
    Go through the string and for each character, count how many times it appears in succession.
    Store the character and the count in a tuple and return a list of such tuples.

    Example:
          count_successive("aaabbcccc") == [("a", 3), ("b", 2), ("c", 4)]
          count_successive("aba") == [("a", 1), ("b", 1), ("a", 1)]
    """

    if not string:
        return []

    result = []
    current = string[0]
    count = 1

    for char in string[1:]:

        if char == current:
            count += 1
        else:
            result.append((current, count))
            current = char
            count = 1

    result.append((current, count))

    return result


def find_positions(items):
    """
    Go through the input list of items and collect indices of each individual item.
    Return a dictionary where the key will be an item and its value will be a list of indices
    where the item was found.

    Example:
        find_positions(["hello", 1, 1, 2, "hello", 2]) == {
            2: [3, 5],
            "hello": [0, 4],
            1: [1, 2]
        }
    """

    result = {}

    for i in range(0, len(items)):
        if items[i] in result.keys():
            tmp: list = result[items[i]]
            tmp.append(i)
        else:
            result[items[i]] = [i]

    return result


def invert_dictionary(dictionary):
    """
    Invert the input dictionary. Turn keys into values and vice-versa.
    If more values would belong to the same key, return None.

    Example:
        invert_dictionary({1: 2, 3: 4}) == {2: 1, 4: 3}
        invert_dictionary({1: 2, 3: 2}) is None
    """

    new_dict = {}

    for (key, value) in dictionary.items():
        if value in new_dict.keys():
            return None

        new_dict[value] = key

    return new_dict
