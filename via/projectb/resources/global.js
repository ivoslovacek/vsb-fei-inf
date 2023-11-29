window.addEventListener('load', () => {
    setNavbarButtons();
    footerExploreBBC();
    handleEmailAddress();
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

function footerExploreBBC() {
    const cattegoriesUl = document.getElementById("cattegories");
    const exploreBBC = document.querySelector(".explore");

    for (let i = 0; i < cattegoriesUl.children.length; i++) {
        const li = cattegoriesUl.children[i];
        const item = li.getElementsByTagName("a");
        exploreBBC.appendChild(item[0].cloneNode(true));
    }
}

function handleEmailAddress() {
    const emailInput = document.getElementById("email");
    const emailPattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
    const emailMessage = document.getElementById("email-message");

    emailInput.addEventListener('change', () => {
        if (!emailPattern.test(emailInput.value)) {
            emailMessage.innerHTML = "Please enter a valid email address.";
        }
        else {
            emailMessage.innerHTML = "Thank you for subscribing to our newsletter!";
        }

    });
}
