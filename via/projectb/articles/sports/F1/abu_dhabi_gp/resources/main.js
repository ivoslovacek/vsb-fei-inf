var jsonData = null;
var currentImage = 0;

window.addEventListener("load", () => {
    loadArticleCreationTime();
    loadImageCarousel();
});

async function loadArticleCreationTime() {
    const filePath = "/articles/";
    var JSONData = null;

    await fetch("/resources/articles.json")
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            data.articles.sort((a, b) => new Date(b.article_creation) - new Date(a.article_creation));
            JSONData = data;
        })
        .catch(error => {
            console.error('Error loading JSON:', error);
        });

    const urlString = window.location.pathname;

    var trimmedUrl = urlString.replace(/^\/|\/$/g, '');
    var parts = trimmedUrl.split('/');

    var fileName = parts.slice(2, -1).join('/');

    var article = JSONData.articles.find(function(article) {
        return article.filename === fileName;
    });

    var articleDate = new Date(article.article_creation);
    var articleDateString = articleDate.toLocaleDateString('en-GB', {
        day: 'numeric',
        month: 'long',
        year: 'numeric'
    });

    const timeElement = document.getElementById("time");

    timeElement.innerHTML = articleDateString;
}

async function loadImageCarousel() {
    await fetch("resources/images.json")
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            jsonData = data;
        })
        .catch(error => {
            console.error('Error loading JSON:', error);
        });

    const leftBtn = document.getElementById("left-btn");
    const rightBtn = document.getElementById("right-btn");

    leftBtn.addEventListener('click', () => {
        currentImage--;
        loadCurrentImage();
    });

    rightBtn.addEventListener('click', () => {
        currentImage++;
        loadCurrentImage();
    });

    loadCurrentImage();
}

function loadCurrentImage() {
    const image = jsonData.images[currentImage];


    const path = "images/" + image.fileName;
    const description = image.description;

    const imgElement = document.getElementById("carousel-img");
    const descriptionElement = document.getElementById("description");

    imgElement.src = path;
    descriptionElement.innerHTML = description;


    const leftBtn = document.getElementById("left-btn");
    const rightBtn = document.getElementById("right-btn");

    if (currentImage === 0) {
        leftBtn.style.visibility = "hidden";
    }
    else {
        leftBtn.style.visibility = "visible";
    }

    if (currentImage === jsonData.images.length - 1) {
        rightBtn.style.visibility = "hidden";
    }
    else {
        rightBtn.style.visibility = "visible";
    }
}
