import json


class TrackDifficulty:
    def to_string(difficulty: int) -> str:
        if difficulty < 1 or difficulty > 5:
            return ""

        int_to_str = {
            1: "Easy",
            2: "Moderate",
            3: "Moderately Strenous",
            4: "Strenous",
            5: "Very Strenuos"
        }

        return int_to_str.get(difficulty)


class TrailData:
    def __init__(self, link: str, distance: float, ascent: int,
                 descent: int, difficulty: int, start: str,
                 end: str, rating: float = 0) -> None:
        self.link = link
        self.distance = distance
        self.ascent = ascent
        self.descent = descent
        self.difficulty = TrackDifficulty.to_string(difficulty)
        self.start = start
        self.end = end
        self.rating = min(rating, 5.0)


class AppData:
    def __init__(self):
        self.trails = self.load()

    def save(self):
        with open("traildata.json", "w") as file:
            json.dump([x.__dict__ for x in self.trails], file, indent=4)

    def load(self):
        json_data = []

        try:
            with open("traildata.json", "r") as file:
                json_data = json.load(file)
            return [TrailData(**x) for x in json_data]
        except FileNotFoundError:
            return []
