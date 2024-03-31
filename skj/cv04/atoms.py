import playground
import random


class Atom:
    count = 0

    def __init__(self, x, y, rad, color):
        """
        Inicializator třídy Atom
        :param x: souřadnice X
        :param y: soouřadnice Y
        :param rad: poloměr
        :param color: barva
        """
        Atom.count += 1
        self.x = x
        self.y = y
        self.rad = rad
        self.color = color
        self.y_dir: float = random.randrange(-5, 5)
        self.x_dir: float = random.randrange(-5, 5)

        self.id = Atom.count

        while (self.x_dir == 0 or self.y_dir == 0):
            self.y_dir = random.randrange(-5, 5)
            self.x_dir = random.randrange(-5, 5)

    def to_tuple(self):
        """Vrátí n-tici hodnot 
        příklad: x = 10, y = 12, rad = 15, color = 'green' -> (10,12,15,'green')
        """
        return (self.x, self.y, self.rad, self.color)

    def move(self, width, height):
        def bounce_back():
            if (self.x - self.rad < 0):
                self.x = self.rad
                self.x_dir *= -1

            if (self.x + self.rad > width):
                self.x = width - self.rad
                self.x_dir *= -1

            if (self.y - self.rad < 0):
                self.y = self.rad
                self.y_dir *= -1

            if (self.y + self.rad > height):
                self.y = height - self.rad
                self.y_dir *= -1

        def bounce_opposite():
            if (self.x - self.rad < 0):
                self.x = self.rad
                self.x_dir *= -1
                self.y_dir *= -1

            if (self.x + self.rad > width):
                self.x = width - self.rad
                self.x_dir *= -1
                self.y_dir *= -1

            if (self.y - self.rad < 0):
                self.y = self.rad
                self.y_dir *= -1

            if (self.y + self.rad > height):
                self.y = height - self.rad
                self.y_dir *= -1

        self.x += self.x_dir
        self.y += self.y_dir

        if self.id % 2 == 0:
            bounce_back()
        else:
            bounce_opposite()


class FallDownAtom(Atom):
    def __init__(self, x, y, rad, color):
        super().__init__(x, y, rad, color)
        self.g = 3
        self.damping = 0.8

    def move(self, width, height):
        def bounce_damped():
            if (self.x - self.rad < 0):
                self.x = self.rad
                self.x_dir *= -1

            if (self.x + self.rad > width):
                self.x = width - self.rad
                self.x_dir *= -1

            if (self.y - self.rad < 0):
                self.y = self.rad
                self.y_dir *= -1

            if (self.y + self.rad > height):
                self.y = height - self.rad
                self.y_dir *= -1
                self.y_dir *= self.damping
                self.x_dir *= self.damping

        self.x += self.x_dir
        self.y_dir += self.g
        self.y += self.y_dir
        bounce_damped()


class ExampleWorld(object):

    def __init__(self, size_x, size_y, count):
        self.width = size_x
        self.height = size_y
        # self.colors = [attr for attr in dir(playground.Colors) if not callable(
        #     getattr(playground.Colors, attr)) and not attr.startswith("__")]
        self.atoms = [self.random_atom() for _ in range(0, count)]

    def random_atom(self):
        radius = random.randrange(1, 50)
        x = random.randrange(radius, self.width - radius)
        y = random.randrange(radius, self.height - radius)
        # color = random.choice(self.color)
        color = random.choice(['blue', 'red', 'green', 'yellow'])
        # return Atom(x, y, radius, color)
        return FallDownAtom(x, y, radius, color)

    def tick(self):
        """This method is called by playground. Sends a tuple of atoms to rendering engine.

        :param size_x: world size x dimension
        :param size_y: world size y dimension
        :return: tuple of atom objects, each containing (x, y, radius) coordinates 
        """

        for atom in self.atoms:
            atom.move(self.width, self.height)

        return tuple({x.to_tuple() for x in self.atoms})


if __name__ == '__main__':
    size_x, size_y = 700, 400

    world = ExampleWorld(size_x, size_y, 10)
    playground.run((size_x, size_y), world)
