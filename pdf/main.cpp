#include <iostream>
#include <fstream> //Needed anytime a program performs file input/output
#include <sstream>
using namespace std;




int main(int argc, wchar_t* argv[])
{
	ifstream infile; //Declaring an ifstream (input file stream) called infile.
					   //This object allows me to bring in data from a file and call
	                   //the fstream libraries that open, close and otherwise manipulate input file

	ofstream outfile; //Declaring an ofstream (input file stream) called outfile.
					   //This object allows me to print data to a file and call
	                   //the fstream libraries that open, close and otherwise manipulate output file
	                   //streams

	infile.open("2169.pdf"); //This opens a file full of arbitrary data that is stored in a basic
	                         //text file, this file is saved in the same directory as my .cpp file, so
	                         //I did not have to specify a path

	outfile.open("2169.txt", ios::out); //This opens or creates a file for output. if einsteinPicOutput.txt exists, it will create a new, empty
	                           //file and save over the old one. If it does not exist, it will create a new one.
	                           //outfile now has a file to output data to



	//A string variable named line that can hold a line of text being read in from the file

	string aLine;

	while(!infile.eof())
    {
        infile >> aLine;

        cout << endl << aLine;

        //getchar();
    }

    //cout is the output stream that leads to the console (Console OUTput)
    //above a different output stream was created and a file was opened
    //for it to output to. outfile used in conjunction with the output stream operators
    // << will output data to the file data2.txt.
    outfile << aLine << endl;

    infile.close();
    outfile.close();


	//}
//	system("pause");

	return 0;
}
