#include <iostream>        // For input/output operations (cout, cin)
#include <fstream>         // For file input/output operations
#include <sstream>         // For string stream operations
#include <string>          // For string data type and operations
#include <vector>          // For dynamic array (vector) data structure
#include <queue>           // For queue data structure (used in Dijkstra)
#include <stack>           // For stack data structure
#include <unordered_map>   // For hash map data structure (key-value pairs)
#include <algorithm>       // For algorithms like reverse, fill, etc.
#include <ctime>           // For time-related functions
#include <limits>          // For numeric limits (like INT_MAX)

// Using standard namespace to avoid writing std:: prefix
using namespace std;

// Define infinity constant for graph algorithms (maximum integer value)
const int INF = numeric_limits<int>::max();

// ===================================================================
// SECTION 1: USER SYSTEM
// ===================================================================
// This section handles user registration, login, and user management
// ===================================================================

// User class to store user information
class User {
public:
    // User's email address (used as unique identifier)
    string email;
    
    // User's password for authentication
    string password;
    
    // User's role: "passenger", "admin", or "manager"
    string role;

    // Default constructor (creates empty user)
    User() {
        // Initialize with empty strings
        email = "";
        password = "";
        role = "";
    }
    
    // Parameterized constructor (creates user with given values)
    User(string e, string p, string r) : email(e), password(p), role(r) {
        // Initialize email, password, and role with provided values
        // This is called member initialization list
    }
};

// UserSystem class manages all user operations
class UserSystem {
private:
    // Hash map to store all users (key: email, value: User object)
    unordered_map<string, User> users;
    
    // Filename where user data is stored
    string filename = "users.txt";

public:
    // Constructor: called when UserSystem object is created
    UserSystem() {
        // Print message to show system initialization
        cout << "[*] Initializing User System...\n";
        cout << "[*] Loading users from file: " << filename << "\n";
        
        // Load all users from file when system starts
        loadUsers();
        
        // Print confirmation message
        cout << "[+] User System initialized successfully!\n";
        cout << "[+] Total users loaded: " << users.size() << "\n\n";
    }

    // Function to load all users from the file
    void loadUsers() {
        // Clear existing users from memory
        users.clear();
        cout << "[*] Clearing existing user data from memory...\n";
        
        // Open file for reading
        ifstream file(filename);
        
        // Check if file opened successfully
        if (!file.is_open()) {
            // If file doesn't exist, create an empty file
            cout << "[!] File not found. Creating new file: " << filename << "\n";
            ofstream(filename).close();
            cout << "[+] New file created successfully.\n";
            return;
        }

        // Variables to store data read from file
        string e, p, r;
        int userCount = 0;
        
        // Read each line from file (email, password, role)
        while (file >> e >> p >> r) {
            // Create User object and store in hash map
            users[e] = User(e, p, r);
            userCount++;
            cout << "[*] Loaded user: " << e << " (Role: " << r << ")\n";
        }

        // Close the file
        file.close();
        cout << "[+] File closed. Total users loaded: " << userCount << "\n";
    }

    // Function to save all users to file
    bool saveAllUsers() {
        cout << "[*] Saving all users to file: " << filename << "\n";
        
        // Open file for writing (overwrites existing file)
        ofstream file(filename);
        
        // Check if file opened successfully
        if (!file.is_open()) {
            cout << "[!] Error: Cannot open file for writing!\n";
            return false;
        }

        int saveCount = 0;
        
        // Iterate through all users in the hash map
        for (auto &kv : users) {
            // Write user data to file (email password role)
            file << kv.second.email << " " << kv.second.password << " " << kv.second.role << "\n";
            saveCount++;
            cout << "[*] Saved user: " << kv.second.email << "\n";
        }

        // Close the file
        file.close();
        cout << "[+] File saved successfully. Total users saved: " << saveCount << "\n";
        return true;
    }
