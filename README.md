# AeroPath - Flight Route Planner

## Overview

AeroPath is a C++ application that helps users find the shortest flight routes between cities based on either fare or duration. It utilizes Dijkstra's algorithm to compute the shortest paths and supports data loading from a text file.

## Features

- **Bidirectional Flight Network**: Allows adding flight routes between cities.
- **Shortest Path Calculation**: Users can choose to find the shortest path based on either fare or duration.
- **File-Based Data Loading**: Reads flight details from a text file.
- **User-Friendly Menu**: Provides an interactive CLI menu for users to explore flight paths.
- **Path Visualization**: Displays the shortest route along with fare and duration.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/AeroPath.git
   cd AeroPath
   ```
2. Compile the program using g++:
   ```sh
   g++ AeroPath.cpp -o AeroPath
   ```
3. Run the program:
   ```sh
   ./AeroPath
   ```

## Usage

1. Ensure you have a file named `Aeropaths.txt` with flight details in the format:
   ```
   CityA|CityB|Fare|Duration
   ```
2. Run the program and choose an option from the menu:
   - **Display all cities**
   - **Find the shortest path between cities** (based on fare or duration)

## Example Input File (`Aeropaths.txt`)

```
New York|Los Angeles|300|360
Los Angeles|Chicago|200|240
Chicago|Houston|150|180
Houston|Miami|180|200
```

## Contributing

Contributions are welcome! Feel free to submit a pull request with enhancements or bug fixes.

## License

This project is licensed under the MIT License.

## Contact

For any inquiries, reach out at parikshitvel0210\@gmail.com or open an issue on GitHub.

