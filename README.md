# SmartInventory - Inventory Tracking and Restocking System

[![Tests](https://img.shields.io/badge/tests-passing-brightgreen)](#testing)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue)](#build-and-run)

**Object-Oriented Programming**  
**Institution:** NYU Courant Institute School of Mathematics, Computing, and Data Science

## Team Members

* **Hollan Yuan** (hy2821@nyu.edu)
* **L'ara Pierre** (lp2778@nyu.edu)
* **Han Xiao** (hx2311@nyu.edu)

---

## 1. Project Description and Scope

**SmartInventory** is an object-oriented inventory management system designed to help small businesses track products, manage stock levels, record sales, and monitor low-stock items through a command-line interface (CLI). The system addresses common inventory problems such as understocking, limited visibility into product quantities, and manual restocking oversight.

The project is implemented in **C++17** and uses classes, inheritance, encapsulation, dynamic dispatch, and object interactions to model real inventory workflows. Inventory data is stored in internal `vector` collections, and users interact with the system through numbered CLI menus.

The system supports two user roles:

* **Employee User (Standard Privilege):** Can view inventory, search items, and record sales transactions.
* **Inventory Manager (Admin Privilege):** Can perform employee operations and additional manager-only operations such as adding, deleting, updating, checking low stock, and fulfilling restock requests.

The system also includes a low-stock/restocking feature. When a sale causes an item's quantity to fall at or below its threshold, the system automatically creates a pending `RestockRequest`. Managers can later review and fulfill those requests.

## Directory Structure

```text
Smart-Inventory-OOP/
|-- README.md
|-- LICENSE
|-- smart_inventory
|-- include/
|   |-- employee.h
|   |-- inventory.h
|   |-- inventory_system.h
|   |-- item.h
|   |-- manager.h
|   |-- restock_request.h
|   |-- transaction.h
|   `-- user.h
|-- src/
|   |-- employee.cpp
|   |-- inventory.cpp
|   |-- inventory_system.cpp
|   |-- item.cpp
|   |-- main.cpp
|   |-- manager.cpp
|   |-- restock_request.cpp
|   |-- transaction.cpp
|   `-- user.cpp
|-- tests/
|   `-- cli_regression.sh
`-- UMLs/
    |-- ClassUML.html
    |-- SequenceUML.html
    `-- UseCaseUML.html
```

Directory and file roles:

* **`include/`** contains class declarations and public interfaces.
* **`src/`** contains class implementations and the `main.cpp` program entry point.
* **`tests/`** contains the automated CLI regression test script.
* **`UMLs/`** contains source files for the class, sequence, and use case UML diagrams.
* **`smart_inventory`** is the compiled executable generated from the C++ source files.
* **`README.md`** explains the project scope, use cases, architecture, setup, running instructions, and testing.

## 2. Use Case Analysis & Actor Interactions

Our system includes two primary **Actors**: the **Inventory Manager (Admin)** and the **Employee User (Standard)**.

### Employee Operations (Standard Privilege)

* **UC-01: View Full Inventory:** The Employee User can view current stock levels and basic product information.
* **UC-02: Search Item:** The Employee User can search for a specific item by name or ID.
* **UC-03: Make Transaction / Record Sale:** The Employee User can record a sale, and the system will update the item quantity accordingly.

### Manager Operations (Admin Privilege)

* **UC-04: Add Item:** The Inventory Manager can add a new item to the inventory.
* **UC-05: Delete Item:** The Inventory Manager can remove an item from the inventory.
* **UC-06: Update Item Details:** The Inventory Manager can edit item information such as name, price, threshold, or category.
* **UC-07: Check Low Stock Alerts:** The Inventory Manager can view items that are below their stock thresholds.
* **UC-08: Update Stock Quantity:** The Inventory Manager can manually adjust stock levels when needed.
* **UC-09: Review Restock Requests:** The Inventory Manager can review and fulfill restock requests.

Manager access authentication is implemented by the login flow, but it is treated as a security precondition rather than a separate use case. Before manager-only operations can run, the user must choose the Manager role and authenticate with a manager account.

## 3. Object-Oriented Logical Architecture & UML Class Design

The system separates data, business logic, user roles, and CLI control flow into focused classes.

### 3.1 Entity Objects (Data Layer)

* **`Item`**: Represents a product in the inventory. It stores item ID, name, category, quantity, price, and stock threshold.
* **`Transaction`**: Represents a completed sale transaction. It stores transaction ID, item ID, item name, sold quantity, total price, and timestamp.
* **`RestockRequest`**: Represents a pending restock request generated when an item becomes low in stock.

### 3.2 User Objects (Role Layer)

* **`User`**: Abstract base class for system users. It stores username, password, and role, and defines shared authentication behavior.
* **`Employee`**: Derived from `User`. It implements standard inventory operations such as viewing inventory, searching items, and recording sales.
* **`Manager`**: Derived from `Employee`. It inherits employee operations and adds manager-only operations for inventory administration and restocking.

Current inheritance structure:

```text
User
  |
Employee
  |
Manager
```

This matches the design that a manager can perform all employee operations plus additional administrative actions.

### 3.3 Control Objects (Business Logic Layer)

* **`Inventory`**: Stores and manages `Item` objects and pending `RestockRequest` objects. It supports item search, item updates, low-stock checks, restock request creation, and request clearing.
* **`InventorySystem`**: Acts as the main controller. It coordinates sign-up, login, role-based menus, inventory actions, transactions, and user input validation.

### 3.4 Boundary Object (Presentation Layer)

* **CLI Menu Interface**: Presents numbered options for login, sign-up, employee operations, and manager operations.

This design supports the rubric's object-oriented requirements: classes are separated by responsibility, user roles use inheritance and polymorphism, and object messages in the code correspond to the UML sequence diagrams.

## 4. Build and Run

### 4.1 Environment Setup

This project only requires a C++17 compiler and a terminal.

On macOS, install Apple's command line developer tools if a compiler is not already available:

```bash
xcode-select --install
```

Check that the compiler is available:

```bash
g++ --version
```

If `g++` prints a version, the environment is ready.

### 4.2 Open the Project Directory

From a terminal, go to the project root:

```bash
cd "/Users/haowen/Documents/NYU/Spring_2026/Object-Oriented_Programming/Final Project/Smart-Inventory-OOP"
```

If the project is cloned or moved to a different location, use that local project path instead. The project root is the folder that contains `README.md`, `src/`, `include/`, and `UMLs/`.

### 4.3 Compile the Program

Compile all source files from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o smart_inventory
```

This command:

* uses the C++17 standard;
* includes header files from the `include/` directory;
* compiles every `.cpp` file in `src/`;
* creates an executable file named `smart_inventory`.

### 4.4 Run the Program

```bash
./smart_inventory
```

The repository may include a prebuilt `smart_inventory` executable for macOS arm64, but recompiling is recommended after source changes. The executable file is not source code; it is the compiled program generated by the build command.

### Default Accounts

```text
Employee:
username: employee
password: emp123

Manager:
username: manager
password: admin123
```

The system also supports in-session sign-up for employee and manager accounts. Newly signed-up accounts are available during the current program run.

### 4.5 How to Use the Program

When the program starts, the main menu appears:

```text
=== SmartInventory ===
1. Login
2. Sign Up
0. Exit
```

Choose `1` to log in with an existing account, choose `2` to create a new account, or choose `0` to exit.

#### Sign Up

Choose `2. Sign Up`, then select the role:

```text
1. Employee
2. Manager
```

After choosing the role, enter a username and password. The system creates an employee ID such as `E-101` or a manager ID such as `M-101`. Usernames must be unique and cannot be empty. Passwords cannot be empty.

#### Login

Choose `1. Login`, then select the role:

```text
1. Employee
2. Manager
```

Then enter the username and password. The role selection is part of authentication: an employee account cannot log in as a manager, and a manager account must be authenticated before manager-only operations are available.

#### Employee Menu

After logging in as an employee, the menu is:

```text
=== Employee Menu ===
1. View Full Inventory
2. Search Item
3. Record Sale / Make Transaction
0. Logout
```

Employee workflow examples:

* Choose `1` to display all inventory items.
* Choose `2`, then enter a name or item ID such as `Apple` or `I1001` to search.
* Choose `3`, then enter an item ID and quantity sold. The system deducts the sold quantity from inventory and records the transaction.

#### Manager Menu

After logging in as a manager, the menu is:

```text
=== Manager Menu ===
1. View Full Inventory
2. Search Item
3. Record Sale / Make Transaction
4. Add Item
5. Delete Item
6. Check Low Stock Alerts
7. Update Item Details
8. Update Stock Quantity
9. Review Restock Requests
0. Logout
```

Manager workflow examples:

* Choose `4` to add a new item by entering its name, category, quantity, price, and threshold.
* Choose `5` to delete an item by item ID.
* Choose `6` to list all items whose quantity is at or below the threshold.
* Choose `7` to update an item's name, category, price, and threshold.
* Choose `8` to manually set an item's stock quantity.
* Choose `9` to view pending restock requests. If requests exist, the manager can fulfill one by entering the item ID.

#### Low-Stock and Restock Flow

When a transaction causes an item's quantity to become less than or equal to its threshold, the system automatically creates a pending restock request. The manager can later use `9. Review Restock Requests` to fulfill that request. When fulfilled, the system increases the item's quantity and clears the pending request.

## 5. Testing

A CLI regression test script is included:

```bash
./tests/cli_regression.sh
```

The test script checks that:

* the project compiles with `-Wall -Wextra -pedantic`;
* employee login and inventory viewing work;
* employee and manager sign-up/login work;
* manager authentication routes users to the manager menu;
* manager accounts inherit employee operations such as search and transaction recording;
* low-stock sales create restock requests;
* repeated low-stock sales do not create duplicate pending restock requests for the same item;
* restock requests can be fulfilled by a manager;
* closed input exits cleanly instead of looping forever.

## 6. UML and Final Deliverables

The project includes the required UML artifacts:

* **Use Case Diagram:** Shows Employee and Manager actors, their use cases, and relationships.
* **Class Diagram:** Shows the implemented classes, attributes, methods, inheritance, composition, aggregation, and dependencies.
* **Sequence Diagrams:** Show object messages for inventory viewing, searching, transaction recording, item management, low-stock checking, stock updates, and restock request review.

UML source files are stored in the `UMLs/` directory. PDF exports are also available for final submission.

## 7. Conclusion

SmartInventory provides a complete CLI-based inventory workflow for a small business. It demonstrates object-oriented design through entity classes, controller classes, inherited user roles, role-based behavior, and message passing between objects. The implemented system satisfies the proposed employee and manager workflows, supports low-stock monitoring and restocking, and includes automated CLI regression tests for core behavior.
