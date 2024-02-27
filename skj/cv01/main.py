# print("Hello world!")
#
# my_list = [1, 2, 3]
#
# if 1 in my_list:
#     print('is in the list')
# else:
#     print('is not in the list')
#
# for i in range(10):
#     print(i)


def add(a, b):
    """Adds parameters."""
    return a + b


def what_number(number) -> str:
    """Returns string positive/zero/negative specifying
    value of the number."""

    if number > 0:
        return f"{number} is positive"
    elif number < 0:
        return f"{number} is negative"
    else:
        return f"{number} is zero"


def sum_of_numbers(numbers) -> int:
    """Returns sum of the numbers in the list."""
    i: int = 0
    for num in numbers:
        i += num

    return i


def ship_name(fleet, designated_no) -> str:
    """Return ship's name for specified designated number
    from the fleet."""
    return fleet[designated_no]


def how_many_5(numbers) -> int:
    """Returns number of numbers greater than 5."""
    i: int = 0

    for num in numbers:
        if num > 5:
            i += 1

    return i


def gen_list_gt(lst, no) -> []:
    """Returns list with numbers greater than no."""
    # syntax: [ item for item in lst if_condition ]
    new_list: [] = []

    for item in lst:
        if item > no:
            new_list.append(item)

    return new_list


def add_numbers(x: int, y: int) -> int:
    print(f"Vlozena cisla {x} a {y}")
    return x + y


# x: int = int(input())
# y: int = int(input())
#
# print(f"Vysledek: {add_numbers(x,y)}")

n = 5
print("Number", n, "is:", what_number(n))

lst = [1, 2, 3, 6, 7, 8]
print("Sum is:", sum_of_numbers(lst))

fleet = {"BS62": "Pegasus", "BS75": "Galactica", 36: "Valkirie"}
designated_no = "BS62"
print("We've got {} in the fleet".format(ship_name(fleet, designated_no)))

lst = [1, 2, 5, 6, 7, 10, 12, 40, 3]
print("There are {} numbers greater than 5".format(how_many_5(lst)))

lst = [1, 2, 3, 4, 5, 6, 7, 8, 9]
no = 5
print("List with numbers > {}: {}".format(no, gen_list_gt(lst, no)))
