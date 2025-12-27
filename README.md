https://github.com/user-attachments/assets/ed15872e-2439-448e-bdf7-e99620870b38

This project simulates queue operations using C to demonstrate vehicle flow and waiting behavior in a controlled system.



# 📁 Project Structure

dsa-queue-simulator/

├── include/

│ ├── queue.h

│ └── priority_queue.h

├── src/

│ ├── queue.c

│ ├── priority_queue.c

│ ├── receiver.c

│ └── receiver2.c

├── bin/

├── .gitignore

├── Makefile

├── README.md

└── demo.gif


- `include/` – Header files for data structures  
- `src/` – Source files (queue logic and test drivers)  
- `bin/` – (Optional) compiled binaries  
- `demo.gif` – GIF showing queue behavior 



## 🚀 How to Build & Run
### 🧾 Requirements
- GCC or compatible C/C++ compiler  
- Make utility (optional but recommended)
  This will build the queue and priority queue programs.

  
  
  🏃 Run the Simulator

Once built, run the compiled executables from the bin/ folder:

./bin/queue_simulator
./bin/priority_queue_simulator



USAGE

Each program runs in console mode.
You can perform operations like:
Enqueue new items
Dequeue existing items
View queue contents
Exit simulation

The priority queue version will dequeue based on priority rules.


Technical Documentation (DSA Queue Simulator)

Implemented using array-based queue
Follows FIFO principle
Uses front and rear pointers
Priority queue processes elements by priority
Handles overflow and underflow conditions
Menu-driven console application
Developed in C 
Built using Makefile / GCC


ACKNOWLEDGEMENT
SDL2 development team
Traffic simulation research community
