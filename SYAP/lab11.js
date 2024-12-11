
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
  
    setName(newName) {
      this.name = newName;
    }
  
    addTask(task) {
      if (task instanceof Task) {
        this.tasks.push(task);
      } else {
        throw new Error("Добавляемый объект должен быть экземпляром класса Task.");
      }
    }
  
 
    filterTasksByStatus(isCompleted) {
      return this.tasks.filter((task) => task.isCompleted === isCompleted);
    }
  }
  

  const task1 = new Task(1, "Купить молоко");
  const task2 = new Task(2, "Написать отчет");
  const task3 = new Task(3, "Позвонить другу", true);
  const task4= new Task(4, "hd",true);
  const todoList1 = new Todolist(1, "Личные дела");
  const todoList2 = new Todolist(2, "Рабочие дела");
  
  todoList1.addTask(task1);
  todoList1.addTask(task2);
  todoList2.addTask(task3);
  todoList2.addTask(task4);
  
  task1.setName("Купить молоко и хлеб");
  task4.setName("оаввао");
  
  task2.toggleStatus();
  task4.toggleStatus();
  
  console.log("Выполненные задачи (Личные дела):", todoList1.filterTasksByStatus(true));
  console.log("Невыполненные задачи (Рабочие дела):", todoList2.filterTasksByStatus(false));
  
  todoList1.setName("Личные приоритеты");
  
  console.log("Обновленный список дел:", todoList1);
  console.log("Обновленный список задач:", todoList1.tasks);
  