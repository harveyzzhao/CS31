//GOAL: create a mini-rental shop

#include <iostream>
#include <string>

using namespace std;

int main() {
	//declare all input values
	int odo1;
	int odo2;
	int rentlength;
	string customer;
	char luxstring;
	bool luxbool;
	int month;
	int mileage;
	double rent;

	//take in the inputs
	cout << "Odometer at start: ";
	cin >> odo1;
	if (odo1 < 0)
	{
		cout << "---\n";
		cout << "The starting odometer reading must not be negative.\n";
		return 1;
	}
	cout << endl;

	//get odometer at end
	cout << "Odometer at end: ";
	cin >> odo2;
	if (odo1 > odo2)
	{
		cout << "---\n";
		cout << "The ending odometer reading must be at least as large as the starting reading.\n";
		return 1;
	}
	cout << endl;

	//get rental days
	cout << "Rental days: ";
	cin >> rentlength;
	if (rentlength <= 0)
	{
		cout << "---\n";
		cout << "The number of rental days must be positive.\n";
		return 1;
	}
	cout << endl;

	//ignore the backslash new line symbol so getline() can start
	cin.ignore(10000, '\n');
	cout << "Customer name: ";
	getline(cin, customer);
	if (customer == "") {
		cout << "---\n";
		cout << "You must enter a customer name.\n";
		return 1;
	}
	cout << endl;

	//get the boolean if the customer rents out a luxury car or not;
	cout << "Luxury car? (y/n): ";
	cin >> luxstring;

	if (luxstring == 'y') {
		luxbool = true;
	}
	else if (luxstring == 'n') {
		luxbool = false;
	}
	else {
		cout << "---\n";
		cout << "You must enter y or n.\n";
		return 1;
	}
	cout << endl;

	//get the month
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;
	if (month < 1 || month > 12)
	{
		cout << "---\n";
		cout << "The month number must be in the range 1 through 12.\n";
		return 1;
	}
	cout << endl;

	//get rent
	cout << "---" << endl;
	mileage = odo2 - odo1;

	//reset precision for the final rent
	cout.setf(ios::fixed);
	cout.precision(2);
	if (mileage <= 100) {
		rent = 43.0 * rentlength + 0.27 * mileage;
	}

	else {
		rent = 43.0 * rentlength + 27.0;
		if (month <= 3 || month == 12) {
			if (mileage <= 500 && mileage > 100) {
				rent += 0.27 * (mileage - 100);
			}

			else
			{
				rent += (0.27 * 400);
				rent += 0.17 * (mileage - 500);
			}
		}

		if (month > 3 && month < 12) {
			if (mileage <= 500 && mileage > 100) {
				rent += (0.21 * (mileage - 100));
			}
			else {
				rent += (0.21 * 400);
				rent += (0.17 * (mileage - 500));
			}
		}
	}
	if (luxbool == true) {
		rent += (28 * rentlength);
	}
	cout << "The rental charge for " << customer << " is $" << rent;
}
