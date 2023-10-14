window.addEventListener('load', () => {
    const todoSaveBttn = document.getElementById("todo-save");

    cleanUpTodoList();
    loadTodoList();

    todoSaveBttn.addEventListener('click', saveNewTodo);
});

function saveNewTodo() {
    const todoHead = document.getElementById("todo-header");
    const todoDesc = document.getElementById("todo-desc");

    const todoObject = {
        head: todoHead.value.toString(),
        desc: todoDesc.value.toString(),
    };

    const todoObjectString = JSON.stringify(todoObject);

    let todoIndex = localStorage.getItem("lastTodo");
    if (todoIndex == null) {
        todoIndex = 0;
    }
    else {
        todoIndex++;
    }

    localStorage.setItem(todoIndex, todoObjectString);
    localStorage.setItem("lastTodo", todoIndex);

    const todoTemplate = document.getElementById("template");
    const newTodo = todoTemplate.cloneNode(true);
    newTodo.id = "id" + todoIndex;

    const newTodoHead = newTodo.querySelector("#todo-item-head");
    newTodoHead.textContent = todoObject.head;

    const newTodoDesc = newTodo.querySelector("#todo-item-desc");
    newTodoDesc.textContent = todoObject.desc;

    const newTodoDelete = newTodo.querySelector("#todo-item-delete");
    newTodoDelete.addEventListener('click', deleteTodo);

    const newTodoEdit = newTodo.querySelector("#todo-item-edit");
    newTodoEdit.addEventListener('click', editTodo);

    document.querySelector(".todo-container").appendChild(newTodo);

    todoHead.value = '';
    todoDesc.value = '';
};

function deleteTodo(event) {
    const match = event.target.parentElement.parentElement.id.match(/(\d+)/);
    const index = parseInt(match[0], 10);

    document.querySelector(".todo-container").removeChild(event.target.parentElement.parentElement);

    localStorage.removeItem(index);
}

function editTodo(event) {
    const todoListItem = event.target.parentElement.parentElement;

    const todoHead = document.getElementById("todo-header");
    todoHead.value = todoListItem.querySelector("#todo-item-head").textContent;

    const todoDesc = document.getElementById("todo-desc");
    todoDesc.value = todoListItem.querySelector("#todo-item-desc").textContent;

    deleteTodo(event);
}

function loadTodoList() {
    let maxIndex = localStorage.getItem("lastTodo");
    if (maxIndex == null) {
        return;
    }

    for (let i = 0; i <= maxIndex; i++) {
        const todoObjectString = localStorage.getItem(i);
        if (todoObjectString == null) {
            continue;
        }

        const todoObject = JSON.parse(todoObjectString);

        const todoTemplate = document.getElementById("template");
        const newTodo = todoTemplate.cloneNode(true);
        newTodo.id = "id" + i;

        const newTodoHead = newTodo.querySelector("#todo-item-head");
        newTodoHead.textContent = todoObject.head;

        const newTodoDesc = newTodo.querySelector("#todo-item-desc");
        newTodoDesc.textContent = todoObject.desc;

        const newTodoDelete = newTodo.querySelector("#todo-item-delete");
        newTodoDelete.addEventListener('click', deleteTodo);

        const newTodoEdit = newTodo.querySelector("#todo-item-edit");
        newTodoEdit.addEventListener('click', editTodo);

        document.querySelector(".todo-container").appendChild(newTodo);
    }
}

function cleanUpTodoList() {
    const maxIndex = localStorage.getItem("lastTodo");
    if (maxIndex == null) {
        return;
    }

    let lastTodo = 0;

    for (let i = 0; i <= maxIndex; i++) {
        const todoObjectString = localStorage.getItem(i);
        if (todoObjectString) {
            lastTodo = i;
            continue;
        }

        for (let j = i; j <= maxIndex; j++) {
            const ObjectStringToTry = localStorage.getItem(j);
            if (ObjectStringToTry == null) {
                localStorage.removeItem(j);
            }
            else {
                localStorage.setItem(i, localStorage.getItem(j));
                localStorage.removeItem(j);
                lastTodo = i;
                i = j;
            }
        }
    }

    console.log(lastTodo);
    localStorage.setItem("lastTodo", lastTodo);
}
