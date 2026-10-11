#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

const int MAX = 50;

struct Date
{
private:
    int day;
    int month;
    int year;

public:
    Date()
    {
        day = 1;
        month = 1;
        year = 2000;
    }

    Date(int d, int m, int y)
    {
        day = 1;
        month = 1;
        year = 2000;
        setDate(d, m, y);
    }

    bool isValid(int d, int m, int y) const
    {
        if (y < 2000 || y > 2100)
        {
            return false;
        }
        if (m < 1 || m > 12)
        {
            return false;
        }

        int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        bool leap = false;
        if (y % 400 == 0)
        {
            leap = true;
        }
        else if (y % 4 == 0 && y % 100 != 0)
        {
            leap = true;
        }

        int maxDay = daysInMonth[m - 1];
        if (m == 2 && leap)
        {
            maxDay = 29;
        }

        if (d < 1 || d > maxDay)
        {
            return false;
        }
        return true;
    }

    bool setDate(int d, int m, int y)
    {
        if (isValid(d, m, y))
        {
            day = d;
            month = m;
            year = y;
            return true;
        }
        return false;
    }

    int getDay() const
    {
        return day;
    }

    int getMonth() const
    {
        return month;
    }

    int getYear() const
    {
        return year;
    }

    int compare(const Date &other) const
    {
        if (year < other.year) return -1;
        if (year > other.year) return 1;
        if (month < other.month) return -1;
        if (month > other.month) return 1;
        if (day < other.day) return -1;
        if (day > other.day) return 1;
        return 0;
    }

    string toString() const
    {
        ostringstream out;
        out << setfill('0') << setw(2) << day << "-"
            << setw(2) << month << "-"
            << setw(4) << year;
        return out.str();
    }

    void display() const
    {
        cout << toString();
    }
};

struct Supplier
{
private:
    string name;
    string city;

public:
    Supplier()
    {
        name = "Unknown";
        city = "Unknown";
    }

    Supplier(string n, string c)
    {
        name = "Unknown";
        city = "Unknown";
        setName(n);
        setCity(c);
    }

    bool setName(string n)
    {
        if (n == "")
        {
            return false;
        }
        name = n;
        return true;
    }

    bool setCity(string c)
    {
        if (c == "")
        {
            return false;
        }
        city = c;
        return true;
    }

    string getName() const
    {
        return name;
    }

    string getCity() const
    {
        return city;
    }

    void display() const
    {
        cout << name << " (" << city << ")";
    }
};

struct Medicine
{
private:
    int id;
    string name;
    Supplier supplier;
    Date expiry;
    int quantity;
    double unitPrice;

public:
    Medicine()
    {
        id = 0;
        name = "Unknown";
        quantity = 0;
        unitPrice = 0.0;
    }

    Medicine(int i, string n, Supplier s, Date e, int qty, double price)
    {
        id = 0;
        name = "Unknown";
        quantity = 0;
        unitPrice = 0.0;
        setId(i);
        setName(n);
        setSupplier(s);
        setExpiry(e);
        setQuantity(qty);
        setUnitPrice(price);
    }

    bool setId(int i)
    {
        if (i > 0)
        {
            id = i;
            return true;
        }
        return false;
    }

    bool setName(string n)
    {
        if (n == "")
        {
            return false;
        }
        name = n;
        return true;
    }

    void setSupplier(const Supplier &s)
    {
        supplier = s;
    }

    void setExpiry(const Date &e)
    {
        expiry = e;
    }

    bool setQuantity(int q)
    {
        if (q >= 0)
        {
            quantity = q;
            return true;
        }
        return false;
    }

    bool setUnitPrice(double p)
    {
        if (p > 0)
        {
            unitPrice = p;
            return true;
        }
        return false;
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getQuantity() const
    {
        return quantity;
    }

    double getUnitPrice() const
    {
        return unitPrice;
    }

    Supplier getSupplier() const
    {
        return supplier;
    }

    Date getExpiry() const
    {
        return expiry;
    }

    double stockValue() const
    {
        return quantity * unitPrice;
    }

    bool isExpired(const Date &today) const
    {
        if (expiry.compare(today) < 0)
        {
            return true;
        }
        return false;
    }

    bool isLowStock(int threshold) const
    {
        if (quantity < threshold)
        {
            return true;
        }
        return false;
    }

    bool sell(int qty)
    {
        if (qty > 0 && qty <= quantity)
        {
            quantity = quantity - qty;
            return true;
        }
        return false;
    }

    bool restock(int qty)
    {
        if (qty > 0)
        {
            quantity = quantity + qty;
            return true;
        }
        return false;
    }

    void displayRow() const
    {
        cout << fixed << setprecision(2);
        cout << left << setw(6) << id
             << setw(20) << name
             << setw(16) << supplier.getName()
             << setw(12) << expiry.toString()
             << right << setw(8) << quantity
             << setw(10) << unitPrice
             << setw(12) << stockValue() << endl;
    }
};

Date readDateFromUser()
{
    Date date;
    int d, m, y;
    bool done = false;

    while (!done)
    {
        cout << "Enter day: ";
        cin >> d;
        cout << "Enter month: ";
        cin >> m;
        cout << "Enter year: ";
        cin >> y;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter numbers only." << endl;
        }
        else if (date.setDate(d, m, y))
        {
            done = true;
        }
        else
        {
            cout << "Invalid date. Try again." << endl;
        }
    }
    return date;
}

bool isSameDay(Date a, Date b)
{
    if (a.compare(b) == 0)
    {
        return true;
    }
    return false;
}

int findById(const Medicine inv[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (inv[i].getId() == id)
        {
            return i;
        }
    }
    return -1;
}

int loadInventory(string fileName, Medicine inv[], string errorFile)
{
    ifstream inFile(fileName.c_str());
    if (!inFile)
    {
        cout << "Could not open stock file " << fileName << endl;
        return 0;
    }

    ofstream errFile(errorFile.c_str());
    if (!errFile)
    {
        cout << "Could not open error file " << errorFile << endl;
        inFile.close();
        return 0;
    }

    int count = 0;
    int recordNo = 0;
    int id, d, m, y, qty;
    double price;
    string name, supplierName, city;

    while (inFile >> id >> name >> supplierName >> city >> d >> m >> y >> qty >> price)
    {
        recordNo++;

        if (count >= MAX)
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") not loaded: array is full (MAX = " << MAX << ")." << endl;
            break;
        }

        Date expiry;

        if (id <= 0)
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") rejected: ID is not positive." << endl;
        }
        else if (!expiry.setDate(d, m, y))
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") rejected: invalid expiry date "
                    << setfill('0') << setw(2) << d << "-"
                    << setw(2) << m << "-"
                    << setw(4) << y << setfill(' ') << "." << endl;
        }
        else if (qty < 0)
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") rejected: negative quantity " << qty << "." << endl;
        }
        else if (price <= 0)
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") rejected: price is not positive." << endl;
        }
        else if (findById(inv, count, id) != -1)
        {
            errFile << "Record " << recordNo << " (ID " << id
                    << ") rejected: duplicate ID." << endl;
        }
        else
        {
            Supplier sup(supplierName, city);
            Medicine med(id, name, sup, expiry, qty, price);
            inv[count] = med;
            count++;
        }
    }

    inFile.close();
    errFile.close();
    return count;
}

void displayMedicine(const Medicine &m)
{
    cout << fixed << setprecision(2);
    cout << "ID          : " << m.getId() << endl;
    cout << "Name        : " << m.getName() << endl;
    cout << "Supplier    : ";
    m.getSupplier().display();
    cout << endl;
    cout << "Expiry date : ";
    m.getExpiry().display();
    cout << endl;
    cout << "Quantity    : " << m.getQuantity() << endl;
    cout << "Unit price  : " << m.getUnitPrice() << endl;
    cout << "Stock value : " << m.stockValue() << endl;
}

void printHeader()
{
    cout << left << setw(6) << "ID"
         << setw(20) << "Name"
         << setw(16) << "Supplier"
         << setw(12) << "Expiry"
         << right << setw(8) << "Qty"
         << setw(10) << "Price"
         << setw(12) << "Value" << endl;
    cout << string(84, '-') << endl;
}

void displayInventory(const Medicine inv[], int count)
{
    printHeader();
    for (int i = 0; i < count; i++)
    {
        inv[i].displayRow();
    }
}

bool restockMedicine(Medicine &m, int qty)
{
    return m.restock(qty);
}

Medicine getMostValuable(const Medicine inv[], int count)
{
    if (count == 0)
    {
        Medicine empty;
        return empty;
    }

    int best = 0;
    for (int i = 1; i < count; i++)
    {
        if (inv[i].stockValue() > inv[best].stockValue())
        {
            best = i;
        }
    }
    return inv[best];
}

void writeExpiryReport(const Medicine inv[], int count, const Date &today, string fileName)
{
    ofstream outFile(fileName.c_str());
    if (!outFile)
    {
        cout << "Could not open file " << fileName << endl;
        return;
    }

    outFile << "Expiry Report" << endl;
    outFile << "Today's date: " << today.toString() << endl;
    outFile << endl;

    for (int i = 0; i < count; i++)
    {
        if (inv[i].isExpired(today))
        {
            outFile << "EXPIRED: " << inv[i].getId() << " " << inv[i].getName()
                    << " (expiry " << inv[i].getExpiry().toString() << ")" << endl;
        }
        else if (isSameDay(inv[i].getExpiry(), today))
        {
            outFile << "EXPIRING TODAY: " << inv[i].getId() << " " << inv[i].getName()
                    << " (expiry " << inv[i].getExpiry().toString() << ")" << endl;
        }
    }

    outFile.close();
}

void closePrescription(ofstream &bill, double subtotal, int acceptedLines, double &grandTotal)
{
    if (acceptedLines == 0)
    {
        bill << "No items billed" << endl;
        bill << endl;
        return;
    }

    double discount = 0.0;
    if (subtotal > 1000)
    {
        discount = subtotal * 0.10;
    }
    double total = subtotal - discount;

    bill << "Subtotal: " << subtotal << " Discount: " << discount
         << " Total: " << total << endl;
    bill << endl;

    grandTotal = grandTotal + total;
}

void processPrescriptions(Medicine inv[], int count, const Date &today, string orderFile, string billFile)
{
    ifstream inFile(orderFile.c_str());
    if (!inFile)
    {
        cout << "Could not open order file " << orderFile << endl;
        return;
    }

    ofstream bill(billFile.c_str());
    if (!bill)
    {
        cout << "Could not open bill file " << billFile << endl;
        inFile.close();
        return;
    }

    bill << fixed << setprecision(2);

    int presNo, medId, qty;
    int currentNo = 0;
    bool started = false;
    double subtotal = 0.0;
    double grandTotal = 0.0;
    int acceptedInPrescription = 0;
    int acceptedLines = 0;
    int rejectedLines = 0;

    while (inFile >> presNo >> medId >> qty)
    {
        if (!started)
        {
            started = true;
            currentNo = presNo;
            bill << "Prescription #" << currentNo << endl;
        }
        else if (presNo != currentNo)
        {
            closePrescription(bill, subtotal, acceptedInPrescription, grandTotal);
            subtotal = 0.0;
            acceptedInPrescription = 0;
            currentNo = presNo;
            bill << "Prescription #" << currentNo << endl;
        }

        int index = findById(inv, count, medId);

        if (index == -1)
        {
            bill << medId << " REJECTED: medicine not found" << endl;
            rejectedLines++;
        }
        else if (inv[index].isExpired(today))
        {
            bill << medId << " " << inv[index].getName()
                 << " REJECTED: expired on " << inv[index].getExpiry().toString() << endl;
            rejectedLines++;
        }
        else if (qty > inv[index].getQuantity())
        {
            bill << medId << " " << inv[index].getName()
                 << " REJECTED: insufficient stock (available "
                 << inv[index].getQuantity() << ", requested " << qty << ")" << endl;
            rejectedLines++;
        }
        else if (!inv[index].sell(qty))
        {
            bill << medId << " " << inv[index].getName()
                 << " REJECTED: invalid quantity " << qty << endl;
            rejectedLines++;
        }
        else
        {
            double lineAmount = qty * inv[index].getUnitPrice();
            bill << medId << " " << inv[index].getName() << " " << qty
                 << " x " << inv[index].getUnitPrice() << " = " << lineAmount << endl;
            subtotal = subtotal + lineAmount;
            acceptedInPrescription++;
            acceptedLines++;
        }
    }

    if (started)
    {
        closePrescription(bill, subtotal, acceptedInPrescription, grandTotal);
    }

    bill << "Grand total: " << grandTotal << endl;
    bill << "Accepted lines: " << acceptedLines << endl;
    bill << "Rejected lines: " << rejectedLines << endl;

    inFile.close();
    bill.close();
}

void saveInventory(const Medicine inv[], int count, string fileName)
{
    ofstream outFile(fileName.c_str());
    if (!outFile)
    {
        cout << "Could not open file " << fileName << endl;
        return;
    }

    outFile << fixed << setprecision(2);

    for (int i = 0; i < count; i++)
    {
        outFile << inv[i].getId() << " "
                << inv[i].getName() << " "
                << inv[i].getSupplier().getName() << " "
                << inv[i].getSupplier().getCity() << " "
                << inv[i].getExpiry().getDay() << " "
                << inv[i].getExpiry().getMonth() << " "
                << inv[i].getExpiry().getYear() << " "
                << inv[i].getQuantity() << " "
                << inv[i].getUnitPrice() << endl;
    }

    outFile.close();
}

int countLines(string fileName)
{
    ifstream inFile(fileName.c_str());
    if (!inFile)
    {
        return 0;
    }

    int lines = 0;
    string line;
    while (getline(inFile, line))
    {
        lines++;
    }

    inFile.close();
    return lines;
}

int main()
{
    string inputFile;
    int attempts = 0;
    bool opened = false;

    while (attempts < 3 && !opened)
    {
        cout << "Enter stock file name: ";
        cin >> inputFile;

        ifstream test(inputFile.c_str());
        if (!test)
        {
            cout << "Cannot open file. Try again." << endl;
            attempts++;
        }
        else
        {
            test.close();
            opened = true;
        }
    }

    if (!opened)
    {
        cout << "Stock file could not be opened after 3 attempts. Program ending." << endl;
        return 0;
    }

    Medicine inventory[MAX];
    int count = loadInventory(inputFile, inventory, "errors.txt");
    int rejected = countLines("errors.txt");

    cout << count << " records loaded, " << rejected << " rejected (see errors.txt)" << endl;

    Date today = readDateFromUser();

    bool prescriptionsDone = false;
    bool running = true;

    while (running)
    {
        cout << endl;
        cout << "1. Display all medicines" << endl;
        cout << "2. Search medicine by ID" << endl;
        cout << "3. Restock a medicine" << endl;
        cout << "4. Change unit price" << endl;
        cout << "5. List low-stock medicines" << endl;
        cout << "6. Generate expired.txt" << endl;
        cout << "7. Process prescriptions" << endl;
        cout << "8. Show most valuable medicine" << endl;
        cout << "9. Save and exit" << endl;
        cout << "0. Exit without saving" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice)
        {
        case 1:
        {
            displayInventory(inventory, count);
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter medicine ID: ";
            cin >> id;
            int index = findById(inventory, count, id);
            if (index == -1)
            {
                cout << "Medicine not found." << endl;
            }
            else
            {
                displayMedicine(inventory[index]);
            }
            break;
        }
        case 3:
        {
            int id, qty;
            cout << "Enter medicine ID: ";
            cin >> id;
            int index = findById(inventory, count, id);
            if (index == -1)
            {
                cout << "Medicine not found." << endl;
            }
            else
            {
                cout << "Enter quantity to add: ";
                cin >> qty;
                if (restockMedicine(inventory[index], qty))
                {
                    cout << "Stock updated. New quantity: " << inventory[index].getQuantity() << endl;
                }
                else
                {
                    cout << "Quantity must be greater than zero." << endl;
                }
            }
            break;
        }
        case 4:
        {
            int id;
            double price;
            cout << "Enter medicine ID: ";
            cin >> id;
            int index = findById(inventory, count, id);
            if (index == -1)
            {
                cout << "Medicine not found." << endl;
            }
            else
            {
                cout << "Enter new unit price: ";
                cin >> price;
                if (inventory[index].setUnitPrice(price))
                {
                    cout << "Price updated." << endl;
                }
                else
                {
                    cout << "Price must be greater than zero." << endl;
                }
            }
            break;
        }
        case 5:
        {
            int threshold;
            bool found = false;
            cout << "Enter threshold: ";
            cin >> threshold;
            printHeader();
            for (int i = 0; i < count; i++)
            {
                if (inventory[i].isLowStock(threshold))
                {
                    inventory[i].displayRow();
                    found = true;
                }
            }
            if (!found)
            {
                cout << "No low-stock medicines." << endl;
            }
            break;
        }
        case 6:
        {
            writeExpiryReport(inventory, count, today, "expired.txt");
            cout << "expired.txt generated." << endl;
            break;
        }
        case 7:
        {
            if (prescriptionsDone)
            {
                cout << "Prescriptions already processed" << endl;
            }
            else
            {
                string orderFile;
                cout << "Enter order file name: ";
                cin >> orderFile;

                ifstream test(orderFile.c_str());
                if (!test)
                {
                    cout << "Cannot open order file." << endl;
                }
                else
                {
                    test.close();
                    processPrescriptions(inventory, count, today, orderFile, "bill.txt");
                    prescriptionsDone = true;
                    cout << "Prescriptions processed. See bill.txt" << endl;
                }
            }
            break;
        }
        case 8:
        {
            if (count == 0)
            {
                cout << "No medicines in stock." << endl;
            }
            else
            {
                Medicine best = getMostValuable(inventory, count);
                displayMedicine(best);
            }
            break;
        }
        case 9:
        {
            string outputFile;
            cout << "Enter output file name: ";
            cin >> outputFile;

            bool save = true;
            if (outputFile == inputFile)
            {
                char answer;
                cout << "Overwrite original file? (y/n) ";
                cin >> answer;
                if (answer != 'y' && answer != 'Y')
                {
                    save = false;
                }
            }

            if (save)
            {
                saveInventory(inventory, count, outputFile);
                cout << "Stock saved to " << outputFile << endl;
                running = false;
            }
            break;
        }
        case 0:
        {
            char answer;
            cout << "Unsaved changes will be lost. Exit? (y/n) ";
            cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                running = false;
            }
            break;
        }
        default:
        {
            cout << "Invalid choice" << endl;
            break;
        }
        }
    }

    return 0;
}