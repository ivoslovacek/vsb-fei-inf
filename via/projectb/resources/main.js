window.addEventListener('load', () => {
    setNavbarButtons();
    displayCurrentDate();
    footerExploreBBC();
});

function setNavbarButtons() {
    const liWithButton = document.querySelectorAll(".li-button");

    liWithButton.forEach((li) => {
        li.getElementsByTagName("button")[0].addEventListener("click", () => {
            let cattegory = li.getElementsByTagName("a")[0].classList[0];
            cattegory += "-navbar";

            let navbar = document.getElementById(cattegory);

            navbar.classList.toggle("hidden-element")
            navbar.parentNode.classList.toggle("hidden");
        });
    });
}

function displayCurrentDate() {
    const currentDate = new Date();

    const options = { weekday: 'long', day: 'numeric', month: 'long' };
    const formattedDate = new Intl.DateTimeFormat('en-UK', options).format(currentDate);

    const DateElement = document.getElementById("date");
    DateElement.innerHTML = formattedDate;
}

function footerExploreBBC() {
    const cattegoriesUl = document.getElementById("cattegories");
    const exploreBBC = document.querySelector(".explore");

    for (let i = 0; i < cattegoriesUl.children.length; i++) {
        const li = cattegoriesUl.children[i];
        const item = li.getElementsByTagName("a");
        exploreBBC.appendChild(item[0].cloneNode(true));
    }
}
