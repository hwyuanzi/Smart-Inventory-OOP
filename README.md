# Final Project Proposal: SmartInventory - Intelligent Restocking & Tracking System

**Object-Oriented Programming:**

**Institution:** NYU Courant Institute School of Mathematics, Computing, and Data Science

## Team Members
*   **Hollan Yuan** (hy2821@nyu.edu)
*   **L'ara Pierre** (lp2778@nyu.edu)
*   **Han Xiao** (hx2311@nyu.edu)

---

## 1. Project Description and Scope
For our final project, we propose **"SmartInventory,"** a sophisticated, object-oriented inventory management system designed for enterprise-level resource tracking. Moving beyond a rudimentary CRUD (Create, Read, Update, Delete) application, SmartInventory incorporates a proactive mathematical engine. The system's core innovation lies in its automated restocking logic engine, which calculates dynamic stock thresholds based on real-time transaction velocities and triggers intelligent reorder alerts to prevent supply chain disruptions.

Acting as system architects, our goal is to implement this system in **Java** (utilizing Java Swing/JavaFX for the GUI) or **Python** (using PyQt/Tkinter GUI frameworks). We will strictly enforce the **"V2 Decoupling" architecture** (the Entity-Control-Boundary pattern). This guarantees that the visual rendering components (Boundary) are absolutely isolated from the core arithmetic processing and data persistence mechanisms (Control and Entity). This separation of concerns ensures UI modifications will never cascade into backend logical failures, significantly maximizing codebase maintainability, scalability, and testability.

## 2. Comprehensive Use Case Analysis & Actor Interactions
Our system design utilizes rigorous UML specification to manage functionalities. We identify two primary system **Actors**: the **Inventory Manager (Admin)** and the **Staff User (Standard)**.

### Staff Operations (Standard Privilege)
*   **UC-01: View Inventory Dashboard (Base Case):** The Staff User queries the centralized database to view real-time stock levels, product metadata, and location allocations.
*   **UC-02: Process Transaction / Deduct Stock:** Staff inputs a transaction, and the system deducts items from the operational inventory.
*   **UC-03: Update Item Details:** The user modifies quantities or locations.
    *   *UML Annotation (`<<include>>`):* Modifying an item inherently requires retrieving its details first. Therefore, UC-03 is strictly modeled with an `<<include>>` relationship pointing to **UC-01 (View Inventory)**, enforcing logical prerequisites.

### Manager Operations (Admin Privilege)
*   **UC-04: Authenticate Manager Access:** Validates encrypted credentials to unlock restricted administrative operations.
*   **UC-05: System Auto-Restock Alert:**
    *   *UML Annotation (`<<extend>>`):* If a transaction drops an item's stock below its calculated minimum safety threshold, the system conditionally triggers an automated warning. This is meticulously modeled via an `<<extend>>` relationship extending **UC-02 (Process Transaction)**, with a specified extension point (Stock Verification).
*   **UC-06: Approve Restock Orders:** The Admin reviews triggered alerts and dispatches verified purchasing orders to external supplier systems.
    *   *UML Annotation (`<<include>>`):* This rigorously `<<include>>`s an internal verify-supplier sub-process.
*   **UC-07: Generate Analytical Reports:** The Admin commands the system to compile turnover rate analytics.
    *   *UML Annotation (`<<include>>`):* Generating this report will `<<include>>` automated sub-processes like "Calculate Total Asset Value" to ensure object-oriented modularity.
*   **UC-08: Manage Product Catalog Hierarchy:** Admin defines new `Product` categories into the system, directly interacting with the Entity persistence layout.

## 3. Object-Oriented Logical Architecture & UML Class Design
To guarantee high cohesion and low coupling, our **Class and Sequence Diagrams** explicitly map the Trinity of Object Types utilizing all core OOP relationships:

### 3.1 Entity Objects (The Data Layer)
We utilize **Generalization (Inheritance)** and **Polymorphism** to create a highly scalable product catalog:
*   **`Product` (Abstract Base Class):** Encapsulates core item fields (ID, Name, BasePrice) and abstract methods (`calculateValue()`).
    *   **`PerishableProduct` (Concrete Subclass):** Inherits from `Product`. Introduces unique attributes like `expirationDate` and overrides `calculateValue()` to simulate price depreciation over time.
    *   **`DurableProduct` (Concrete Subclass):** Inherits from `Product`. Implements logic for long-term durable item metrics.

### 3.2 Control Objects (The Business Logic Layer)
The arithmetic and flow control are orchestrated entirely independent of the UI:
*   **`InventoryManager`:** Acts as the central system orchestrator. 
    *   *UML Annotation (Aggregation / Composition):* Maintains an **Aggregation** (or **Composition**, depending on database lifespan configuration) relationship by holding a modular `List<Product>` collection. 
*   **`RestockController`:** Processes dynamic threshold evaluations. 
    *   *UML Annotation (Dependency):* Utilizes a **Dependency** relationship (`...uses...`) by temporarily instantiating an `AlertNotifier` object to dispatch warnings. It does not store the `AlertNotifier` as a persistent field—it only depends on it during the brief execution slice of a method.

### 3.3 Boundary Objects (The Presentation Layer)
*   **`MainDashboardGUI`:** The primary interface for data visualization and navigation triggering.
*   **Task-Specific GUI Forms:** When an Actor initiates a task, `MainDashboardGUI` instantiates specialized event forms (e.g., `UpdateStockGUI`). 
    *   *UML Annotation (Realization / Interfaces):* All GUI forms will implement a common `IRenderable` interface (**Realization** relationship), enforcing Polymorphism when the Control layer issues display commands via `showResult()`. This perfectly manifests the V2 Decoupling standard.

## 4. Required Final Deliverables & Artifacts
To demonstrate our mastery of software engineering principles, the final project submission will encompass:
1.  **Comprehensive Use Case Diagram:** Visually demarcating the system boundary, Actors, and the precise mathematical flow of `<<extend>>` and `<<include>>` execution paths.
2.  **Structural Class Diagram:** A meticulously detailed blueprint showcasing all classes, attributes, methods (with visibility modifiers `+`, `-`, `#`), and specifically calling out Inheritance, Composition, Aggregation, Realization, and Dependency edges mapping the EBC pattern.
3.  **Behavioral Sequence Diagrams:** Multiple temporal diagrams visualizing dynamic message passing across lifelines (Entity, Control, and Boundary) for:
    *   *Standard Workflow:* Staff processing a valid sales transaction.
    *   *Algorithmic Workflow:* The system automatically calculating thresholds and conditionally dispatching an `<<extend>>` restock alert.