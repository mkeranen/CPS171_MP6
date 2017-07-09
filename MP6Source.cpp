/*Machine Problem 6
Author: Mark Keranen CPS171 07/08/2017

This program reads a series of names of people from a data file that has been created with extra blank 
spaces and reformats the names into a standardized format.

Assumptions:
The input datafile is arranged with the information for one person on each line.  The first character on the line will be 
either ‘M’ or ‘F’ indicating the gender of the person, and the second character will be either ‘M’, ‘S’, or ‘D’ indicating married, 
single or divorced. It is assumed that there will be no bad data in the file. 

The remainder of the line is the person’s name in the form:

Last_name, First_name Middle_Initial.

Note that there will always be a comma immediately after the last name and, if the person has middle initial, it will always be 
followed by a period.  However, there could be any number of blank spaces in between each part of the name and some people do not 
have middle initial.

The program outputs the formatted names in the following form:

Prefix. First_name Middle_Initial Last_name
*/

//Include statements for std IO, file manipulation, input/output manipulation, string operations
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//Define enum 'Marital Status'
enum Maritalstatus {SINGLE = 'S', MARRIED = 'M', DIVORCED = 'D'};

//Main loop: Opens input datafile, parses contents, formats contents, outputs original & formatted names
int main(){
	
	//Function prototype statement
	string formatNames(string);

	//Variable declarations
	string originalName, formattedName;

	//Setup filestream
	ifstream fin;

	//Open file with unformatted names
	fin.open("mp6Names.txt");

	//Print headers for data output, set width to 32 and left justify for readability
	cout << setw(32) << left << "Original name";
	cout << setw(32) << left << "Standardized name\n" << endl;

	//Loop through the file, read in all the names and format them
	while (getline(fin, originalName)){                         //While there's a line to read in, assign to 'originalName'
		cout << setw(32) << left << originalName;               //Print out the unformatted name that was read in
		formattedName = formatNames(originalName);              //Call the function to format the unformatted name
		cout << setw(32) << left << formattedName << endl;      //Print out the results of formatting the name
	}
	
	cout << endl;
	return 0;
}

//Function: This function takes in a string and removes white space, rearranges substrings, and returns a new string
string formatNames(string originalName){
	
	//Variable declaration for use in function
	string formattedName, firstName, lastName, middleInitial;
	int position;

	//Check if name is male or female, single/married/divorced, and assign corresponding prefix
	if (originalName[0] == 'M'){                 //If line starts with 'M', the only prefix possible is "Mr."
		formattedName = "Mr. ";                  //Start building formatted name string
	}
	else{                                        //If not male..
		switch (originalName[1]){                //Switch case to decide if "Mrs." or "Ms." is appropriate, operates on second character
			                                     //because we already know its not a male, so only marital status is important here
		case MARRIED: formattedName = "Mrs. ";   //If currently married, then "Mrs." is appropriate
			break;
		default: formattedName = "Ms. ";         //If not married, then "Ms." is appropriate for single or divorced, 
			                                     //good practice to have a default case instead of a separate case
			break;
		}
	}
	
	//Find comma, which indicates position of end of last name
	position = originalName.find(',');

	//Extract last name and remove whitespace from string
	lastName = originalName.substr(2, position-2);
	lastName = lastName.substr(lastName.find_first_not_of(' '));

	//Move positional locator past all whitespace to start of first name
	while (originalName[++position] == ' ');

	//Cut whitespace off of unformatted name
	originalName = originalName.substr(position);

	//Find next whitespace, which indicates location of end of first name
	position = originalName.find(' ');

	//Extract first name
	firstName = originalName.substr(0, position);

	//Move positional locator past all whitespace to start of middle initial
	while (originalName[++position] == ' ');

	//Extract middle initial; If no middle initial exists, there will be no character assigned
	middleInitial = originalName.substr(position, originalName.find('.'));

	//Build final formatted name string
	formattedName.append(firstName + ' ');
	formattedName.append(middleInitial + ' ');
	formattedName.append(lastName);
	return formattedName;
}