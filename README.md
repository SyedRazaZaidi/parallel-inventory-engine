# parallel-inventory-engine
A high-performance C backend utilizing POSIX Threads and OpenMP, paired with a React dashboard to benchmark parallel computing paradigms on large-scale datasets.
1. Repository Setup Details
Use these when creating the repository on GitHub to make it highly discoverable and professional.

Repository Name Options: * parallel-inventory-engine (Recommended)

pdc-compute-dashboard

c-react-parallel-backend

Short Description (About Section): A high-performance C backend utilizing POSIX Threads and OpenMP, paired with a React dashboard to benchmark parallel computing paradigms on large-scale datasets.

Topics / Tags: c, parallel-computing, pthreads, openmp, react, high-performance-computing, socket-programming, dashboard, backend-architecture

2. The Complete README.md
Copy and paste this directly into your README.md file. It highlights the architecture, the custom HTTP server, and the real-time UI—which looks great to recruiters and instructors.

Markdown
# Parallel Computing Inventory Engine

A high-performance backend system built in C that demonstrates the speedup capabilities of parallel computing paradigms. The system processes massive inventory datasets using standard Sequential logic, POSIX Threads (Pthreads), and OpenMP, and serves a modern React-based dashboard to visualize the performance metrics in real-time.

## 🚀 Features

* **Custom Modular Backend:** A lightweight, custom-built HTTP server in C handling routing, dynamic memory allocation, and API endpoints without relying on heavy web frameworks.
* **Parallel Processing:** Compares execution times across three paradigms:
    * **Sequential (Linear):** Baseline single-core processing.
    * **POSIX Threads:** Explicit multi-threading (configured for 4 cores) with memory chunking.
    * **OpenMP:** Compiler-directed automatic parallelization.
* **Dynamic Workloads:** Handles dataset sizes ranging from 10 Million to 250+ Million records, with dynamic heap reallocation to prevent memory leaks.
* **Interactive React Dashboard:** A single-file React application (served directly by the C backend) utilizing Tailwind CSS and Recharts to visualize execution speedups and system logs.

## 🛠️ Tech Stack

* **Backend:** C, Socket Programming, POSIX Threads, OpenMP
* **Frontend:** HTML5, React 18, Tailwind CSS, Recharts, Babel

## ⚙️ How to Run Locally

### Prerequisites
* GCC Compiler (with OpenMP support)
* A POSIX-compliant OS (Linux/macOS or WSL for Windows)

### Build and Execute
1. Clone the repository:
   ```bash
   git clone [https://github.com/yourusername/parallel-inventory-engine.git](https://github.com/yourusername/parallel-inventory-engine.git)
   cd parallel-inventory-engine
Compile the C backend:

Bash
gcc -fopenmp server.c compute.c -o pdc_server
Run the server:

Bash
./pdc_server
Access the dashboard: Open your web browser and navigate to http://localhost:8080.

📡 API Endpoints
The C server exposes the following REST-like endpoints to trigger computations:

GET /run/linear?items=[SIZE] - Executes standard sequential processing.

GET /run/pthreads?items=[SIZE] - Executes POSIX Threads processing.

GET /run/openmp?items=[SIZE] - Executes OpenMP processing.

GET / or GET /index.html - Serves the React frontend.


---

### 3. Professional Resume Snippets
When you add this to your resume or LinkedIn, here are a few ways to describe it that adhere to strict industry standards (concise, action-oriented, 1-3 lines max):

**Option 1 (Focus on Full-Stack & Architecture):**
> Developed a custom C-based HTTP server utilizing POSIX Threads and OpenMP to parallelize data processing across 250M+ records. Designed a single-file React and TailwindCSS dashboard to monitor real-time execution metrics and CPU paradigm speedups.

**Option 2 (Focus on High-Performance Computing):**
> Engineered a parallel computing engine in C to benchmark Sequential, Pthreads, and OpenMP processing times on massive inventory arrays. Implemented dynamic memory reallocation and a custom REST-like API to serve performance data to a Recharts UI. 

**Option 3 (Short & Punchy):**
> Built a parallelized inventory processing system in C utilizing OpenMP and Pthreads, achieving significant speedups over linear processing, visualized through a custom-served React dashboard.
