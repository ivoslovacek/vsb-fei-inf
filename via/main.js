window.addEventListener('load', () => {
    setInterval(updateTimeString, 1000);
    setInterval(updateTimeStamp, 1000);

    const lectButton = document.getElementById("lec-btn");
    const labButton = document.getElementById("lab-btn");
    const allButton = document.getElementById("all-btn");

    lectButton.addEventListener('click', () => {
        const lectures = document.querySelectorAll('.prednaska');
        const laboratories = document.querySelectorAll('.cviceni');

        for (let i = 0; i < lectures.length; i++) {
            lectures[i].classList.add("highlighted");
        }

        for (let i = 0; i < laboratories.length; i++) {
            laboratories[i].classList.remove("highlighted");
        }
    });

    labButton.addEventListener('click', () => {
        const lectures = document.querySelectorAll('.prednaska');
        const laboratories = document.querySelectorAll('.cviceni');

        for (let i = 0; i < lectures.length; i++) {
            lectures[i].classList.remove("highlighted");
        }

        for (let i = 0; i < laboratories.length; i++) {
            laboratories[i].classList.add("highlighted");
        }
    });

    allButton.addEventListener('click', function changeAll() {
        const lectures = document.querySelectorAll('.prednaska');
        const laboratories = document.querySelectorAll('.cviceni');

        for (let i = 0; i < lectures.length; i++) {
            lectures[i].classList.add("highlighted");
        }

        for (let i = 0; i < laboratories.length; i++) {
            laboratories[i].classList.add("highlighted");
        }
    });

    allButton.dispatchEvent(new Event('click'));

    const labClasses = document.querySelectorAll(".cviceni");
    const lecClasses = document.querySelectorAll(".prednaska");
    const allClasses = Array.from(labClasses).concat(Array.from(lecClasses));

    const dialog = document.querySelector("dialog");
    dialog.querySelector("button").addEventListener('click', () => {
        const textArea = dialog.querySelector("textarea");
        const target = localStorage.getItem('lastActive');

        localStorage.setItem(target, textArea.value.toString());
        textArea.value = '';

        dialog.close();
    });

    for (let i = 0; i < allClasses.length; i++) {
        allClasses[i].addEventListener('click', (event) => {
            if (allClasses[i].classList.contains('highlighted')) {
                const cell = event.target;
                const textArea = dialog.querySelector("textarea");
                const target = cell.textContent + cell.classList[0];

                textArea.value = localStorage.getItem(target);
                localStorage.setItem('lastActive', target);
                dialog.showModal();
            }
        })
    }

    updateTimeString();
    updateTimeStamp();
});

function updateTimeStamp() {
    const timeStamp = document.getElementById('timeStamp');
    timeStamp.style.visibility = "shown";

    const timeHead = document.getElementById('timeHead');
    timeHead.style.visibility = "shown";


    const currentDateTime = new Date();
    const day = currentDateTime.getDay();
    switch (day) {
        case 7:
            timeStamp.style.visibility = "hidden";
            timeHead.style.visibility = "hidden";

            break;

        default:
            const cells = document.getElementById('timetable').children[0].children[day].children;

            const currentTimeInMinutes = currentDateTime.getHours() * 60 + currentDateTime.getMinutes();
            // start time of each class segment in minutes, each segment is 45 minutes
            // this is then used to find which coresponding cell 
            // should the timestamp and timehead be placed in
            const classStart = [435, 480, 540, 585, 645, 690, 750, 795, 855, 900, 960, 1005, 1065, 1110];

            if (currentTimeInMinutes >= classStart[0] && currentTimeInMinutes <= classStart[classStart.length - 1] + 45) {
                let cellIndex = 0;

                for (let i = 0; i < classStart.length; i++) {
                    if (currentTimeInMinutes >= classStart[i] && currentTimeInMinutes <= classStart[i + 1]) {
                        cellIndex = i;
                    }
                }

                const cellRect = cells[cellIndex + 1].getBoundingClientRect();

                let posX = cellRect.left + ((currentTimeInMinutes - classStart[cellIndex]) / 45) * (cellRect.width);
                if (currentTimeInMinutes > classStart[cellIndex + 1]) {
                    posX = cellRect.left + cellRect.width;
                }

                timeStamp.style.top = `${cellRect.top}px`;
                timeStamp.style.left = `${posX}px`;
                timeStamp.style.height = `${cellRect.height}px`;

                timeHead.style.top = `${cellRect.top - timeHead.getBoundingClientRect().height / 2}px`;
                timeHead.style.left = `${posX - timeHead.getBoundingClientRect().width / 2}px`;
            }
            else {
                timeStamp.style.visibility = "hidden";
                timeHead.style.visibility = "hidden";
            }
    }
}

function updateTimeString() {
    const timeElement = document.getElementById('time');

    const timeString = timeElement.querySelector('span');

    const currentDateTime = new Date();

    const year = currentDateTime.getFullYear();
    const month = currentDateTime.getMonth() + 1;
    const day = currentDateTime.getDate();

    const hours = currentDateTime.getHours();
    const minutes = currentDateTime.getMinutes();
    const seconds = currentDateTime.getSeconds();

    const dateTimeString = `${year}-${month}-${day} ${hours}:${minutes}:${seconds}`;

    timeString.textContent = dateTimeString;
}
