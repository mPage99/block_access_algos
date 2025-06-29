# Disk Scheduling Algorithm Visualizer

This project simulates and visualizes various disk scheduling algorithms using a C backend for computation and a simple API to serve visualizations. It provides a hands-on understanding of how operating systems handle disk I/O requests and how different algorithms affect disk performance.

## 📚 Overview

Disk scheduling determines how read/write requests to a disk are ordered. This simulation includes four major algorithms:

- **FCFS (First-Come, First-Served)**
- **SSTF (Shortest Seek Time First)**
- **LOOK**
- **C-LOOK**

Each algorithm processes a list of block requests and outputs `.csv` files containing step-by-step disk head movements. These files are used by the API to generate visual graphs that show:

- **Step** — the order in which each request is serviced  
- **Position** — the disk block location of the read/write head

Understanding both values is important to visualize how much the head moves and compare the efficiency of different algorithms.

## 🛠️ Features

- Implemented in **C** for efficient simulation
- Outputs per-algorithm `.csv` files (e.g. `fcfs_steps.csv`, `sstf_steps.csv`, etc.)
- Includes a sample input file: `block-list.txt`
- Comes with a `Makefile` to build and run the simulator easily
- Integrates with an API that visualizes simulation results as interactive graphs

## 📂 File Structure
```
project-root/
├── Makefile           # Build automation script
├── README.md          # Project documentation
├── block-list.txt     # Input file with disk block requests
├── block_algos.c      # Core implementation of disk scheduling algorithms
├── run_sim            # Compiled executable (generated after build)
```
## 🚀 Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`)
- `make` (optional, but recommended)

### 🧪 Sample Input Format

The `block-list.txt` file should contain one integer per line, each representing a disk block request.

Example:

50
10
30
70
90

The **first number** is treated as the starting disk head position.

### 🔧 Build and Run

1. **Build the executable (using bash):**
```
make
```
2. ** Run the simulator**
```
./run_sim block-list.txt
```
Example Output (This will also generate the .csv step files for each algorithm):

FCFS Total Seek: 180
SSTF Total Seek: 130
LOOK Total Seek: 120
C-LOOK Total Seek: 110

