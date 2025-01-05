// HTML структура
const app = document.createElement('div');
app.innerHTML = `
  <div>
    <input id="taskInput" type="text" placeholder="Название задачи">
    <button id="addTaskButton">Добавить</button>
  </div>
  <div>
    <button id="showAll">Все</button>
    <button id="showCompleted">Выполненные</button>
    <button id="showPending">Невыполненные</button>
  </div>
  <ul id="taskList"></ul>
`;
document.body.appendChild(app);

// Классы (взяты из вашего кода)
class Task {
    constructor(id, name, isCompleted = false) {
        this.id = id;
        this.name = name;
        this.isCompleted = isCompleted;
    }

    setName(newName) {
        this.name = newName;
    }

    toggleStatus() {
        this.isCompleted = !this.isCompleted;
    }
}

class Todolist {
    constructor(id, name) {
        this.id = id;
        this.name = name;
        this.tasks = [];
    }

    addTask(task) {
        if (task instanceof Task) {
            this.tasks.push(task);
        } else {
            throw new Error("Добавляемый объект должен быть экземпляром класса Task.");
        }
    }

    removeTask(taskId) {
        this.tasks = this.tasks.filter(task => task.id !== taskId);
    }

    filterTasksByStatus(isCompleted) {
        return this.tasks.filter(task => task.isCompleted === isCompleted);
    }
}

// Основной функционал
let currentTaskId = 1;
const todoList = new Todolist(1, "Список дел");

const renderTasks = (filter = null) => {
    const taskList = document.getElementById('taskList');
    taskList.innerHTML = '';

    let tasksToRender = todoList.tasks;
    if (filter === 'completed') {
        tasksToRender = todoList.filterTasksByStatus(true);
    } else if (filter === 'pending') {
        tasksToRender = todoList.filterTasksByStatus(false);
    }

    tasksToRender.forEach(task => {
        const taskItem = document.createElement('li');

        const checkbox = document.createElement('input');
        checkbox.type = 'checkbox';
        checkbox.checked = task.isCompleted;
        checkbox.addEventListener('change', () => {
            task.toggleStatus();
            renderTasks(filter);
        });

        const taskName = document.createElement('span');
        taskName.textContent = task.name;

        const editButton = document.createElement('button');
        editButton.textContent = 'Редактировать';
        editButton.addEventListener('click', () => {
            const newName = prompt('Введите новое название задачи:', task.name);
            if (newName) {
                task.setName(newName);
                renderTasks(filter);
            }
        });

        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Удалить';
        deleteButton.addEventListener('click', () => {
            todoList.removeTask(task.id);
            renderTasks(filter);
        });

        taskItem.appendChild(checkbox);
        taskItem.appendChild(taskName);
        taskItem.appendChild(editButton);
        taskItem.appendChild(deleteButton);

        taskList.appendChild(taskItem);
    });
};

// Обработчики событий
const addTaskButton = document.getElementById('addTaskButton');
addTaskButton.addEventListener('click', () => {
    const taskInput = document.getElementById('taskInput');
    const taskName = taskInput.value.trim();
    if (taskName) {
        const newTask = new Task(currentTaskId++, taskName);
        todoList.addTask(newTask);
        taskInput.value = '';
        renderTasks();
    }
});

const showAllButton = document.getElementById('showAll');
showAllButton.addEventListener('click', () => renderTasks());

const showCompletedButton = document.getElementById('showCompleted');
showCompletedButton.addEventListener('click', () => renderTasks('completed'));

const showPendingButton = document.getElementById('showPending');
showPendingButton.addEventListener('click', () => renderTasks('pending'));

// Первоначальная отрисовка
renderTasks();
