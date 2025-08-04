#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "picoshad2.h"

using namespace std;

bool userExists(const string& username)
{
    ifstream file("users.txt");
    string u, p;
    while (file >> u >> p) 
    {
        if (u == username) return true;
    }
    return false;
}

string hashPassword(const string& password)
{
    return picosha2::hash256_hex_string(password);
}

void registerUser()
{
    string username, password;

    cout<<"Enter a new username: ";
    cin>>username;

    if (username.empty() || password.empty())
    {
        cout << "Username and password must not be empty.\n";
        return;
    }

    if (userExists(username)) 
    {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout<<"Enter a password: ";
    cin>>password;

    string hashedPassword = hashPassword(password);
    ofstream file("users.txt", ios::app);
    file<<username<<" "<<password<< endl;

    cout<<"Registration successful!\n";
}

bool loginUser()
{
    string username, password;

    cout<<"Enter your username: ";
    cin>>username;
    cout<<"Enter your password: ";
    cin>>password;

    if (username.empty() || password.empty())
    {
        cout << "Username and password must not be empty.\n";
        return false;
    }
    string hashedPassword = hashPassword(password);
    
    ifstream file("users.txt");
    string u, p;

    while (file >> u >> p) 
    {
        if (u == username && p == password) {
            cout<<"Login successful!\n";
            return true;
        }
    }
    cout<<"Invalid username or password.\n";
    return false;
}

int main() 
{
    int choice;

    do {
        cout<<"\n====== Welcome ======\n";
        cout<<"1. Register\n";
        cout<<"2. Login\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) 
        {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}