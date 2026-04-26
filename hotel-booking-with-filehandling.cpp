#include <iostream>
#include <windows.h>  //for colour output 
#include <string>
#include <limits>
#include <sstream>
#include <cctype> // For isalpha() function       
#include <cstdlib> // For system() function
#include <fstream> // For file handling

using namespace std;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

const int NUM_ROOMS = 10;
const int NUM_MEETING_ROOMS = 4;

// Enum to represent room categories
enum RoomCategory { ECONOMICAL, LUXURY };

// Class to represent a room 
class Room {
public:
    int roomNumber;
    bool isBooked;
    RoomCategory category;
    string guestName;
    string guestCNIC;
    string guestContact;
    
    string checkInDate;
    string checkOutDate;
    bool isMorningBooking;
    double price;

    Room(int number = 0, RoomCategory cat = ECONOMICAL, double roomPrice = 0.0)
        : roomNumber(number), isBooked(false), category(cat), isMorningBooking(true), price(roomPrice) {}

    // Function to display room information
    void displayInfo() const {
        cout << "Room " << roomNumber << " (";
        if (category == ECONOMICAL) {
            cout << "Economical";
        } else {
            cout << "Luxury";
        }
        cout << ", Price: $" << price << "): ";
        if (isBooked) {
            cout << "Booked" << endl;
            cout << "  Guest: " << guestName << endl;
            cout << "  CNIC: " << guestCNIC << endl;
            cout << "  Contact: " << guestContact << endl;
            cout << "  Check-in: " << checkInDate << endl;
            cout << "  Check-out: " << checkOutDate << endl;
            cout << "  Time: ";
            if (isMorningBooking) {
                cout << "Morning";
            } else {
                cout << "Evening";
            }
            cout << endl;
        } else {
            cout << "Available" << endl;
        }
    }

    // Function to book a room
    void bookRoom(const string &name, const string &cnic, const string &contact, const string &checkIn, const string &checkOut, bool morningBooking) {
        guestName = name;
        guestCNIC = cnic;
        guestContact = contact;
        checkInDate = checkIn;
        checkOutDate = checkOut;
        isMorningBooking = morningBooking;
        isBooked = true;
    }

    // Function to cancel a booking
    void cancelBooking() {
        guestName = "";
        guestCNIC = "";
        guestContact = "";
        checkInDate = "";
        checkOutDate = "";
        isBooked = false;
        isMorningBooking = true;
    }

    // Save room data to file
    void saveToFile(ofstream &outFile) const {
        outFile << isBooked << "\n";
        outFile << guestName << "\n";
        outFile << guestCNIC << "\n";
        outFile << guestContact << "\n";
        outFile << checkInDate << "\n";
        outFile << checkOutDate << "\n";
        outFile << isMorningBooking << "\n";
    }

    // Load room data from file
    void loadFromFile(ifstream &inFile) {
        string line;
        getline(inFile, line); isBooked = (line == "1");
        getline(inFile, guestName);
        getline(inFile, guestCNIC);
        getline(inFile, guestContact);
        getline(inFile, checkInDate);
        getline(inFile, checkOutDate);
        getline(inFile, line); isMorningBooking = (line == "1");
    }
};

// Class to represent a meeting room
class MeetingRoom {
public:
    int roomNumber;
    bool isBooked;
    string bookedBy;
    int bookedHours;
    string checkInDate;
    string checkOutDate;
    double pricePerHour;

    MeetingRoom(int number = 0, double price = 0.0) : roomNumber(number), isBooked(false), bookedHours(0), pricePerHour(price) {}

    // Function to display meeting room information
    void displayInfo() const {
        cout << "Meeting Room " << roomNumber << " (Price per hour: $" << pricePerHour << "): ";
        if (isBooked) {
            cout << "Booked" << endl;
            cout << "  Booked by: " << bookedBy << endl;
            cout << "  Hours: " << bookedHours << endl;
            cout << "  Check-in: " << checkInDate << endl;
            cout << "  Check-out: " << checkOutDate << endl;
        } else {
            cout << "Available" << endl;
        }
    } 

    // Function to book a meeting room
    void bookRoom(const string &name, int hours, const string &checkIn, const string &checkOut) {
        bookedBy = name;
        bookedHours = hours;
        checkInDate = checkIn;
        checkOutDate = checkOut;
        isBooked = true;
    }

    // Function to cancel a booking
    void cancelBooking() {
        bookedBy = "";
        bookedHours = 0;
        checkInDate = "";
        checkOutDate = "";
        isBooked = false;
    }

    // Save meeting room data to file
    void saveToFile(ofstream &outFile) const {
        outFile << isBooked << "\n";
        outFile << bookedBy << "\n";
        outFile << bookedHours << "\n";
        outFile << checkInDate << "\n";
        outFile << checkOutDate << "\n";
    }

    // Load meeting room data from file
    void loadFromFile(ifstream &inFile) {
        string line;
        getline(inFile, line); isBooked = (line == "1");
        getline(inFile, bookedBy);
        getline(inFile, line); bookedHours = stoi(line);
        getline(inFile, checkInDate);
        getline(inFile, checkOutDate);
    }
};

// ---- File Handling Functions ----

// Save all data to files
void saveData(const Room rooms[], const MeetingRoom meetingRooms[]) {
    // Save rooms
    ofstream roomFile("rooms.txt");
    if (roomFile.is_open()) {
        for (int i = 0; i < NUM_ROOMS; ++i) {
            rooms[i].saveToFile(roomFile);
        }
        roomFile.close();
    }

    // Save meeting rooms
    ofstream meetingFile("meeting_rooms.txt");
    if (meetingFile.is_open()) {
        for (int i = 0; i < NUM_MEETING_ROOMS; ++i) {
            meetingRooms[i].saveToFile(meetingFile);
        }
        meetingFile.close();
    }
}

// Load all data from files
void loadData(Room rooms[], MeetingRoom meetingRooms[]) {
    // Load rooms
    ifstream roomFile("rooms.txt");
    if (roomFile.is_open()) {
        for (int i = 0; i < NUM_ROOMS; ++i) {
            rooms[i].loadFromFile(roomFile);
        }
        roomFile.close();
    }

    // Load meeting rooms
    ifstream meetingFile("meeting_rooms.txt");
    if (meetingFile.is_open()) {
        for (int i = 0; i < NUM_MEETING_ROOMS; ++i) {
            meetingRooms[i].loadFromFile(meetingFile);
        }
        meetingFile.close();
    }
}

// ---- End File Handling Functions ----

// Function prototypes
void bookRoom(Room rooms[], MeetingRoom meetingRooms[]);
void bookMeetingRoom(MeetingRoom meetingRooms[], Room rooms[]);
void cancelBooking(Room rooms[], MeetingRoom meetingRooms[]);
void displayBookedRooms(const Room rooms[], const MeetingRoom meetingRooms[]);
void displayRoomAvailability(const Room rooms[], const MeetingRoom meetingRooms[]);
void displayRoomDetails(const Room rooms[], const MeetingRoom meetingRooms[]);
void printMenu();
int getValidIntInput();
bool isValidDate(const string &date);
bool isValidNumericInput(const string &input);
bool isValidNameInput(const string &input);
void waitForEnter();

int main() {
    Room rooms[NUM_ROOMS] = {
        Room(1, ECONOMICAL, 50.0), Room(2, ECONOMICAL, 50.0), Room(3, ECONOMICAL, 50.0), Room(4, ECONOMICAL, 50.0), Room(5, ECONOMICAL, 50.0),
        Room(6, LUXURY, 150.0), Room(7, LUXURY, 150.0), Room(8, LUXURY, 150.0), Room(9, LUXURY, 150.0), Room(10, LUXURY, 150.0)
    };

    MeetingRoom meetingRooms[NUM_MEETING_ROOMS] = { MeetingRoom(1, 20.0), MeetingRoom(2, 30.0), MeetingRoom(3, 40.0), MeetingRoom(4, 50.0) };

    // Load saved data when program starts
    loadData(rooms, meetingRooms);

    int choice;
    do {
        printMenu();
        choice = getValidIntInput();

        switch (choice) {
            case 1:
                bookRoom(rooms, meetingRooms);
                saveData(rooms, meetingRooms); // Save after booking
                break;
            case 2:
                bookMeetingRoom(meetingRooms, rooms);
                saveData(rooms, meetingRooms); // Save after booking
                break;
            case 3:
                cancelBooking(rooms, meetingRooms);
                saveData(rooms, meetingRooms); // Save after cancellation
                break;
            case 4:
                displayBookedRooms(rooms, meetingRooms);
                break;
            case 5:
                displayRoomAvailability(rooms, meetingRooms);
                break;
            case 6:
                displayRoomDetails(rooms, meetingRooms);
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                SetColor(12); // Setting text color to red
                cout << "Invalid choice. Please enter a valid number.\n";
                SetColor(7);
        }

        waitForEnter();

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

    } while (choice != 7);

    return 0;
}

// Function to book a room
void bookRoom(Room rooms[], MeetingRoom meetingRooms[]) {
    string name, cnic, contact, checkInDate, checkOutDate;
    int roomNum, categoryChoice;
    char timeChoice;

    cout << "Enter guest name: ";
    cin.ignore();
    getline(cin, name);
    while (!isValidNameInput(name)) {
    	SetColor(12); // Setting text color to red
        cout << "Invalid name. Please enter a valid name: ";
        SetColor(7); // Setting text color to red
        getline(cin, name);
    }

    cout << "Enter guest CNIC: ";  
    cin >> cnic;
    while (!isValidNumericInput(cnic)) {
    	SetColor(12); // Setting text color to red
        cout << "Invalid CNIC. Please enter a valid numeric CNIC: ";
        SetColor(7); 
        cin >> cnic;
    }

    cout << "Enter guest contact number: ";  
    cin >> contact;
    while (!isValidNumericInput(contact)) {
    	SetColor(12); // Setting text color to red
        cout << "Invalid contact number. Please enter a valid numeric contact number: ";
        SetColor(7); 
        cin >> contact;
    }

    cout << "Choose room category: \n";
    cout << "1. Economical\n";
    cout << "2. Luxury\n";
    cout << "Enter choice: ";
    categoryChoice = getValidIntInput();

    if (categoryChoice != 1 && categoryChoice != 2) {
    		SetColor(12);
        cout << "Invalid category choice. Please enter 1 for Economical or 2 for Luxury.\n";
        	SetColor(7);
        return;
    }

    RoomCategory selectedCategory = (categoryChoice == 1) ? ECONOMICAL : LUXURY;

    cout << "Available rooms (" << (selectedCategory == ECONOMICAL ? "Economical" : "Luxury") << "):\n";
    for (int i = 0; i < NUM_ROOMS; ++i) {
        if (!rooms[i].isBooked && rooms[i].category == selectedCategory) {
            cout << "Room " << rooms[i].roomNumber << " (Price: $" << rooms[i].price << ")\n";
        }
    }

    cout << "Enter room number (choose from available rooms): ";
    roomNum = getValidIntInput();

    if (roomNum < 1 || roomNum > NUM_ROOMS || rooms[roomNum - 1].category != selectedCategory) {
    		SetColor(12);
        cout << "Invalid room number. Please enter a valid room number.\n";
        	SetColor(7);
        return;
    }

    if (rooms[roomNum - 1].isBooked) {
        cout << "Room " << roomNum << " is already booked.\n";
        return;
    }

    cin.ignore();
    cout << "Enter check-in date (YYYY-MM-DD): ";
    getline(cin, checkInDate);
    while (!isValidDate(checkInDate)) {
    		SetColor(12);
        cout << "Invalid date format. Please enter a valid date (YYYY-MM-DD): ";
        	SetColor(7);
        getline(cin, checkInDate);
    }

    cout << "Enter check-out date (YYYY-MM-DD) or type 'not yet' if not checked out: ";
    getline(cin, checkOutDate);
    while (!isValidDate(checkOutDate) && checkOutDate != "not yet") {
    		SetColor(12);
        cout << "Invalid date format. Please enter a valid date (YYYY-MM-DD), or type 'not yet' if not checked out: ";
        	SetColor(7);
        getline(cin, checkOutDate);
    }

    cout << "Choose booking time (M for Morning, E for Evening): ";
    cin >> timeChoice;
    bool morningBooking = (timeChoice == 'M' || timeChoice == 'm');

    rooms[roomNum - 1].bookRoom(name, cnic, contact, checkInDate, checkOutDate, morningBooking);
	    SetColor(10);
    cout << "Room " << roomNum << " has been successfully booked.\n";
    	SetColor(7);
}


// Function to book a meeting room
void bookMeetingRoom(MeetingRoom meetingRooms[], Room rooms[]) {
    string name, checkInDate, checkOutDate;
    int roomNum, hours;

    cout << "Enter guest name: ";
    cin.ignore();
    getline(cin, name);
    while (!isValidNameInput(name)) {
        SetColor(12); // Setting text color to red
        cout << "Invalid name. Please enter a valid name: ";
        SetColor(7); // Setting text color to red
        getline(cin, name);
    }

    cout << "Available meeting rooms:\n";
    bool foundAvailable = false;
    for (int i = 0; i < NUM_MEETING_ROOMS; ++i) {
        if (!meetingRooms[i].isBooked) {
            cout << "Meeting Room " << meetingRooms[i].roomNumber << " (Price per hour: $" << meetingRooms[i].pricePerHour << ")\n";
            foundAvailable = true;
        }
    }
    if (!foundAvailable) {
        cout << "No available meeting rooms.\n";
        return;
    }

    cout << "Enter meeting room number to book: ";
    roomNum = getValidIntInput();

    if (roomNum < 1 || roomNum > NUM_MEETING_ROOMS || meetingRooms[roomNum - 1].isBooked) {
        SetColor(12); // Setting text color to red
        cout << "Invalid meeting room number or room already booked.\n";
        SetColor(7);
        return;
    }

    cout << "Enter number of hours for booking: ";
    hours = getValidIntInput();
    while (hours <= 0) {
        SetColor(12); // Setting text color to red
        cout << "Invalid input. Please enter a valid number of hours: ";
        SetColor(7);
        hours = getValidIntInput();
    }

    cin.ignore();
    cout << "Enter check-in date (YYYY-MM-DD): ";
    getline(cin, checkInDate);
    while (!isValidDate(checkInDate)) {
    		SetColor(12);
        cout << "Invalid date format. Please enter a valid date (YYYY-MM-DD): ";
        	SetColor(7);
        getline(cin, checkInDate);
    }

    cout << "Enter check-out date (YYYY-MM-DD) or type 'not yet' if not checked out: ";
    getline(cin, checkOutDate);
    while (!isValidDate(checkOutDate) && checkOutDate != "not yet") {
    		SetColor(12);
        cout << "Invalid date format. Please enter a valid date (YYYY-MM-DD), or type 'not yet' if not checked out: ";
        	SetColor(7);
        getline(cin, checkOutDate);
    }

    meetingRooms[roomNum - 1].bookRoom(name, hours, checkInDate, checkOutDate);

    SetColor(10); // Setting text color to green
    cout << "Meeting Room " << roomNum << " booked successfully!\n";
    SetColor(7);
}

// Function to cancel a booking
void cancelBooking(Room rooms[], MeetingRoom meetingRooms[]) {
    int roomNum;

    cout << "Enter room number to cancel booking: ";
    roomNum = getValidIntInput();

    if (roomNum >= 1 && roomNum <= NUM_ROOMS && rooms[roomNum - 1].isBooked) {
        rooms[roomNum - 1].cancelBooking();
        SetColor(10); // Setting text color to green
        cout << "Booking for Room " << roomNum << " canceled successfully!\n";
        SetColor(7);
    } else if (roomNum >= 1 && roomNum <= NUM_MEETING_ROOMS && meetingRooms[roomNum - 1].isBooked) {
        meetingRooms[roomNum - 1].cancelBooking();
        SetColor(10); // Setting text color to green
        cout << "Booking for Meeting Room " << roomNum << " canceled successfully!\n";
        SetColor(7);
    } else {
        SetColor(12); // Setting text color to red
        cout << "Invalid room number or room not booked.\n";
        SetColor(7);
    }
}

// Function to display booked rooms
void displayBookedRooms(const Room rooms[], const MeetingRoom meetingRooms[]) {
    bool foundBooked = false;

    cout << "Booked Rooms:\n";
    for (int i = 0; i < NUM_ROOMS; ++i) {
        if (rooms[i].isBooked) {
            rooms[i].displayInfo();
            foundBooked = true;
        }
    }

    cout << "Booked Meeting Rooms:\n";
    for (int i = 0; i < NUM_MEETING_ROOMS; ++i) {
        if (meetingRooms[i].isBooked) {
            meetingRooms[i].displayInfo();
            foundBooked = true;
        }
    }

    if (!foundBooked) {
        cout << "No rooms or meeting rooms are currently booked.\n";
    }
}

// Function to display room availability
void displayRoomAvailability(const Room rooms[], const MeetingRoom meetingRooms[]) {
    cout << "Room Availability:\n";
    for (int i = 0; i < NUM_ROOMS; ++i) {
        cout << "Room " << rooms[i].roomNumber << " (";
        if (rooms[i].category == ECONOMICAL) {
            cout << "Economical";
        } else {
            cout << "Luxury";
        }
        cout << "): ";
        if (rooms[i].isBooked) {
            cout << "Booked\n";
        } else {
            cout << "Available\n";
        }
    }

    cout << "\nMeeting Room Availability:\n";
    for (int i = 0; i < NUM_MEETING_ROOMS; ++i) {
        cout << "Meeting Room " << meetingRooms[i].roomNumber << ": ";
        if (meetingRooms[i].isBooked) {
            cout << "Booked\n";
        } else {
            cout << "Available\n";
        }
    }
}

// Function to display detailed room information
void displayRoomDetails(const Room rooms[], const MeetingRoom meetingRooms[]) {
    int roomNum;

    cout << "Enter room number for details: ";
    roomNum = getValidIntInput();

    if (roomNum >= 1 && roomNum <= NUM_ROOMS) {
        rooms[roomNum - 1].displayInfo();
    } else if (roomNum >= 1 && roomNum <= NUM_MEETING_ROOMS) {
        meetingRooms[roomNum - 1].displayInfo();
    } else {
        SetColor(12); // Setting text color to red
        cout << "Invalid room number.\n";
        SetColor(7);
    }
}

// Function to print the menu
void printMenu() {
	cout<<endl;
	SetColor(3); // Setting text color to red
    cout << "........................................................................HOTEL BOOKING SYSTEM .............................................................................\n";
    cout<<"___________________________________________________________________________________________________________________________________________________________________________"<<endl;
    SetColor(7); // reset
    cout <<"                                                                        1. Book a room\n";
    cout <<"                                                                        2. Book a meeting room\n";
    cout <<"                                                                        3. Cancel booking\n";
    cout <<"                                                                        4. Display booked rooms\n";
    cout <<"                                                                        5. Display room availability\n";
    cout <<"                                                                        6. Display room details\n";
    cout <<"                                                                        7. Exit\n";
    	SetColor(3);
    cout<<"____________________________________________________________________________________________________________________________________________________________________________"<<endl;
    	SetColor(7);
    cout <<".Enter your choice: ";
}

// Function to get a valid integer input
int getValidIntInput() {
    int choice;
    while (!(cin >> choice) || cin.peek() != '\n') {
        SetColor(12); // Setting text color to red
        cout << "Invalid input. Please enter a valid number: ";
        SetColor(7);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

// Function to check if a string is a valid date in YYYY-MM-DD format
bool isValidDate(const string &date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            continue;
        }
        if (!isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

// Function to check if a string consists of numeric characters only
bool isValidNumericInput(const string &input) {
    for (char ch : input) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

// Function to check if a string consists of alphabetic characters only
bool isValidNameInput(const string &input) {
    for (char ch : input) {
        if (!isalpha(ch) && ch != ' ') {
            return false;
        }
    }
    return true;
}

// Function to wait for user to press enter
void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}
