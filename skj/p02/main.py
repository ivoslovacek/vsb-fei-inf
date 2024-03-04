class Dog:
    def __init__(self, name) -> None:
        self.name = name

    def make_sound(self) -> str:
        return f"Bark: {self.name}"


class Cat:
    def __init__(self, name) -> None:
        self.name = name

    def make_sound(self) -> str:
        return f"Meow: {self.name}"


animals = [Dog("Lassie"), Cat("Mikes"), Dog("Goro")]

for animal in animals:
    print(animal.make_sound())


class Document:
    no_of_documents = 0
    total_length = 0

    def __init__(self, content):
        self._content = content
        Document.no_of_documents += 1
        Document.total_length += len(self._content)

    @property
    def content(self):
        return self._content

    @content.setter
    def content(self, content):
        Document.total_length -= len(self._content)
        self._content = content
        Document.total_length += len(self._content)

    @staticmethod
    def average_length():
        return Document.total_length / Document.no_of_documents

    def __str__(self):
        return f'Document: {self.content}'


d1 = Document('Text')
d2 = Document('Another text')
print(Document.no_of_documents)
print(Document.average_length())
print(d2)
