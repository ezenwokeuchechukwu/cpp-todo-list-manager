// todo.cpp
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Task class representing each to-do item
class Task {
public:
    std::string description;
    bool done;

    Task(const std::string& desc) : description(desc), done(false) {}
};

// ToDoList class managing tasks
class ToDoList {
    std::vector<Task> tasks;

public:
    // Add a new task
    void addTask(const std::string& desc) {
        tasks.emplace_back(desc);
    }

    // List all tasks with their status
    void listTasks() {
        if (tasks.empty()) {
            std::cout << "No tasks in the list.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". [" << (tasks[i].done ? "X" : " ") << "] " << tasks[i].description << "\n";
        }
    }

    // Mark a task as done based on index
    void markDone(size_t index) {
        if (index > 0 && index <= tasks.size()) {
            tasks[index - 1].done = true;
            std::cout << "Task marked done.\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
    }

    // Save tasks to a file
    void saveToFile(const std::string& filename) {
        std::ofstream out(filename);
        if (!out) {
            std::cerr << "Error opening file for saving.\n";
            return;
        }
        for (auto& task : tasks) {
            out << task.done << "|" << task.description << "\n";
        }
    }

    // Load tasks from a file
    void loadFromFile(const std::string& filename) {
        tasks.clear();
        std::ifstream in(filename);
        if (!in) return;  // No file yet, no tasks loaded

        std::string line;
        while (std::getline(in, line)) {
            size_t delimPos = line.find('|');
            if (delimPos != std::string::npos) {
                bool done = (line.substr(0, delimPos) == "1");
                std::string desc = line.substr(delimPos + 1);
                Task t(desc);
                t.done = done;
                tasks.push_back(t);
            }
        }
    }
};

int main() {
    ToDoList todo;
    todo.loadFromFile("tasks.txt");

    int choice = 0;
    while (choice != 4) {
        std::cout << "\nTo-Do List Manager\n";
        std::cout << "1. Add Task\n2. List Tasks\n3. Mark Task Done\n4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Clear newline from input buffer

        if (choice == 1) {
            std::string desc;
            std::cout << "Enter task description: ";
            std::getline(std::cin, desc);
            todo.addTask(desc);
        } else if (choice == 2) {
            todo.listTasks();
        } else if (choice == 3) {
            size_t taskNum;
            std::cout << "Enter task number to mark done: ";
            std::cin >> taskNum;
            todo.markDone(taskNum);
        } else if (choice == 4) {
            todo.saveToFile("tasks.txt");
            std::cout << "Tasks saved. Goodbye!\n";
        } else {
            std::cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
