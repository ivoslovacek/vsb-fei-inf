window.addEventListener('load', () => {
    loadArticles();
    displayCurrentDate();

    window.addEventListener('resize', () => {
        const articleContainer = document.querySelector(".articles-container");

        if (window.innerWidth < 1280) {
            articleContainer.style.minHeight = `${0.2953125 * window.innerWidth}px`;
        }
        else {
            articleContainer.style.minHeight = `${378}px`;
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
    {
        const mainArticle = document.querySelector(".main-article");
        const imagePath = `${filePath}${JSONData.articles[0].category}/${JSONData.articles[0].filename}/images/main.jpg`;
        mainArticle.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0.4) ),url(${imagePath})`;
        mainArticle.addEventListener("mouseover", () => {
            mainArticle.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.3), rgba(0, 0, 0, 0.3) ),url(${imagePath})`;
        });
        mainArticle.addEventListener("mouseleave", () => {
            mainArticle.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0.4) ),url(${imagePath})`;
        });

        const htmlPath = `${filePath}${JSONData.articles[0].category}/${JSONData.articles[0].filename}/index.html`;
        mainArticle.querySelector(".article-link").href = `${htmlPath}`;

        const link = mainArticle.querySelector(".article-link");
        link.href = `${htmlPath}`;

        const headlineText = mainArticle.querySelector(".headline-text");
        const categoryLink = mainArticle.querySelector(".cattegory-link");

        headlineText.innerHTML = await getHeadline(htmlPath);

        categoryLink.innerHTML = JSONData.articles[0].category.toUpperCase();
    }

    const articles = document.querySelector(".articles");
    for (let i = 1; i < JSONData.articles.length; i++) {
        const imagePath = `${filePath}${JSONData.articles[i].category}/${JSONData.articles[i].filename}/images/main.jpg`;
        const htmlPath = `${filePath}${JSONData.articles[i].category}/${JSONData.articles[i].filename}/index.html`;

        if (i < 5) {
            const article = articles.children[i - 1];

            const background = article.querySelector(".article-background");
            const link = article.querySelector(".article-link");

            background.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0.4) ),url(${imagePath})`;
            background.addEventListener("mouseover", () => {
                background.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.3), rgba(0, 0, 0, 0.3) ),url(${imagePath})`;
            });
            background.addEventListener("mouseleave", () => {
                background.style.backgroundImage = `linear-gradient( rgba(0, 0, 0, 0.4), rgba(0, 0, 0, 0.4) ),url(${imagePath})`;
            });

            link.href = `${htmlPath}`;

            const headlineText = article.querySelector(".headline-text");
            const categoryLink = article.querySelector(".cattegory-link");

            headlineText.innerHTML = await getHeadline(htmlPath);

            categoryLink.innerHTML = JSONData.articles[i].category.toUpperCase();
        }
    }
}

async function getHeadline(url) {
    try {
        const response = await fetch(url);

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        const htmlContent = await response.text();

        const tmpContainer = document.createElement('div');
        tmpContainer.innerHTML = htmlContent;

        const headline = tmpContainer.querySelector(".headline").children[0];
        return headline.innerHTML;
    } catch (error) {
        console.error(`Couldn't fetch ${htmlPath}`, error);
    }
}
