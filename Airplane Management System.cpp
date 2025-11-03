#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
using namespace std;

// ------------------- Base Class -------------------
class Flight {
protected:
    string flightNumber;
    string airline;
    string origin;
    string destination;
    string status;
    string time;
    string runway;

public:
    Flight() {}
    Flight(string fno, string al, string org, string dest, string t)
        : flightNumber(fno), airline(al), origin(org), destination(dest), time(t) {
        status = "Scheduled";
        runway = "Not Assigned";
    }

    virtual void displayInfo() {
        cout << "\nFlight Number : " << flightNumber;
        cout << "\nAirline       : " << airline;
        cout << "\nFrom          : " << origin;
        cout << "\nTo            : " << destination;
        cout << "\nTime          : " << time;
        cout << "\nStatus        : " << status;
        cout << "\nRunway        : " << runway;
        cout << "\n-------------------------------------";
    }

    string getFlightNumber() { return flightNumber; }
    void setStatus(string s) { status = s; }
    void setRunway(string r) { runway = r; }
    string getStatus() { return status; }
};

// ------------------- Derived Class -------------------
class Weather {
    string condition;

public:
    Weather() {
        srand(time(0)); // seed random generator
        generateRandomCondition();
    }

    void generateRandomCondition() {
        string conditions[] = {"Clear", "Rainy", "Foggy", "Stormy"};
        condition = conditions[rand() % 4];
    }

    void showWeather() {
        // generate a new random weather condition each time
        generateRandomCondition();
        cout << "\n🌦️  Current Weather: " << condition << endl;

        if (condition == "Stormy" || condition == "Foggy") {
            cout << "⚠️  Warning: Some flights may experience delays.\n";
        } else if (condition == "Rainy") {
            cout << "☔ Moderate rain, flights operating with caution.\n";
        } else {
            cout << "✅ Weather is clear and safe for flight operations.\n";
        }
    }
};

// ------------------- Airport Management -------------------
class Airport {
    vector<Flight> flights;
    Weather weather;

public:
    void addFlight() {
        string fno, al, org, dest, time;
        cout << "\nEnter Flight Number: ";
        cin >> fno;
        cout << "Enter Airline: ";
        cin >> al;
        cout << "Enter Origin: ";
        cin >> org;
        cout << "Enter Destination: ";
        cin >> dest;
        cout << "Enter Arrival Time (HH:MM): ";
        cin >> time;

        Flight f(fno, al, org, dest, time);
        flights.push_back(f);
        cout << "\n✅ Flight added successfully!\n";
    }

    void showAllFlights() {
        if (flights.empty()) {
            cout << "\nNo flight records available.\n";
            return;
        }
        for (auto &f : flights)
            f.displayInfo();
    }

    void updateStatus() {
        string fno, newStatus;
        cout << "\nEnter Flight Number to update: ";
        cin >> fno;
        for (auto &f : flights) {
            if (f.getFlightNumber() == fno) {
                cout << "Enter new status (Arriving / Delayed / Landed): ";
                cin >> newStatus;
                f.setStatus(newStatus);
                cout << "✅ Status updated successfully!\n";
                return;
            }
        }
        cout << "❌ Flight not found!\n";
    }

    void assignRunway() {
        string fno, run;
        cout << "\nEnter Flight Number: ";
        cin >> fno;
        cout << "Enter Runway Number: ";
        cin >> run;

        for (auto &f : flights) {
            if (f.getFlightNumber() == fno) {
                f.setRunway(run);
                cout << "✅ Runway assigned successfully!\n";
                return;
            }
        }
        cout << "❌ Flight not found!\n";
    }

    void showWeatherNow() {
        weather.showWeather();
    }

    void saveData() {
        ofstream fout("flights.txt");
        for (auto &f : flights) {
            fout << f.getFlightNumber() << "," << f.getStatus() << "\n";
        }
        fout.close();
        cout << "\n💾 Data saved to file successfully!\n";
    }
};

// ------------------- Main Menu -------------------
int main() {
    Airport a;
    int choice;

    do {
        cout << "\n\n===== ✈️ AIRPLANE MANAGEMENT SYSTEM =====";
        cout << "\n1. Add New Flight";
        cout << "\n2. View All Flights";
        cout << "\n3. Update Flight Status";
        cout << "\n4. Assign Runway";
        cout << "\n5. Show Weather";
        cout << "\n6. Save Data";
        cout << "\n0. Exit";
        cout << "\n-------------------------------------";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: a.addFlight(); break;
            case 2: a.showAllFlights(); break;
            case 3: a.updateStatus(); break;
            case 4: a.assignRunway(); break;
            case 5: a.showWeatherNow(); break;
            case 6: a.saveData(); break;
            case 0:
                cout << "\nExiting... Thank you!\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 0);

    // 👇 Keeps console open until Enter is pressed
    cout << "\nPress Enter to close the program...";
    cin.ignore();
    cin.get();

    return 0;
}