# The-Deadly-Embrace-in-Databases-The-Microsoft-SQL-Server-Deadlock-Case
# 🔄 SQL Server Deadlock Simulation in C++  
### "The Deadly Embrace in Databases – A Case Study with Microsoft SQL Server"

---

## 📌 Overview

This project demonstrates a **real-world deadlock scenario** in **Microsoft SQL Server**, triggered through **concurrent multithreaded transactions written in C++** using **ODBC API**. Inspired by operating system-level deadlocks, the simulation showcases how database-level deadlocks occur, get detected, and resolved.

---

## 🎓 Academic Context

- **Course:** Fundamentals of Operating Systems  
- **Semester:** 6th  
- **Institution:** K.S. School of Engineering and Management, VTU  
- **Guided By:** Mrs. Nagaveni  
- **Department:** Electronics and Communication Engineering  

---

## 👥 Team Members

| Name                  | USN         |
|-----------------------|-------------|
| Aashish Aryan N S     | 1KG22EC002  |
| Abhinandan S          | 1KG22EC003  |
| Anvitha M Shetty      | 1KG22EC009  |
| Asfiya Kousar B I     | 1KG22EC010  |
| Gowthami B            | 1KG22EC011  |
| Bezawada Sucharitha   | 1KG22EC012  |

---

## ⚙️ How It Works

Two threads simulate conflicting database transactions:

- **Transaction A**:
  - Locks a row in `TableA`
  - Waits, then attempts to lock a row in `TableB`

- **Transaction B**:
  - Locks a row in `TableB`
  - Waits, then attempts to lock a row in `TableA`

This lock ordering difference creates a **circular wait**, fulfilling all **Coffman conditions** for a deadlock.

SQL Server's **wait-for graph** detects the cycle and rolls back the "cheaper" transaction, resolving the deadlock automatically.

---

## 💻 Tech Stack

- C++
- Microsoft SQL Server
- ODBC (Open Database Connectivity)
- Windows APIs
- SQL (DDL + DML)

---

## 📁 Repository Structure

```bash
├── README.md
├── DeadlockSimulator.cpp     # Main C++ code to simulate deadlock
├── report.pdf                # Academic report (case study)
