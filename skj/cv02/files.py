def read_file(filename):
    """
    Returns content of a file as a string.

    Uses classic file access.
    """

    f = None
    lines = "Unable to open a file: {0}".format(filename)
    try:
        f = open(filename, "r")
        lines = f.readlines()
        f.close()
    except FileNotFoundError:
        print(lines)
        lines = []
    finally:
        return lines


def read_file_using_with(filename):
    """
    Returns content of a file as a string.

    Uses with statement to open a file.
    """

    lines = "Unable to open a file: {0}".format(filename)
    try:
        with open(filename, "r") as file:
            lines = file.readlines()
        pass
    except FileNotFoundError:
        print(lines)
        return []
    finally:
        return lines


def split_line(line):
    slices = line.split(":")
    return (slices[0], slices[1])


def filter_cities(filename, **kw):
    """
    Returns a list of cities that match their population specified by restrictions.
    In **kw it will be possible to set an argument:
     'gt': only cities with a population greater than the value of the argument
     'lt': only cities with a population less than the value of the argument
    It is possible to enter none, one or both parameters at once.
    If no parameter is specified, an empty list is returned.
    Use list comprehension for filtering.
    Use so-called "unpacking" to load data.

    Reimplement the function to return a generator.
    """

    cities = read_file(filename)
    parsed_cities = dict(map(split_line, cities))
    filtered = []
    if "gt" in kw:
        filtered = [
            f"{y}:{x}"
            for y, x in parsed_cities.items()
            if int(x) > int(kw.get("gt") or 0)
        ]

    filtered = []
    if "lt" in kw:
        filtered = [
            f"{y}:{x}"
            for y, x in parsed_cities.items()
            if int(x) < int(kw.get("lt") or 0)
        ]

    return filtered


def main():
    """
    Main function.
    This function is run at the startup of a script thanks to the cryptic if statement below.
    """

    # file reading
    filename = "cities.txt"
    content = read_file(filename)
    print("{} file content is: {}".format(filename, content))

    content = read_file_using_with(filename)
    print("{} file content using with statement is: {}".format(filename, content))

    # filtering
    print(filter_cities(filename, gt=500000))
    print(filter_cities(filename, lt=300000))
    print(filter_cities(filename, lt=300000, gt=500000))


if __name__ == "__main__":
    main()
