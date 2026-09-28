#include <iostream>
#include <vector>
#include <string>

using namespace std;


// Base class
class Vehicle {

protected:
    int id;
    string brand;
    double rentPerDay;
    bool available;

public:

    Vehicle(int id, string brand, double rentPerDay) {

        this->id = id;
        this->brand = brand;
        this->rentPerDay = rentPerDay;
        this->available = true;
    }

    virtual void display() {

        cout << "ID: " << id << endl;
        cout << "Brand: " << brand << endl;
        cout << "Rent per day: " << rentPerDay << endl;
        cout << "Status: " << (available ? "Available" : "Rented") << endl;
    }

    int getId() {
        return id;
    }

    bool isAvailable() {
        return available;
    }

    void rentVehicle() {
        available = false;
    }

    void returnVehicle() {
        available = true;
    }

    double getRentPerDay() {
        return rentPerDay;
    }

    virtual ~Vehicle() {}
};


// Derived class - Car
class Car : public Vehicle {

private:
    int seats;

public:

    Car(int id, string brand, double rentPerDay, int seats)
        : Vehicle(id, brand, rentPerDay) {

        this->seats = seats;
    }

    void display() override {

        cout << "\nVehicle Type: Car" << endl;
        cout << "ID: " << id << endl;
        cout << "Brand: " << brand << endl;
        cout << "Seats: " << seats << endl;
        cout << "Rent per day: " << rentPerDay << endl;
        cout << "Status: "
             << (available ? "Available" : "Rented")
             << endl;
    }
};


// Derived class - Bike
class Bike : public Vehicle {

private:
    bool helmetIncluded;

public:

    Bike(int id, string brand, double rentPerDay, bool helmetIncluded)
        : Vehicle(id, brand, rentPerDay) {

        this->helmetIncluded = helmetIncluded;
    }

    void display() override {

        cout << "\nVehicle Type: Bike" << endl;
        cout << "ID: " << id << endl;
        cout << "Brand: " << brand << endl;
        cout << "Helmet Included: "
             << (helmetIncluded ? "Yes" : "No")
             << endl;
        cout << "Rent per day: " << rentPerDay << endl;
        cout << "Status: "
             << (available ? "Available" : "Rented")
             << endl;
    }
};


// Find vehicle using ID
Vehicle* findVehicle(vector<Vehicle*>& vehicles, int id) {

    for (Vehicle* vehicle : vehicles) {

        if (vehicle->getId() == id) {
            return vehicle;
        }
    }

    return nullptr;
}


// Add vehicle
void addVehicle(vector<Vehicle*>& vehicles) {

    int type;
    int id;
    string brand;
    double rent;

    cout << "\n1. Car" << endl;
    cout << "2. Bike" << endl;

    cout << "Enter vehicle type: ";
    cin >> type;

    cout << "Enter vehicle ID: ";
    cin >> id;

    cout << "Enter brand: ";
    cin >> brand;

    cout << "Enter rent per day: ";
    cin >> rent;


    if (type == 1) {

        int seats;

        cout << "Enter number of seats: ";
        cin >> seats;

        vehicles.push_back(
            new Car(id, brand, rent, seats)
        );

    }

    else if (type == 2) {

        int helmet;

        cout << "Helmet included? (1 = Yes, 0 = No): ";
        cin >> helmet;

        vehicles.push_back(
            new Bike(id, brand, rent, helmet)
        );
    }

    else {

        cout << "Invalid vehicle type!" << endl;
        return;
    }

    cout << "Vehicle added successfully!" << endl;
}


// View vehicles
void viewVehicles(vector<Vehicle*>& vehicles) {

    if (vehicles.empty()) {

        cout << "\nNo vehicles available!" << endl;
        return;
    }

    cout << "\n===== ALL VEHICLES =====" << endl;

    for (Vehicle* vehicle : vehicles) {

        vehicle->display();

        cout << "------------------------" << endl;
    }
}


// Search vehicle
void searchVehicle(vector<Vehicle*>& vehicles) {

    int id;

    cout << "Enter vehicle ID: ";
    cin >> id;

    Vehicle* vehicle = findVehicle(vehicles, id);

    if (vehicle != nullptr) {

        cout << "\nVehicle found!" << endl;

        vehicle->display();
    }

    else {

        cout << "Vehicle not found!" << endl;
    }
}


// Rent vehicle
void rentVehicle(vector<Vehicle*>& vehicles) {

    int id;

    cout << "Enter vehicle ID to rent: ";
    cin >> id;

    Vehicle* vehicle = findVehicle(vehicles, id);

    if (vehicle == nullptr) {

        cout << "Vehicle not found!" << endl;
        return;
    }

    if (!vehicle->isAvailable()) {

        cout << "Vehicle is already rented!" << endl;
        return;
    }

    int days;

    cout << "Enter number of rental days: ";
    cin >> days;

    double cost = vehicle->getRentPerDay() * days;

    vehicle->rentVehicle();

    cout << "\nVehicle rented successfully!" << endl;
    cout << "Total rental cost: " << cost << endl;
}


// Return vehicle
void returnVehicle(vector<Vehicle*>& vehicles) {

    int id;

    cout << "Enter vehicle ID to return: ";
    cin >> id;

    Vehicle* vehicle = findVehicle(vehicles, id);

    if (vehicle == nullptr) {

        cout << "Vehicle not found!" << endl;
        return;
    }

    if (vehicle->isAvailable()) {

        cout << "This vehicle is not currently rented!" << endl;
        return;
    }

    vehicle->returnVehicle();

    cout << "Vehicle returned successfully!" << endl;
}


// Main function
int main() {

    vector<Vehicle*> vehicles;

    int choice;

    do {

        cout << "\n\n===== VEHICLE RENTAL SYSTEM =====" << endl;

        cout << "1. Add Vehicle" << endl;
        cout << "2. View Vehicles" << endl;
        cout << "3. Search Vehicle" << endl;
        cout << "4. Rent Vehicle" << endl;
        cout << "5. Return Vehicle" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {

            case 1:
                addVehicle(vehicles);
                break;

            case 2:
                viewVehicles(vehicles);
                break;

            case 3:
                searchVehicle(vehicles);
                break;

            case 4:
                rentVehicle(vehicles);
                break;

            case 5:
                returnVehicle(vehicles);
                break;

            case 6:
                cout << "Thank you for using Vehicle Rental System!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
        }

    } while (choice != 6);


    // Free dynamically allocated memory
    for (Vehicle* vehicle : vehicles) {

        delete vehicle;
    }

    return 0;
}