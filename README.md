# 🏦 Bank Management System (C++ Console Application)

A complete **banking management system** built in C++ that simulates real-world banking operations including client management, transactions, user administration, and a role-based permission system.

This project is fully file-based and designed to demonstrate **real system architecture concepts in C++**.

---

## 📌 Project Overview

This system allows:

- 👤 Managing bank clients
- 💰 Performing financial transactions
- 👨‍💼 Managing system users
- 🔐 Controlling access using permissions (RBAC)
- 💾 Persistent data storage using text files

---

## ✨ Features

### 👤 Client Management
- Show all clients
- Add new client
- Delete client
- Update client info
- Find client by account number

---

### 💰 Transactions System
- Deposit money
- Withdraw money
- View total balances of all clients

---

### 👨‍💼 User Management System
- List users
- Add new user
- Delete user
- Update user
- Find user

---

### 🔐 Security System
- Login authentication (username + password)
- Role-Based Access Control (RBAC)
- Permission-based feature access
- Admin full access mode
- Access denied protection screen

---

## 🧠 Concepts Used

- File handling (`fstream`)
- Structs (`stClient`, `stUser`)
- Vectors
- Enums for menus & permissions
- Bitwise permission system
- Role-Based Access Control (RBAC)
- Modular programming design
- String parsing & serialization
- Menu-driven console UI
- Authentication system

---

## 🔐 Permission System

Each feature is controlled using numeric permissions:

| Permission | Value |
|------------|------|
| Full Access | -1 |
| Show Clients | 1 |
| Add Client | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |

---

## 📂 Project Structure
