var jsonData = null;
var currentImage = 0;

window.addEventListener("load", () => {
    loadTopStories();
});

async function loadTopStories() {
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

    const topStoryTemplate = document.getElementById("topstory-template");

    for (let i = 0; i < JSONData.articles.length; i++) {
        var tmpPath = `${filePath}${JSONData.articles[i].category}/${JSONData.articles[i].filename}/`;

        const newElement = topStoryTemplate.cloneNode(true);
        newElement.id = "";

        const img = newElement.querySelector(".other-article-image").children[0];
        img.src = tmpPath + "images/main.jpg";

        const header = newElement.querySelector(".other-article-text").children[0];
        try {
            const response = await fetch(tmpPath + "index.html");

            if (!response.ok) {
                throw new Error('Network response was not ok');
            }

            const htmlContent = await response.text();

            const tmpContainer = document.createElement('div');
            tmpContainer.innerHTML = htmlContent;

            const headline = tmpContainer.querySelector(".headline").children[0];
            header.innerHTML = headline.innerHTML;
        } catch (error) {
            console.error(`Couldn't fetch ${tmpPath + "index.html"}`, error);
        }

        const articleLink = newElement.querySelector(".article-link");
        articleLink.href = tmpPath + "index.html";

        newElement.style.display = "flex";
        topStoryTemplate.parentNode.appendChild(newElement);
    }
}
