# FCFS - Based Operating System Process Scheduling Simulator (C Project)

## 📌 1. Project Title
**Design and Implementation of a FCFS-Based Operating System Process Scheduler using Queues and HashMap in C**

---

## 🎯 2. Objective
The objective of this project is to build a simplified CPU process scheduler similar to those used inside modern operating systems.

The simulator maintains all processes using a **Process Control Block (PCB)** stored in a HashMap and manages process execution through:

- Ready Queue  
- Waiting Queue  
- Terminated Queue  

The scheduler supports:

- FCFS-based scheduling  
- I/O blocking and completion  
- Process creation and termination  
- Kill events at runtime  
- Execution timeline simulation  
- CPU time vs I/O time handling  

This project covers concepts like OS scheduling, PCB management, state transitions, queues, and CPU scheduling mechanics.

---

## 📘 3. Key Concepts

### **CPU Burst**
Time during which a process actively executes on CPU (arithmetic, logic, memory operations).

### **I/O Burst**
Time spent waiting for I/O operations:
- Disk read/write  
- Network I/O  
- Keyboard input  
- System calls  

During I/O burst, the process **does not use CPU**.

---

## 🏗️ 4. System Architecture Overview

### **1. PCB HashMap**
- Key → PID  
- Value → PCB structure  
Contains:  
process name, CPU burst, I/O start time, I/O duration, timestamps, and state.

### **2. Queues (Linked List Based)**
- **Ready Queue** → runnable processes  
- **Waiting Queue** → processes performing I/O  
- **Terminated Queue** → processes that have completed or were killed  

### **3. Scheduler**
- Implements **First Come First Serve (FCFS)**  
- Simulates CPU burst execution  
- Detects I/O events  

### **4. System Clock**
Each tick:
- Advances CPU burst  
- Updates I/O timers  
- Applies scheduled kill events  
- Moves processes between queues  

---

## 📥 5. Input Specification

### **Process Format**
<process_name> <pid> <cpu_burst> <io_start_time> <io_duration>

### **Kill Event Format**
KILL <PID> <kill_time>

### Example Input
chrome 101 10 4 3
vscode 102 8 3 2
terminal 103 6 2 3
spotify 104 5 0 0
notepad 105 7 5 2
KILL 102 7
KILL 105 10

---

## ⚙️ 6. Functional Requirements

### **6.1 Process Initialization**
- Read process details from input  
- Create PCB and store in HashMap  
- Insert into Ready Queue  

### **6.2 Scheduling Behavior**

#### ✔ 1. FCFS Scheduling
The scheduler always selects the **front** process from the Ready Queue.

#### ✔ 2. CPU Execution
Simulated using:

Turnaround = completion_time
Waiting = Turnaround - CPU_burst - IO_burst

---

## 🔁 8. Example State Transition Outputs

### **Test Case 1**
Name PID CPU IO_Start IO_Duration
chrome 101 10 4 3
vscode 102 6 - -
notes 103 4 2 2

**Expected Output**
PID Name CPU IO Turnaround Waiting
101 chrome 10 3 18 8
102 vscode 6 0 10 4
103 notes 4 2 20 16

---

### **Test Case 2 – Kill Event**
PID Name CPU IO Status Turnaround Waiting
201 server 12 3 KILLED at 4 - -
202 db 6 0 OK 10 4
203 cache 7 2 OK 19 12

---

### **Test Case 3**
firefox 301 8 3 2
editor 302 5 - -
music 303 10 4 4

**Expected Output**
PID Name CPU IO Turnaround Waiting
301 firefox 8 2 17 9
302 editor 5 0 8 3
303 music 10 4 23 13

---

## 📦 Assignment Submission Guidelines

### ✔ Create a public GitHub repository  
### ✔ Use a separate branch & create a Pull Request  
### ✔ Written in **C language only**  
### ✔ Deadline: **11th December, 05:00 PM**  
### ❌ No AI-generated code allowed  
### ✔ Mentors will review thoroughly  

---

## 🙌 Author
Your Name  
B.Tech CSE  
Kalpavriksha OS Assignment – FCFS Scheduler Project

