/*
Jared Morris
Lab 4
*/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct Inventory{
    char desc[30];
    int qty;
    double wholeSaleCost;
};

// Function prototypes
void addRecord(fstream &);
void viewRecord(fstream &);
void changeRecord(fstream &);

int main(){
    fstream inventoryFile;
    int choice;
    cout << setprecision(2) << fixed;

    do{
        // Display the menu.
        cout << "\n1. Add a new record\n";
		cout << "2. View an existing record by record number\n";
		cout << "3. Change an existing record\n";
		cout << "4. Exit\n\n";

        do{
            cout << "Enter your choice (1-4): ";
            cin >> choice;
        } while(choice < 1 || choice > 4);

        // Process the selection
        switch(choice){
            // Choice 1 is to add a record
            case 1: 
                addRecord(inventoryFile);
                break;
            // Choice 2 is to view a record
            case 2:
                viewRecord(inventoryFile);
                break;
            // Choice 3 is to change a record
            case 3:
                changeRecord(inventoryFile);
        }
    }while(choice != 4);
    
    system("pause");
    return 0;
}

// Get input from the user and write the input to a file
void addRecord(fstream &file){
    Inventory item;
   file.open("inventory.dat", ios::out | ios::app | ios::binary);
   cin.ignore();

    // Get user input and validate it
    cout << "Enter the following inventory data: \n";

    cout << "Description: ";
    cin.get(item.desc, 30);
    

    do{
        cout << "Quantity: ";
        cin >> item.qty;
        if(item.qty <= 0){
            cout << "Please try again...\n";
        }
        cin.ignore();
    } while(item.qty <= 0);

    do {
        cout << "Retail price: ";
        cin >> item.wholeSaleCost;
        if(item.wholeSaleCost <= 0){
            cout << "Please try again...\n";
        }
        cin.ignore();
    } while(item.wholeSaleCost <= 0);

    // Write the structure to the file
    file.write(reinterpret_cast<char *>(&item), sizeof(item));

    file.close();
    cout << "Record written to file\n\n";
}

// Ask the user for an item they want (array notation) and display that entry from the file
void viewRecord(fstream &file){
    Inventory item;
    file.open("inventory.dat", ios::in | ios::binary);
    int choice;

    cout << "\nEnter the record number of the item: ";
    cin >> choice;
    file.seekg((long)sizeof(Inventory) * choice, ios::beg);
    file.read(reinterpret_cast<char *>(&item), sizeof(item));

    cout << "Description: " << item.desc << endl;
    cout << "Quantity: " << item.qty << endl;
    cout << "Retail Price: " << item.wholeSaleCost << endl;

    file.close();
}

// Ask the user for the item they want to change (array notation) and overwrite that entry with new input data
void changeRecord(fstream &file){
    Inventory item;
    file.open("inventory.dat", ios::in | ios::out | ios::binary);
    int choice;

    // Get placement of record
    cout << "\nEnter the record number of the item: ";
    cin >> choice;

    // Display current data
    cout << "Current record contents: \n";
    file.seekg((long)sizeof(Inventory) * choice, ios::beg);
    file.read(reinterpret_cast<char *>(&item), sizeof(item));

    cout << "Description: " << item.desc << endl;
    cout << "Quantity: " << item.qty << endl;
    cout << "Retail Price: " << item.wholeSaleCost << endl;

    // Record new data
    cout << "\nEnter the new data: \n";
    cout << "Description: ";
    cin.ignore();
    cin.get(item.desc, 30);

    do{
        cout << "Quantity: ";
        cin >> item.qty;
        if(item.qty <= 0){
            cout << "Please try again...\n";
        }
    } while(item.qty <= 0);

    do {
        cout << "Retail price: ";
        cin >> item.wholeSaleCost;
        if(item.wholeSaleCost <= 0){
            cout << "Please try again...\n";
        }
    } while(item.wholeSaleCost <= 0);

    // Overrite data
    file.seekp(choice * sizeof(item), ios::beg);
    file.write(reinterpret_cast<char *>(&item), sizeof(item));
    file.close();
}