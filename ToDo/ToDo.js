let tasks = [];

// document.addEventListener("DOMContentLoaded", () => {
//   const input = document.getElementById("taskInput");
//   input.addEventListener("keydown", function (event) {
//     if (event.key === "Enter") {
//       AddTask(); 
//     }
//   });
// });

function AddTask() {
  const input = document.getElementById("taskInput");
  const taskText = input.value.trim();

  if (taskText.length > 20 || taskText === "") {
    alert("Please enter a task (max 20 characters).");
    return;
  }
  if (tasks.length >= 5) {
    alert("Sorry, you can't add more than 5 tasks.");
    return;
  }

  tasks.unshift({ text: taskText, done: false });
  input.value = ""; 
  renderTasks();
}

function toggleTask(index) {
  tasks[index].done = !tasks[index].done;
  renderTasks();
}

function deleteTask(index) {
  tasks.splice(index, 1);
  renderTasks();
}

function clearCompleted() {
  tasks = tasks.filter(task => !task.done);
  renderTasks();
}

function renderTasks() {
  const list = document.getElementById("taskList");
  list.innerHTML = "";

  tasks.forEach((task, index) => {
    const li = document.createElement("li");

    const checkbox = document.createElement("input");
    checkbox.type = "checkbox";
    checkbox.checked = task.done;
    checkbox.classList.add("my-checkbox");
    checkbox.onchange = () => toggleTask(index);

    const span = document.createElement("span");
    span.textContent = task.text;
    if (task.done) span.style.textDecoration = "line-through";

    const deleteBtn = document.createElement("button");
    deleteBtn.textContent = "Delete";
    deleteBtn.style.marginLeft = "10px";
    deleteBtn.onclick = () => deleteTask(index);
    deleteBtn.style.display = task.done ? "inline" : "none";

    li.appendChild(checkbox);
    li.appendChild(span);
    li.appendChild(deleteBtn);
    list.appendChild(li);
  });

  const clearBtn = document.getElementById("clearCompletedBtn");

}
