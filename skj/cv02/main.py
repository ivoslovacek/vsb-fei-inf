def envelope(string):
    """
    Returns input string with added leading and closing '!' character.

    Example:
      "Hello" -> "!Hello!"
    """
    return f"!{string}!"


def use_envelope(lst):
    """
    Returns a list that contains strings that are enveloped using '!' character.
    Use envelope function to decouple the problem.
    """
    return list(map(envelope, lst))


def super_print(*arg):
    """
    Prints string of joined strings from *arg separated by whitespace.
    On the top and bottom of the string, `-` character is print in the same length
    as the output string.

    Example:
      super_print("Hello", "World!")

      ------------
      Hello World!
      ------------
    """
    str = " ".join(arg)
    idk = "".join(["-" for _ in str])

    print("\n".join([idk, str, idk]))


print(envelope("Hello"))
print(use_envelope(["Hello", "World"]))
super_print("Hello", "World!")
