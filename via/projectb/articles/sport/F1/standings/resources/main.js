var jsonData = null;
var currentImage = 0;

window.addEventListener("load", () => {
    loadStandings();
});

async function loadStandings() {
    var JSONData = null;

    await fetch("resources/standings.json")
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            data.Drivers = sortByProperties(data.Drivers, "Points", "Podiums");
            data.Constructors = sortByProperties(data.Constructors, "Points", "Podiums");
            JSONData = data;
        })
        .catch(error => {
            console.error('Error loading JSON:', error);
        });

    console.log(JSONData);

    const drivers = document.querySelector(".drivers");
    const constructors = document.querySelector(".constructors");

    const driverTemplate = drivers.querySelector(".hidden");

    for (let i = 0; i < JSONData.Drivers.length; i++) {
        const newRow = driverTemplate.cloneNode(true);
        newRow.classList.toggle("hidden");

        newRow.children[0].innerHTML = i + 1;
        newRow.children[1].innerHTML = `${JSONData.Drivers[i].Country} ${JSONData.Drivers[i].Driver}`;
        newRow.children[2].innerHTML = `${JSONData.Drivers[i].Team}`;
        newRow.children[3].innerHTML = `${JSONData.Drivers[i].Wins}`;
        newRow.children[4].innerHTML = `${JSONData.Drivers[i].Points}`;

        driverTemplate.parentNode.appendChild(newRow);
    }

    const constructorTemplate = constructors.querySelector(".hidden");
    for (let i = 0; i < JSONData.Constructors.length; i++) {
        const newRow = constructorTemplate.cloneNode(true);
        newRow.classList.toggle("hidden");

        newRow.children[0].innerHTML = i + 1;
        newRow.children[1].innerHTML = `${JSONData.Constructors[i].Country} ${JSONData.Constructors[i].Team}`;
        newRow.children[2].innerHTML = `${JSONData.Constructors[i].Wins}`;
        newRow.children[3].innerHTML = `${JSONData.Constructors[i].Points}`;

        constructorTemplate.parentNode.appendChild(newRow);
    }

    const driverBtn = document.getElementById("drivers");
    const constructBtn = document.getElementById("constructors");

    driverBtn.addEventListener("click", () => {
        driverBtn.classList.add("selected");
        constructBtn.classList.remove("selected");

        drivers.classList.remove("hidden");
        constructors.classList.add("hidden");
    });

    constructBtn.addEventListener("click", () => {
        constructBtn.classList.add("selected");
        driverBtn.classList.remove("selected");

        constructors.classList.remove("hidden");
        drivers.classList.add("hidden");
    });
}

const sortByProperties = (array, ...props) => {
    return array.sort((a, b) => {
        for (let prop of props) {
            if (a[prop] !== b[prop]) {
                return b[prop] - a[prop];
            }
        }
        return 0;
    });
};
