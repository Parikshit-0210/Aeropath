#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct FlightInfo {
    int duration;
    double fare;
};

class Graph {
    unordered_map<string, vector<pair<string, FlightInfo>>> g;

public:
    void addEdge(string start, string end, int duration, double fare);
    void ShortestPath(string dep, string des, bool useFare, int& total_duration, double& total_fare);
    void Display();
    void loadDataFromFile(string filename);
    void printPath(unordered_map<string, string>& parent, string destination);
};

// Bidirectional Aeropath network
void Graph::addEdge(string start, string end, int duration, double fare) {
    g[start].push_back({end, {duration, fare}});
    g[end].push_back({start, {duration, fare}});
}

void Graph::ShortestPath(string dep, string des, bool useFare, int& total_duration, double& total_fare) {
    unordered_map<string, double> distFare;
    unordered_map<string, int> distInMin;
    unordered_map<string, string> parent;

    for (auto x : g) {
        distFare[x.first] = DBL_MAX;  // Initialize durations as infinity (double)
        distInMin[x.first] = INT_MAX;   // Initialize durations in km as infinity (int)
    }

    unordered_map<string, bool> processed;
    for (auto x : g)
        processed[x.first] = false;

    distFare[dep] = 0;
    distInMin[dep] = 0;
    parent[dep] = "";  // Start has no parent
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> q;
    q.push({0, dep});

    while (!q.empty()) {
        string a = q.top().second;
        q.pop();
        if (processed[a])
            continue;
        processed[a] = true;

        for (auto u : g[a]) {
            string b = u.first;
            // Update fare or duration based on user preference
            double newFare = distFare[a] + u.second.fare;
            int newduration = distInMin[a] + u.second.duration;

            if (useFare) {  // If user chose fare
                if (newFare < distFare[b]) {
                    distFare[b] = newFare;
                    distInMin[b] = newduration;  // Update duration in km separately
                    q.push({distFare[b], b});
                    parent[b] = a;  // Update the parent of node b
                }
            } else {  // If user chose duration
                if (newduration < distInMin[b]) {
                    distInMin[b] = newduration;
                    distFare[b] = newFare;  // Update fare based on duration
                    q.push({distInMin[b], b});
                    parent[b] = a;  // Update the parent of node b
                }
            }
        }
    }

    // Print the path from dep to des
    if (distFare[des] == DBL_MAX) {
        cout << "\nNo path exists between " << dep << " and " << des << ".\n";
        total_duration = 0;
        total_fare = 0.0;
        return;
    } else {
        cout << "\nShortest path from " << dep << " to " << des << " is: ";
        printPath(parent, des);  // Print the path
        cout << '\n';
    }

    total_fare = distFare[des];  // Store the total fare (or cost)
    total_duration = distInMin[des];  // Store the total duration
}

void Graph::Display() {
    for (auto x : g)
        cout << x.first << '\n';
}

void Graph::loadDataFromFile(string filename) {
    ifstream inFlightDetails(filename);
    if (!inFlightDetails) {
        cerr << "Flight Details file not opened correctly";
        return;
    }

    string line;
    string origin, destination;
    int duration;
    double fare;

    while (getline(inFlightDetails, line)) {
        stringstream ss(line);
        getline(ss, origin, '|');
        getline(ss, destination, '|');
        ss >> fare;
        ss.ignore();  // Ignore the '|' delimiter
        ss >> duration;

        addEdge(origin, destination, duration, fare);
        addEdge(destination, origin, duration, fare);
    }

    inFlightDetails.close();
}

void Graph::printPath(unordered_map<string, string>& parent, string destination) {
    if (parent[destination] == "") {
        cout << destination;
        return;
    }
    printPath(parent, parent[destination]);
    cout << " -> " << destination;
}

int main() {
    Graph g;
    string filename;
    g.loadDataFromFile("Aeropaths.txt");

    int ch = 1,choice;
    do {
        cout << endl << endl;
        cout << "................................................................................................................\n"
             << "................................................................................................................\n"
             << "............................%%%%...%%%%%%%.%%%%%....%%%%...%%%%%....%%%%...%%%%%%..%%...%%......................\n"
             << "...........................%%..%%..%%......%%..%%..%%..%%..%%..%%..%%..%%....%%....%%...%%......................\n"
             << "...........................%%%%%%..%%%%....%%%%%...%%..%%..%%%%%...%%%%%%....%%....%%%%%%%......................\n"
             << "...........................%%..%%..%%......%%.%%...%%..%%..%%......%%..%%....%%....%%...%%......................\n"
             << "...........................%%..%%..%%%%%%%.%%..%%...%%%%...%%......%%..%%....%%....%%...%%......................\n"
             << "................................................................................................................\n\n\n\n";
        cout << "\n====== AeroPath Menu ======\n";
        cout << "1. Display all cities\n";
        cout << "2. Find the shortest path between cities\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        cin.ignore();  // To ignore the newline after entering the choice

        switch (ch) {
            case 1: {
                // Option to display all cities
                cout << "\nList of all cities:\n";
                g.Display();
                break;
            }

            case 2: {
                // Option to find the shortest path between cities
                cout << "\nEnter Departure City: ";
                string dep;
                getline(cin, dep);
                dep[0] = toupper(dep[0]);  // Capitalize the first letter of the departure city

                cout << "\nEnter Destination City: ";
                string des;
                getline(cin, des);
                des[0] = toupper(des[0]);  // Capitalize the first letter of the destination city

                cout << "\nChoose weight for shortest path calculation (1 for Fare, 2 for duration): ";
                int choice;
                cin >> choice;
                bool useFare = (choice == 1);

                int total_duration = 0;
                double total_fare = 0.0;

                g.ShortestPath(dep, des, useFare, total_duration, total_fare);

                if (total_duration == 0) {
                    cerr << "There is no Flight Path between " << dep << " and " << des << "!\n";
                } else {
                    // Print both duration and fare
                    cout << "\nTotal duration: " << total_duration << " min";
                    cout << "\nTotal fare: Rs. " << total_fare << '\n';
                }
                break;
            }

            case 0:
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

        // Clear screen before displaying the menu again (if on Windows)
        if (ch != 0) {
            cout << "\nEnter 1 to return to the menu or 0 to exit: ";
            cin >> ch;
            cin.ignore(); // Clear the buffer
            if (ch == 1) {
                system("CLS"); // Clear the screen (works on Windows)
            } else {
                ch = 0;  // Exit loop if user chooses not to return to the menu
            }
        }

    } while (ch != 0);
    system("CLS"); // Clear the screen (works on Windows)
   cout << endl << endl <<
 "            /                                 /      "
 "\n          #/                                #/     "
 "\n    #     ##                                ##     "
 "\n   ##     ##                                ##     "
 "\n   ##     ##                                ##     "
 "\n ######## ##  /##      /###    ###  /###    ##  /##       ##   ####         /###    ##   ####         "
 "\n########  ## / ###    / ###  /  ###/ #### / ## / ###       ##    ###  /    / ###  /  ##    ###  /     "
 "\n   ##     ##/   ###  /   ###/    ##   ###/  ##/   /        ##     ###/    /   ###/   ##     ###/      "
 "\n   ##     ##     ## ##    ##     ##    ##   ##   /         ##      ##    ##    ##    ##      ##       "
 "\n   ##     ##     ## ##    ##     ##    ##   ##  /          ##      ##    ##    ##    ##      ##"
 "\n   ##     ##     ## ##    ##     ##    ##   ## ##          ##      ##    ##    ##    ##      ##"
 "\n   ##     ##     ## ##    ##     ##    ##   ######         ##      ##    ##    ##    ##      ##"
 "\n   ##     ##     ## ##    /#     ##    ##   ##  ###        ##      ##    ##    ##    ##      /#"
 "\n   ##     ##     ##  ####/ ##    ###   ###  ##   ### /      #########     ######      ######/ ##"
 "\n    ##     ##    ##   ###   ##    ###   ###  ##   ##/         #### ###     ####        #####   ##"
 "\n                /                                                  ### "
 "\n               /                                            #####   ###"
 "\n              /                                           /#######  /#"
 "\n             /                                           /      ###/";
    cout << endl;
    return 0;
}
