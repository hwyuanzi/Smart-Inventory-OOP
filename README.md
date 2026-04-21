# Final Project Proposal: SmartInventory - Inventory Tracking and Restocking System

**Object-Oriented Programming**

**Institution:** NYU Courant Institute School of Mathematics, Computing, and Data Science

## Team Members
* **Hollan Yuan** (hy2821@nyu.edu)
* **L'ara Pierre** (lp2778@nyu.edu)
* **Han Xiao** (hx2311@nyu.edu)

---

## GitHub Repository URL
[Add repository link here]

## 1. Project Description and Scope
For our final project, we propose **SmartInventory**, an object-oriented inventory management system designed to help small businesses track products, manage stock levels, and monitor low-stock items using a command-line interface (CLI). Many businesses face challenges such as overstocking, understocking, and limited visibility into current inventory levels. This system, which we aim to implement in **C++**, addresses these issues by providing an organized and automated approach to inventory tracking, stock updates, and low-stock monitoring.

Rather than being only a basic CRUD (Create, Read, Update, Delete) application, SmartInventory will also include a restocking feature that alerts users when item quantities fall below predefined stock thresholds. The system is intended for a small store or business environment and will allow users to view inventory records, search for items, update product information, record sales transactions, and review low-stock alerts through a simple interface.

## 2. Use Case Analysis & Actor Interactions
Our system includes two primary **Actors**: the **Inventory Manager (Admin)** and the **Employee User (Standard)**.

### Employee Operations (Standard Privilege)
* **UC-01: View Full Inventory:** The Employee User can view current stock levels and basic product information.
* **UC-02: Search Item:** The Employee User can search for a specific item by name or ID.
* **UC-03: Make Transaction / Record Sale:** The Employee User can record a sale, and the system will update the item quantity accordingly.

### Manager Operations (Admin Privilege)
* **UC-04: Authenticate Manager Access:** The Inventory Manager logs into the system to access administrative functions.
* **UC-05: Add Item:** The Inventory Manager can add a new item to the inventory.
* **UC-06: Delete Item:** The Inventory Manager can remove an item from the inventory.
* **UC-07: Check Low Stock Alerts:** The Inventory Manager can view items that are below their stock thresholds.
* **UC-08: Update Item Details:** The Inventory Manager can edit item information such as name, price, quantity, or stock threshold.
* **UC-09: Update Stock Quantity:** The Inventory Manager can manually adjust stock levels when needed.
* **UC-10: Review Restock Requests:** The Inventory Manager can review items that may need to be restocked and decide on the next action.

## 3. Object-Oriented Logical Architecture & UML Class Design
Our **Class Diagram** and **Sequence Diagrams** will reflect an object-oriented design with separate responsibilities for data objects, control logic, and user interaction.

### 3.1 Entity Objects (The Data Layer)
The data layer will store the main information used by the system.
* **`Item`**: Represents a product in the inventory and stores attributes such as item ID, name, quantity, price, and stock threshold.
* **`User`**: Represents a system user and stores shared account information.
  * **`Manager`**: A derived class of `User` with administrative permissions.
  * **`Employee`**: A derived class of `User` with standard permissions.

### 3.2 Control Objects (The Business Logic Layer)
The control layer manages the main system behavior.
* **`Inventory`**: Stores and manages the collection of items in the system.
* **`InventorySystem`**: Acts as the main controller, coordinating interactions between users and inventory data.
* **Restock-related logic**: Handles stock threshold checking and low-stock alert generation when item quantities fall below predefined limits.

### 3.3 Boundary Objects (The Presentation Layer)
The presentation layer handles user interaction through a CLI.
* **CLI Menu Interface**: Provides numbered menu options for different user operations, such as viewing inventory, searching for items, adding items, and checking alerts.

This design separates user interaction from inventory data and business logic, which helps improve code organization and maintainability.

## 4. Required Final Deliverables & Artifacts
The final project submission will include:
1. **Use Case Diagram:** Showing the system boundary, actors, and the main use cases of the system, including the low-stock alert behavior.
2. **Class Diagram:** Showing the main classes, attributes, methods, and object-oriented relationships such as inheritance and association.
3. **Sequence Diagram(s):** Showing the interaction between objects during important workflows, such as:
   * **Standard Workflow:** An employee records a sale and the system updates inventory.
   * **Alert Workflow:** The system checks whether the updated quantity is below the stock threshold and generates a low-stock alert if needed.

## 5. Conclusion
SmartInventory provides a practical solution to common inventory challenges in a small business setting. By combining core inventory operations with automated low-stock alerts and a structured object-oriented design, this project demonstrates understanding of object-oriented programming and real-world applicability.
