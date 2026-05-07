# SmartInventory - Inventory Tracking and Restocking System

[![Tests](https://img.shields.io/badge/tests-passing-brightgreen)](#testing)
[![Language](https://img.shields.io/badge/C%2B%2B-17-blue)](#build-and-run)

**Object-Oriented Programming**  
**Institution:** NYU Courant Institute of Mathematical Sciences

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

## 2. Use Case Analysis & Actor Interactions

Our system includes two primary **Actors**: the **Inventory Manager (Admin)** and the **Employee User (Standard)**.

### Employee Operations (Standard Privilege)

* **UC-01: View Full Inventory:** The Employee User can view current stock levels and basic product information.
* **UC-02: Search Item:** The Employee User can search for a specific item by name or ID.
* **UC-03: Make Transaction / Record Sale:** The Employee User can record a sale, and the system will update the item quantity accordingly.

### Manager Operations (Admin Privilege)

* **UC-05: Add Item:** The Inventory Manager can add a new item to the inventory.
* **UC-06: Delete Item:** The Inventory Manager can remove an item from the inventory.
* **UC-07: Check Low Stock Alerts:** The Inventory Manager can view items that are below their stock thresholds.
* **UC-08: Update Item Details:** The Inventory Manager can edit item information such as name, price, threshold, or category.
* **UC-09: Update Stock Quantity:** The Inventory Manager can manually adjust stock levels when needed.
* **UC-10: Review Restock Requests:** The Inventory Manager can review and fulfill restock requests.

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

Compile from the project root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o smart_inventory
```

Run the program:

```bash
./smart_inventory
```

The repository also includes a prebuilt `smart_inventory` executable for macOS arm64, but recompiling is recommended after source changes.

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
