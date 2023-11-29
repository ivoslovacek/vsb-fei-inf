window.addEventListener("load", () => {
    loadArticleCreationTime();
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
