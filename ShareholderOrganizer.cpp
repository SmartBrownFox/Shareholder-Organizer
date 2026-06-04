// Program: CharltonW_2
// Purpose: Manage shareholder data and provide category analysis
// Author: Wesley Charlton
// Date: 10/05/25

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Defining shareholder struct
struct Shareholder {
	string name;
	string category;
	int shares;
};

// Function fro-yo types (prototypes)
void fillVector(vector<Shareholder>& ClientList);
void printvectors(const vector<Shareholder>& ClientList);
void findcategory(const vector<Shareholder>& ClientList);
void breakdown(const vector<Shareholder>& ClientList);

int main() {
	vector<Shareholder> ClientList;

	// Filling vector with data from file
	fillVector(ClientList);

	// Printing shareholder data
	printvectors(ClientList);

	// Finding and displaying specific categories
	findcategory(ClientList);

	// Display the financial breakdown
	breakdown(ClientList);

	return 0;
}

void fillVector(vector<Shareholder>& ClientList) {
	ifstream infile;
	infile.open("shares.txt"); // change every instance of shares.txt with "urfilename.txt"

	if (!infile) {
		cout << "Error opening file!" << endl;
		return;
	}

	Shareholder tempClient;

	while (!infile.eof()) {
		getline(infile, tempClient.name);
		getline(infile, tempClient.category);
		infile >> tempClient.shares;
		infile.ignore(); // Ignore the newline after shares cuz otherwise everything would look weird

		ClientList.push_back(tempClient);
	}

	infile.close();
}

void printvectors(const vector<Shareholder>& ClientList) {
	cout << left << setw(20) << "Name" << setw(10) << "Category"
	     << setw(10) << "Shares" << endl;
	cout << setw(20) << "----" << setw(10) << "--------"
	     << setw(10) << "------" << endl;

	for (int k = 0; k < ClientList.size(); k++) {
		cout << setw(20) << ClientList[k].name
		     << setw(10) << ClientList[k].category
		     << setw(10) << ClientList[k].shares << endl;
	}
	cout << endl << endl;
}

void findcategory(const vector<Shareholder>& ClientList) {
	string searchCategory;
	int totalShares = 0;
	int count = 0;

	cout << "Enter category to search (Gold, Silver, Bronze): ";
	cin >> searchCategory;

	cout << endl << "Clients in " << searchCategory << " category:" << endl;
	cout << setw(20) << "Name" << setw(10) << "Shares" << endl;
	cout << setw(20) << "----" << setw(10) << "------" << endl;

	// My single loop
	for (int k = 0; k < ClientList.size(); k++) {
		if (ClientList[k].category == searchCategory) {
			cout << setw(20) << ClientList[k].name
			     << setw(10) << ClientList[k].shares << endl;
			totalShares += ClientList[k].shares;
			count++;
		}
	}

	if (count > 0) {
		double average = static_cast<double>(totalShares) / count;
		cout << endl << "Average shares for " << searchCategory << " category: "
		     << average << endl;
	} else {
		cout << "No clients found in that category." << endl;
	}
	cout << endl;
}

void breakdown(const vector<Shareholder>& ClientList) {
	double goldTotal = 0.0, silverTotal = 0.0, bronzeTotal = 0.0;
	double totalAssets = 0.0;

	// Another single loop as required
	for (int k = 0; k < ClientList.size(); k++) {
		if (ClientList[k].category == "Gold") {
			goldTotal += ClientList[k].shares * 8.95;
		} else if (ClientList[k].category == "Silver") {
			silverTotal += ClientList[k].shares * 4.95;
		} else if (ClientList[k].category == "Bronze") {
			bronzeTotal += ClientList[k].shares * 1.95;
		}
	}

	totalAssets = goldTotal + silverTotal + bronzeTotal;

	cout << fixed << setprecision(2);
	cout << "ASSET BREAKDOWN BY CATEGORY" << endl;
	cout << "---------------------------" << endl;
	cout << "Gold Assets:   $" << setw(10) << goldTotal << endl;
	cout << "Silver Assets: $" << setw(10) << silverTotal << endl;
	cout << "Bronze Assets: $" << setw(10) << bronzeTotal << endl;
	cout << "Total Assets:  $" << setw(10) << totalAssets << endl;
}