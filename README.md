          ## TRAFFIC QUEUE SIMULATOR
  This project simulates queue operations using C to demonstrate vehicle flow and waiting behavior in a controlled system. 

![Image](https://github.com/user-attachments/assets/ed7f13fa-6c3a-4f2e-a867-d9351b505e5a)


## Features

- Realistic intersection layout with lanes and stop lines  
- Multiple vehicle types:
  - Regular Cars  
  - Ambulances  
  - Police Cars  
  - Fire Trucks
    
 - Intelligent traffic light system:
  - Normal cycling between directions  
  - Priority mode for emergency vehicles  
  - Congestion detection and handling
    
- Vehicle behaviors:
  - Lane following  
  - Turning (left/right)  
  - Traffic light obeying  
  - Vehicle spacing and collision avoidance  
  - Right-turn-on-red capability
    
- Real-time statistics:
  - Vehicle throughput  
  - Total vehicles  
  - Vehicles per minute :contentReference[oaicite:1]{index=1}

## Prerequisites
To run this simulation, you need:

- GCC or G++ compiler  
- SDL2 library  
- MinGW (for Windows) :contentReference[oaicite:2]{index=2}

### Installing SDL2

#### On Windows:

1. Download the SDL2 development libraries from https://libsdl.org  
2. Extract the contents to your project directory  
3. Create folders:
   - `include` (for SDL2 headers)  
   - `lib` (for SDL2 libs)  
   - `bin` (for executable output) :contentReference[oaicite:3]{index=3}

## Project Structure
Traffic-Simulation/

├── include/ # Header files

├── lib/ # Library files

├── src/ # Source files

│ ├── main.c # Main simulation code

│ ├── traffic_simulation.h

│ ├── traffic_simulation.c

│ └── generator.c # Vehicle generator

├── bin/ # Executable output

└── README.md

## Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/AayushmanBajracharya/Dsa-Queue-Simulator.git
   cd Dsa-Queue-Simulator
   ```
   
Compile both programs:

g++ -Iinclude -Llib -o bin/main.exe src/main.c src/traffic_simulation.c -lmingw32 -lSDL2main -lSDL2

g++ -o bin/generator src/generator.c src/traffic_simulation.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2



## Running the Simulation

1.Start the vehicle generator:

./bin/generator.exe

2.In another terminal, start the main simulation:

./bin/main.exe



## How It Works

Program Components

1.Generator (generator.exe):

-Generates vehicles with random properties

-Writes vehicle info to a file

-Spawns new vehicles every 500 ms



2.Main Simulation (main.exe):

-Reads vehicle data

-Renders intersection & vehicles

-Manages traffic flow & lights

-Processes movement logic



3.Traffic Management Logic:

-Each lane is implemented using a Queue

-Vehicles are enqueued when they arrive

-Vehicles are dequeued when signals allow movement

-Emergency vehicles bypass normal queues

-Prevents collisions using spacing rules




## Time complexity analysis:

| Operation                        | Data Structure Used | Time Complexity |
| -------------------------------- | ------------------- | --------------- |
| Vehicle arrival (enqueue)        | Queue               | O(1)            |
| Vehicle departure (dequeue)      | Queue               | O(1)            |
| Emergency vehicle priority check | Queue traversal     | O(n)            |
| Traffic signal switching         | Conditional logic   | O(1)            |
| Congestion detection             | Queue traversal     | O(n)            |
| Vehicle movement update          | Iteration           | O(n)            |

short Explanation:

-O(1) operations execute in constant time regardless of queue size

-O(n) operations depend on the number of vehicles present in the lane



## Learning Outcomes:

-Practical implementation of Queue data structure

-Understanding traffic management systems

-Real-time simulation handling

-Emergency priority algorithms

-File handling and inter-process coordination

-SDL-based rendering concepts



 ## Applications:

-Traffic signal simulation

-Smart city traffic management

-Emergency response prioritization

-DSA academic projects

-System simulation studies


## Contribution:

1.Fork the repository

2.Create a new branch

git checkout -b feature-name


3.Commit your changes

git commit -m "Added new feature"


4.Push to the branch

git push origin feature-name

5.Open a Pull Request



## Acknowledgement:
 
-SDL2 Development Team

-Faculty and mentors for guidance

-Online DSA learning resources




