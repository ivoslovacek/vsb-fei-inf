window.addEventListener('load', () => {
    const todoSaveBttn = document.getElementById("todo-save");
    todoSaveBttn.addEventListener('click', () => {
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

        todoHead.value = '';
        todoDesc.value = '';
    });
});
