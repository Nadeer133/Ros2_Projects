# Project Doubt Notes

**Date:** 28 July 2026

------------------------------------------------------------------------

# 1. ROS2 Interface Types vs Generated C++ Types

## Doubt

Why is `float64` in a `.msg` file treated as `double` in C++?

## Explanation

A `.msg` file is **not C++ code**. It is written using ROS2's Interface
Definition Language (IDL), which is language-independent. During
`colcon build`, ROS2 generates C++ classes from the interface.

Therefore:

-   `float64` → `double`
-   `int16` → `int16_t`
-   `bool` → `bool`

The generated C++ class contains normal C++ types, even though the
original `.msg` file uses ROS2 interface types.

### Key Takeaway

Always remember that `.msg` files define an interface, not a C++ class.

------------------------------------------------------------------------

# 2. Why Publishers Cannot Publish Primitive Types

## Doubt

Why can't I publish a `double` or `bool` directly?

## Explanation

ROS2 topics always transport **message objects**, not primitive C++
variables.

Even if you only want to send a single floating-point value, ROS2
expects a message object such as:

-   `std_msgs::msg::Float64`
-   `std_msgs::msg::Bool`

These message objects wrap the primitive value inside a field named
`data`.

### Key Takeaway

Publishers always send ROS2 messages, never raw C++ variables.

------------------------------------------------------------------------

# 3. Understanding `std_msgs`

## Doubt

What exactly is `std_msgs`?

## Explanation

`std_msgs` is a ROS2 package containing simple, reusable message
definitions.

Examples include:

-   `std_msgs::msg::Float64`
-   `std_msgs::msg::Bool`
-   `std_msgs::msg::Int16`
-   `std_msgs::msg::String`

Whenever you need to send a single primitive value on a topic,
`std_msgs` is usually the first package to consider.

------------------------------------------------------------------------

# 4. Understanding `this`

## Doubt

Why do we write:

`std::bind(&VehicleControlManager::publish_all_vehcomnds, this, _1)`?

## Explanation

`this` is a pointer to the current object.

A member function belongs to an object, not just the class itself.

`std::bind()` therefore needs three pieces of information:

1.  Which member function to call.
2.  Which object owns that function (`this`).
3.  The callback arguments (`_1`, `_2`, ...).

Without `this`, the compiler knows *what* function to call but not
*which object* should execute it.

### Key Takeaway

`this` identifies the current object instance.

------------------------------------------------------------------------

# 5. Member Variables vs Global Variables

## Doubt

Are member variables global to the class?

## Explanation

Member variables are **not** global variables.

They belong to each object created from the class.

Every member function of that object can access them directly, which
makes them feel "global" within that object. However, if multiple
objects are created, each object has its own independent copy.

Global variables, on the other hand, exist once for the entire program.

### Key Takeaway

Member variables are object-level data, while global variables are
program-level data.

------------------------------------------------------------------------

# 6. Queue vs Array

## Doubt

Is accessing queue elements the same as accessing array elements?

## Explanation

No.

An array allows random access, meaning any element can be accessed
directly using its index.

A queue follows the FIFO (First-In, First-Out) principle. You can only
interact with the front element (and inspect the rear). Middle elements
cannot be accessed directly.

### Key Takeaway

Arrays are designed for random access. Queues are designed for ordered
processing.

------------------------------------------------------------------------

# 7. Queue Operations

## Explanation

A queue separates **reading** from **removing**.

-   `front()` lets you inspect the first element.
-   `pop()` removes the first element.
-   `pop()` does **not** return the removed value.

Typical processing flow:

1.  Read the front element.
2.  Process it.
3.  Remove it.

This design enforces FIFO behaviour.

### Key Takeaway

Always think of a queue as a waiting line where only the person at the
front can be served.

------------------------------------------------------------------------

# Revision Checklist

-   [ ] ROS2 interface types vs generated C++ types
-   [ ] Why publishers require ROS2 message objects
-   [ ] Purpose of `std_msgs`
-   [ ] Meaning of `this`
-   [ ] Member variables vs global variables
-   [ ] Queue vs array
-   [ ] Difference between `front()` and `pop()`
