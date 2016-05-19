#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
struct Date //Date struct for delivery
{
	int month;
	int day;
	int year;
};
enum CarMake {Ford,Lexus,Nissan,Mercedes,Honda,Audi,Chrysler,Volvo,Porche}; //Enum for car make
struct Car //Car struct consisting of first name, last name, car cost, date struct, and car make
{
	string fName;
	string lName;
	float cost;
	Date date;
	CarMake carMaker;
};
void heading();
Car get_car_data(ifstream&); //Prototype
void lookup_car_data(char, Car[]); //Prototype
float modify_car_data(float, int, Car[]); //Prototype
void output_car_data(Car[], ofstream&); //Prototype
void print_car_report(Car[]); //Prototype
void write_car_output(Car[], ofstream&); //Prototype
void heading()
{
	cout << "**********************************************************\n";
	cout << "Osi Otugo\n";
	cout << "@02662492\n";
	cout << "December 9, 2015\n";
	cout << "Assignment 11\n";
	cout << "Increase/decrease car prices\n";
	cout << "**********************************************************\n";
}

int main()
{
	//Declare variables
	char runAgain, make;
	//Array consisting of 10 elements -- car structs
	Car cars[10];
	//Input file and output file used to extract and store data, respectively
	ifstream myFile;
	ofstream outFile;
	myFile.open("infile.txt");
	outFile.open("outfile.txt");
	//Counter for elements in Car array
	int index = 1;
	//Priming read
	cars[0] = get_car_data(myFile);
	//Simple while loop to store car data from input file
	while (myFile && (index <= 9)) {
		//Call function to store data into element
		cars[index] = get_car_data(myFile);
		//Increment by 1
		index++;
	}
	//Do while loop to prompt user of what car (s)he wants to modify. Ends if user inputs "N"
	do
	{
		cout << "Choose from the list of car manufacturers below." << endl
			<< "F - Ford, L - Lexus, N- Nissan, M - Mercedes, H - Honda," << endl
			<< "A - Audi, C - Chrysler, V - Volvo, P - Porche>" << endl << endl;
		cout << "Enter the make of the car you wish to discount: ";
		//Take user's input
		cin >> make;
		//Call look up car data function
		lookup_car_data(make, cars);
		//Prompt user to find out if (s)he would like to continue modifying car files
		cout << "Do you want to discount any more cars? ";
		//Record user's answer
		cin >> runAgain;
	} while (runAgain != 'N');
	//Call output car data function to output data onto temrinal and into outfile
	output_car_data(cars, outFile);
	system("pause");
}
//Function is used to store data from infile
Car get_car_data(ifstream& myFile)
{
	//Declare variables/struct
	Car cars;
	char carManu;
	//Store data from infile
	myFile >> cars.fName >> cars.lName >> cars.cost >> cars.date.month
		>> cars.date.day >> cars.date.year >> carManu; 
	//Switch statement to store car make
	switch (carManu)
	{
		case 'F':
			cars.carMaker = Ford; break;
		case 'L':
			cars.carMaker = Lexus; break;
		case 'N':
			cars.carMaker = Nissan; break;
		case 'M':
			cars.carMaker = Mercedes; break;
		case 'H':
			cars.carMaker = Honda; break;
		case 'A':
			cars.carMaker = Audi; break;
		case 'C':
			cars.carMaker = Chrysler; break;
		case 'V':
			cars.carMaker = Volvo; break;
		case 'P':
			cars.carMaker = Porche; break;
	}
	//Return car struct to main
	return cars;
}
//Function used to look up the car data the use wants to modify
void lookup_car_data(char carComp, Car car[])
{
	//Declare variables/struct
	Car cars;
	string carManu;
	float discount;
	int index;
	//Switch statement created for use in if statement later also to output the car make
	switch (carComp)
	{
		case 'F':
			cars.carMaker = Ford; carManu = "Ford"; break;
		case 'L':
			cars.carMaker = Lexus; carManu = "Lexus"; break;
		case 'N':
			cars.carMaker = Nissan; carManu = "Nissan"; break;
		case 'M':
			cars.carMaker = Mercedes; carManu = "Mercedes"; break;
		case 'H':
			cars.carMaker = Honda; carManu = "Honda"; break;
		case 'A':
			cars.carMaker = Audi; carManu = "Audi"; break;
		case 'C':
			cars.carMaker = Chrysler; carManu = "Chrysler"; break;
		case 'V':
			cars.carMaker = Volvo; carManu = "Volvo"; break;
		case 'P':
			cars.carMaker = Porche; carManu = "Porche"; break;
	}
	//Look through array of car structs to find the car that matches the user's input
	for (index = 0; index <= 9; index++)
	{
		if (cars.carMaker == car[index].carMaker)
		{
			//Once found, exit loop
			break;
		}
	}
	//Simple output statements
	cout << "\n\nYou are modifying : " << endl;
	cout << "\tCustomer Name: " << car[index].fName << " " << car[index].lName << endl;
	cout << "\tCar Price:\t$" << fixed << setprecision(2) << car[index].cost << endl;
	cout << "\tPurchase Date: " << car[index].date.month << "/" << car[index].date.day
		<< "/" << car[index].date.year << endl;
	cout << "\tCar Model:\t" << carManu;
	//Prompt user for discount
	cout << "Enter the discount <e.g. 0.10 = 10%>: ";
	//Store discount
	cin >> discount;
	cout << endl << endl;
	//Show user the old and new price and the discount applied
	cout << "Old Price : $" << fixed << setprecision(2) << car[index].cost << endl;
	//Call the modify car data function and store the returned file as the new car cost
	car[index].cost =  modify_car_data(discount, index, car);
	cout << "New Price: $" << fixed << setprecision(2) << car[index].cost << endl;
	//Reset index
	index = 0;
	float percentage = 100 * discount;
	cout << percentage << "% Discount has been applied" << endl;
}
//Function calculates the discount for car
float modify_car_data(float discount, int index, Car car[])
{
	//New price is current cost minus the cost after multiplied by the discount
	float price = car[index].cost - (car[index].cost * discount);
	//Return price
	return price;
}
//Calls two other functions to output the car data
void output_car_data(Car car[], ofstream& outFile)
{
	//Calls print car report to output data onto screen
	print_car_report(car);
	//Calls write car output to store data into outfile
	write_car_output(car, outFile);
}
//Funciton output data onto screen
void print_car_report(Car car[])
{
	string carManu;
	cout << "Customer\tPrice\t\tPurchase\tModel" << endl;
	cout << setw(6) << "  Name\t\t\t\t   Date" << endl << endl;
	//Loops through array to info for the cars
	for (int index = 0; index <= 9; index++)
	{
		cout << car[index].fName << " " << car[index].lName << "\t" << fixed << setw(8) <<
			setprecision(2) << car[index].cost << "\t" << car[index].date.month << "/" 
			<< car[index].date.day << "/" << car[index].date.year << "\t";
		//Switch statement used to determine the full name of the car make
		switch (car[index].carMaker)
		{
			case Ford:
				carManu = "Ford"; break;
			case Lexus:
				carManu = "Lexus"; break;
			case Nissan:
				carManu = "Nissan"; break;
			case Mercedes:
				carManu = "Mercedes"; break;
			case Honda:
				carManu = "Honda"; break;
			case Audi:
				carManu = "Audi"; break;
			case Chrysler:
				carManu = "Chrysler"; break;
			case Volvo:
				carManu = "Volvo"; break;
			case Porche:
				carManu = "Porche"; break;
		}
		cout << carManu << endl;
	}
}
//Function stores data into outfile
void write_car_output(Car car[], ofstream& outFile)
{
	string carManu;
	//Loops through array and stores stores data into the outfile
	for (int index = 0; index <= 9; index++)
	{
		outFile << car[index].fName << " " << car[index].lName << " " << car[index].cost 
			<< " " << car[index].date.month << " " << car[index].date.day << " " 
			<< car[index].date.year << " ";
		//Switch statement used to determine the full name of the car make
		switch (car[index].carMaker)
		{
			case Ford:
				carManu = "Ford"; break;
			case Lexus:
				carManu = "Lexus"; break;
			case Nissan:
				carManu = "Nissan"; break;
			case Mercedes:
				carManu = "Mercedes"; break;
			case Honda:
				carManu = "Honda"; break;
			case Audi:
				carManu = "Audi"; break;
			case Chrysler:
				carManu = "Chrysler"; break;
			case Volvo:
				carManu = "Volvo"; break;
			case Porche:
				carManu = "Porche"; break;
		}
		outFile << carManu << endl;
	}
}
/*
Choose from the list of car manufacturers below.
F - Ford, L - Lexus, N- Nissan, M - Mercedes, H - Honda,
A - Audi, C - Chrysler, V - Volvo, P - Porche>

Enter the make of the car you wish to discount: L


You are modifying :
        Customer Name: Bear Bare
        Car Price:      $44444.00
        Purchase Date: 9/6/1990
        Car Model:      LexusEnter the discount <e.g. 0.10 = 10%>: .20


Old Price : $44444.00
New Price: $35555.20
20.00% Discount has been applied
Do you want to discount any more cars? Y
Choose from the list of car manufacturers below.
F - Ford, L - Lexus, N- Nissan, M - Mercedes, H - Honda,
A - Audi, C - Chrysler, V - Volvo, P - Porche>

Enter the make of the car you wish to discount: V


You are modifying :
        Customer Name: Janis Smith
        Car Price:      $23450.00
        Purchase Date: 7/11/2001
        Car Model:      VolvoEnter the discount <e.g. 0.10 = 10%>: .30


Old Price : $23450.00
New Price: $16415.00
30.00% Discount has been applied
Do you want to discount any more cars? N
Customer        Price           Purchase        Model
  Name                             Date

Tiny Tim        55000.00        1/1/1985        Ford
Mary Murphy     12500.00        2/7/1995        Nissan
Bear Bare       35555.20        9/6/1990        Lexus
Sally Sale       7500.00        6/3/1970        Mercedes
Betty Bye       18888.00        4/8/1988        Chrysler
Alice Alas      23005.00        6/6/1992        Ford
Randy Law       12098.00        1/4/2009        Audi
Carl Lane       45000.00        12/3/2003       Porche
Janis Smith     16415.00        7/11/2001       Volvo
George Lee      14560.00        4/4/1999        Honda
Press any key to continue . . .
*/
//Below is the outfile
/*
Tiny Tim 55000 1 1 1985 Ford
Mary Murphy 12500 2 7 1995 Nissan
Bear Bare 35555.2 9 6 1990 Lexus
Sally Sale 7500 6 3 1970 Mercedes
Betty Bye 18888 4 8 1988 Chrysler
Alice Alas 23005 6 6 1992 Ford
Randy Law 12098 1 4 2009 Audi
Carl Lane 45000 12 3 2003 Porche
Janis Smith 16415 7 11 2001 Volvo
George Lee 14560 4 4 1999 Honda

*/