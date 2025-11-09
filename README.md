Restaurant Ordering System (ROS) Simulation

Project Overview

Welcome to the Restaurant Ordering System (ROS), a sophisticated Java simulation designed to model the full lifecycle of a modern restaurant order—from customer selection to payment and fulfillment.

This project was developed for the Advanced Software Engineering course at Cairo University, with a core focus on applying Gang of Four (GoF) Design Patterns to achieve a highly modular, extensible, and maintainable architecture.

Architectural Design: Patterns in Action
Our system is structured around key behavioral and structural design patterns, ensuring that we can swap out components (like payment methods or discount rules) without altering the core ordering logic.

1. The Core Workflow (Template Method)
The entire process of placing an order—from calculating totals to generating the receipt—is controlled by the Template Method pattern (OrderProcessingTemplate).

It defines a fixed "skeleton" for processing an order: Apply Charges → Apply Discounts → Generate Receipt.

The steps vary based on the order type: DeliveryOrderProcessor, DineInOrderProcessor, and TakeawayOrderProcessor implement the required specific logic (e.g., Delivery Fee vs. Service Charge).

2. Item Construction (Builder Pattern)
Complex, customizable items like Pizza and Burger are constructed using the Builder pattern.

This keeps the core Order class clean, separating the construction logic from the order assembly.

The OrderDirector guides specialized builders (EasternPizzaBuilder, ClassicBurgerBuilder) to ensure items are created correctly, regardless of how many toppings or add-ons the user chooses.

3. Payment Methods (Strategy Pattern)
Payment is the most volatile part of any system, so it's managed by the Strategy pattern (IPaymentStrategy).

It allows us to use payment interchangeably—be it CreditCardPayment, MobileWalletPayment, or CashPayment—without modifying the Facade.

Crucially, this is where we implement system resilience, allowing each payment method to define its own failure conditions (e.g., Mobile Wallet transaction limits) via checked exceptions.

4. Discount Handling (Chain of Responsibility)
Calculating cumulative and conditional discounts is handled sequentially using the Chain of Responsibility pattern.

Discounts are linked together (ItemCategoryDiscountHandler → MinimumOrderDiscountHandler → CustomerLoyaltyDiscountHandler).

The order progresses through the chain, with each handler deciding if its rule applies to the current order total, providing transparent and stackable discount calculation.

5. System Communication (Observer Pattern)
Once an order is successfully paid for, the Observer pattern notifies backend systems.

The Order acts as the subject, notifying observers like the KitchenSystem (start cooking!) and the WaiterSystem (prepare for service/delivery).

Running the Project
The project is pre-configured to run three comprehensive static test scenarios via the Application.java main method.

Prerequisites
Java Development Kit (JDK) 11 or newer installed.

A Java IDE (IntelliJ, Eclipse, VS Code) or terminal for compilation and execution.

Execution
Compile: Ensure all source files (*.java) are compiled.

Run: Execute the Application class.

Bash

# Example command line execution (adjust classpath as necessary)
java Application
Example Output Preview
Running the program will automatically execute three distinct tests, printing the full processing details for each, including applied charges, discounts, and the final receipt or error message.


Scenario 1	Delivery Order	Loyalty Discount and Chicken Category Discount applied via the Chain of Responsibility, followed by a successful Credit Card Strategy.

Scenario 2	Takeaway Order	Minimum Order Discount ($10 off) triggered by a high subtotal, demonstrating the Takeaway Template Method and a simple Cash Payment Strategy.

Scenario 3	Payment Failure	Order value intentionally set over $500 to trigger a PaymentProcessingException within the MobileWalletPayment Strategy, halting the workflow before completion.
