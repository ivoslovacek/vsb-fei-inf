window.addEventListener('load', () => {
    loadArticles();
    displayCurrentDate();

    window.addEventListener('resize', () => {
        const articleContainer = document.querySelector(".articles-container");

        if (window.innerWidth < 1280) {
            articleContainer.style.minHeight = `${0.234375 * window.innerWidth}px`;
        }
        else {
            articleContainer.style.minHeight = `${300}px`;
        }

    });
});

function displayCurrentDate() {
    const currentDate = new Date();

    const options = { weekday: 'long', day: 'numeric', month: 'long' };
    const formattedDate = new Intl.DateTimeFormat('en-UK', options).format(currentDate);

    const DateElement = document.getElementById("date");
    DateElement.innerHTML = formattedDate;
}

async function loadArticles() {
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

    const mainArticle = document.querySelector(".main-article");
    var tmpPath = `${filePath}${JSONData.articles[0].category}/${JSONData.articles[0].filename}/images/main.jpg`;

    mainArticle.style.backgroundImage = `url(${tmpPath})`;

    console.log(mainArticle.style.backgroundImage)
}
