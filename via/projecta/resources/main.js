var map;

window.addEventListener("load", () => {
    const searchBar = document.getElementById("location-search");
    const errorField = document.getElementById("error-field");
    var searchedLocation = null;

    setupMap();
    searchBar.addEventListener("change", () => {
        searchedLocation = searchBar.value;
        searchBar.value = "";
        searchedLocation = searchedLocation.replace(/\//g, '%2F');

        getLocationCordinates(searchedLocation).then(locationObj => {
            if (locationObj == null) {
                errorField.classList.remove("hidden");
            }
            else {
                errorField.classList.add("hidden");
                searchBar.parentNode.classList.remove("nolocation");

                document.getElementById("map").classList.remove("hidden");
                resizeMapElement();
                moveMapView(locationObj.Latitude, locationObj.Longitude, locationObj.Zoom);

                const location = document.getElementById("location");
                location.innerHTML = locationObj.Name;
                location.classList.remove("hidden");

                getWeather(locationObj.Latitude, locationObj.Longitude)
                    .then(weatherObj => {
                        const template = document.querySelector(".forecast-container");
                        removeNonTemplateChildren(template.parentNode);

                        const currentWeatherElement = template.cloneNode(true);
                        currentWeatherElement.id = "";
                        currentWeatherElement.classList.remove("hidden");
                        setWeather(currentWeatherElement, weatherObj, 0);
                        template.parentNode.appendChild(currentWeatherElement);

                        for (let i = 1; i < weatherObj.days.length; i++) {
                            const newElement = template.cloneNode(true);
                            newElement.id = "";
                            newElement.classList.remove("hidden");
                            setWeather(newElement, weatherObj, i);
                            template.parentNode.appendChild(newElement);
                        }
                    });
            }
        });
    });
});

window.addEventListener("resize", () => {
    resizeMapElement();
});

function resizeMapElement() {
    const mapElement = document.getElementById("map");

    mapElement.style.height = `${mapElement.offsetWidth * 0.5}px`;
}

function moveMapView(lat, lon, zoom) {
    removeMarkers();

    map.invalidateSize();
    map.setView([lat, lon], zoom);
    L.marker([lat, lon]).addTo(map);
}

async function setupMap() {
    map = L.map('map').setView([0, 0], 13);

    L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
        maxZoom: 19,
        attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
    }).addTo(map);
}

function removeMarkers() {
    map.eachLayer(function(layer) {
        if (layer instanceof L.Marker) {
            map.removeLayer(layer);
        }
    });
}

async function getLocationCordinates(location) {
    if (location == null || typeof location !== "string") {
        return null;
    }

    var locationObj = {
        Name: "",
        Suburb: "",
        City: "",
        Country: "",
        Latitude: 0,
        Longitude: 0,
        Zoom: 13
    }

    await fetch(`https://nominatim.openstreetmap.org/search?q=${location}&format=geojson&addressdetails=1`)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            return response.json();
        })
        .then(data => {
            if (data.features.length === 0) {
                locationObj = null;
            }
            else {
                console.log(data)
                const addressProperties = data.features[0].properties.address;

                if ("suburb" in addressProperties) {
                    locationObj.Suburb = addressProperties.suburb + ", ";
                }

                if ("city" in addressProperties) {
                    locationObj.City = addressProperties.city + ", ";
                }

                if ("country" in addressProperties) {
                    locationObj.Country = addressProperties.country
                }

                locationObj.Name = locationObj.Suburb + locationObj.City + locationObj.Country;

                if (data.features[0].properties.addresstype == "country") {
                    locationObj.Zoom = 2;
                }

                locationObj.Latitude = data.features[0].geometry.coordinates[1];
                locationObj.Longitude = data.features[0].geometry.coordinates[0];
            }

        })
        .catch(error => {
            console.error('Fetch error:', error);
        });

    return locationObj;
}

async function setWeather(parent, weatherObj, index) {
    const iconElement = parent.querySelector(".icon");
    const tempElement = parent.querySelector(".temperature");
    const descElement = parent.querySelector(".desc");
    const precipitationElement = parent.querySelector(".precipitation");
    const speedElement = parent.querySelector(".speed");
    const directionElement = parent.querySelector(".direction");

    tempElement.innerHTML = `${weatherObj.days[index].temperature} ${weatherObj.units.temperature}`;
    precipitationElement.innerHTML += `${weatherObj.days[index].precipitation} ${weatherObj.units.precipitation}`;
    speedElement.innerHTML += `${weatherObj.days[index].windSpeed} ${weatherObj.units.windSpeed}`;
    directionElement.innerHTML += `${weatherObj.days[index].windDirection}`;

    const dayOfData = parent.querySelector(".day-of-data");
    if (weatherObj.days[index].time === null) {
        dayOfData.innerHTML = "Current Weather";
    }
    else {
        const dayString = weatherObj.days[index].time.toLocaleDateString('en-US', { weekday: 'long' });
        dayOfData.innerHTML = dayString;
    }

    await fetch(`/weathercode/descriptions.json`)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            return response.json();
        })
        .then(data => {
            if (weatherObj.days[index].isDay) {
                iconElement.src = data[`${weatherObj.days[index].weatherCode}`].day.image;
                descElement.innerHTML = data[`${weatherObj.days[index].weatherCode}`].day.description;
            } else {
                iconElement.src = data[`${weatherObj.days[index].weatherCode}`].night.image;
                descElement.innerHTML = data[`${weatherObj.days[index].weatherCode}`].night.description;
            }


        })
        .catch(error => {
            console.error('Fetch error:', error);
        });
}

async function getWeather(lat, lon) {
    var weatherObj = {
        units: {
            temperature: "°C",
            precipitation: "mm",
            windSpeed: "km/h",
        },
        days: [{
            time: null,
            is_day: true,
            weatherCode: 0,
            temperature: 0,
            precipitation: 0,
            windSpeed: 0,
            windDirection: ""
        }]
    };

    await fetch(`https://api.open-meteo.com/v1/forecast?latitude=${lat}&longitude=${lon}&current=temperature_2m,is_day,precipitation,weather_code,wind_speed_10m,wind_direction_10m&daily=weather_code,temperature_2m_max,precipitation_sum,wind_speed_10m_max,wind_direction_10m_dominant&timezone=auto`)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP error! Status: ${response.status}`);
            }

            return response.json();
        })
        .then(data => {
            weatherObj.units.temperature = data.current_units.temperature_2m;
            weatherObj.units.precipitation = data.current_units.precipitation;
            weatherObj.units.windSpeed = data.current_units.wind_speed_10m;

            weatherObj.days[0].weatherCode = data.current.weather_code;
            weatherObj.days[0].temperature = data.current.temperature_2m;
            weatherObj.days[0].is_day = data.current.is_day;
            weatherObj.days[0].precipitation = data.current.precipitation;
            weatherObj.days[0].windSpeed = data.current.wind_speed_10m;
            weatherObj.days[0].windDirection = getWindDirectionString(data.current.wind_direction_10m);

            for (let i = 1; i < data.daily.time.length; i++) {
                const [year, month, day] = data.daily.time[i].split('-');
                const dateObject = new Date(year, month - 1, day);

                weatherObj.days.push({
                    time: dateObject,
                    weatherCode: data.daily.weather_code[i],
                    temperature: data.daily.temperature_2m_max[i],
                    is_day: true,
                    precipitation: data.daily.precipitation_sum[i],
                    windSpeed: data.daily.wind_speed_10m_max[i],
                    windDirection: getWindDirectionString(data.daily.wind_direction_10m_dominant[i])
                });
            }
        })
        .catch(error => {
            console.error("Fetch error:", error);
        });

    return weatherObj;
}

function getWindDirectionString(degrees) {
    const directions = ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW'];
    const index = Math.round(degrees / 45) % 8;
    return directions[index];
}

function removeNonTemplateChildren(node) {
    while (node.children.length != 3) {
        node.removeChild(node.lastChild);
    }
}
