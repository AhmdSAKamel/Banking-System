// Breakpoint & Memory values
// f5 for executing code between 2 breakpoints
// Debug Dropdown/ Disable/Delete/enable all breakpoints
// Autos Window
// Quick Watch Window. When debugging, Highlight the values, then press shift + f9
// Step Into: f11 /Over: f10 /Out: shift + f11 .
// Create Library: Local Library as a file on the device.	ctrl + alt + l || veiw drop down / Selution Explorer, Double click then Add.
// Ternary Operator/ Short Hand If  :	condition   ?   expression1   :   expression2;			also nested ternary operator is possible
// Ranged Loop	{ '1','2','3','4' } this called setts of items
// Validatation Number
// Bitwise AND operator '&'   |    Logical And is (&&) 
// Bitwise Or Operator '|'
// Declaration Vs Definition
// Default Parameters (Default = Fail), (Optional Paramter).
// Function Overloading (To have the same name for more than one function), Compiler differentiates them by the number of parameters + the type of.
// ctrl + shift + b = Build
// Active Frame (Active Functioning frame), During the execution, there is only one active frame. Last execution enter the stack is the first one exists.
// if you want to look through the hierarachy, use breakpoint/ or without, view call hierarachy/stack option.
// Functions Tips, Find all refrences options for discovering where exactly the function have been called in the programme (shift + f11)
// Rename in right click for changing the name only one time
// Recurtion, recursive call for functions.
// Static Variables: A variable keeps its value in the lifetime of the programme. (like globale variables)
// Automatic Variables.
// Register Variables: In past, C++ had the ability to define a variable (adding "register" word to it) then preserve a place in Registers (not RAM)
// Two dimensional Arrays, Rows & Culamns
// Vectors : Declaration & Initialization. (Dynamic Array)
// Add elements to vectors : push-back function.
// Vector of Structure
// Remove elements from Vectors: pop_back (It removes the last element added to the Vector).
// Call ByRef/ByVal: When calling by val, Compiler Creates a variable, gives it an address, then add the value of the parameter into it.
// When calling by Ref: Compiler doesn't create a new variable as Calling by Val do, it gives the parameter a nickname (Same address), it can access from both names.
// Syntax for printing Hexadecimal Address: "cout << & + variable"
// Creating References, By creating a reference of a variable, both are pointing at the same place in memory : int &x = a; Here a and x are pointing at the same place in memory, so address of 'a' and address of 'x' are the same.
// Pointers: Other languages use Pointers automatically in the backgroud and don't allow developers to use Pointer, only C and C++ do.
// Pointers give you full access to memory for maneging it. Pointer is a variable for storing address belongs to another variable, function or anything in memory.
// Dereferencing Pointers: Reaching the Value of Pointers, write "cout << *Variable", Both the pointer and the variable points at the same locatation in memory.
// Pointers Vs References: Reference is like a nickname for the variable, When we create a reference to a variabel, compiler gives a nicname to that variable in the same memory slot in memory.
// When creating a pointer of a variable, compiler creates a different slot in memory, then stores the address of that variable into it.
// When we assign a reference to a variable, we can't change it to another variable during the execution, While we can with pointers.
// Call by Reference: Using Pointers.
// Pointers and Arrays: When we assign a pointer to an array from the same type, The Pointer points at the first element at the array.
// Dynamic Memory Allocation New-Delete: it gives power to C++ to have full controll over memory
// Dynamic Array New-Delete
// Stack vs Heap: Heap is a location in the memory stores dynamic variable/objects/array...etc.	We reach it only by pointers.
// Vectors part || : Access Elements.
// Vectors Change Elements.
// Vector Iterators: a Way for going through the Elements of Vectors using pointers.
// Exception Handling: Try Catch
// String Object. (Common Methods)
// Some cctype Library Functions.
// Write Mode: Write Data To File.
// Append mode - Append Data to File.
// Files Read Mode.
// Load Data From File to Vector.
// Save Vector to File.
// Files Delete Record From File.
// Update Record.
// Files Update Record In File.
// Local/UTC Datetime.
// Datetiem Structure.

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>


#pragma warning(disable: 4996) // When C++ douts in any code, it'll pop up a warning message, this line makes compiler disable the warning with the number 4996.
#pragma once

using namespace std;


namespace Course6Test
{
	int ReadNumberTest(string Message)
	{

		int Number = 0;

		cout << Message;
		cin >> Number;

		while (cin.fail())
		{

			cin.clear();	//Delete the error
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //Ignore rest of the line
			cout << "Invalid Number, Enter a valid one: " << endl;

			cin >> Number;
		}

		return Number;
	}

	string PositiveNegetiveTest(short Number)
	{
		string Status = "";

		Status = (Number == 0) ? "Zero" : ((Number > 0) ? "Positive" : "Negative");		//Nested Ternary Operator.

		return Status;
	}

	struct stName
	{
		string FirstName = "";
		string LastName = "";
		short Salary = 0;
	};

	struct stEmployee
	{
		string FirstName = "";
		string LastName = "";
		short Salary = 0;
	};

	//function decleration
	short Add(short, short);

	int MySum(int a, int b, int c = 0, int d = 0)
	{				//Optional Parameters/ Default Parameters

		return a + b + c + d;

	}

	void PrintNumbers(int N, int M)
	{
		if (N <= M)		//Recursive call 
		{
			cout << N << endl;
			PrintNumbers(N + 1, M); //Calling itslf.
		}

	}

	void RecursiveFromMToN(short M, short N = 0)
	{
		if (M >= 1)
		{
			cout << M << endl;
			RecursiveFromMToN(M - 1);
		}
	}

	short RecursivePowFunction(short N, short P)
	{

		if (P == 0)
			return 1; //Will not be executed untill the call stack is empty.
		else
		{
			short M = (N * RecursivePowFunction(N, P - 1));		//Will come back here for emptying the call stack.
			return M;
		}
	}

	void FillDimensionalArrayInMultTableTest(int arr10[10][10])
	{

		for (short i = 0; i < 10; i++)
		{
			for (short j = 0; j < 10; j++)
			{
				arr10[i][j] = (i + 1) * (j + 1);
			}
		}
	}

	void PrintDimensionalArray(int arr[10][10])
	{
		FillDimensionalArrayInMultTableTest(arr);

		for (short i = 0; i < 10; i++)
		{
			for (short j = 0; j < 10; j++)
			{
				printf("%0*d ", 2, arr[i][j]);
			}
			cout << endl;
		}
	}

	void FillVecotrsTest(vector <short>& vtor)
	{

		for (short& Number : vtor) //When we add the reference sign, it does not copy the item, it goes directly to its location at the memory.
		{
			cout << Number << " "; //Ranged loop will go to the first item reference and print it in a new variable.
		}
		cout << endl;
	}

	void VectorsTest()
	{
		vector <string> vNumbers = { "[]" , "{}" };

		vNumbers.push_back("8"); //Adding elements
		vNumbers.push_back("oop");
		vNumbers.push_back("oop");

		for (string& S : vNumbers)
		{
			cout << S << endl;
		}
	}

	void ReadNumbers(vector <short>& vNumbers)
	{
		short Number = 0;

		char Again = 'y';

		do
		{
			cout << "Please enter a number? ";
			cin >> Number;
			vNumbers.push_back(Number);

			cout << "\nDo you want to read more numbers? Y/N ? ";
			cin >> Again;


		} while (Again == 'y' || Again == 'Y');

	}

	void PrintVectorNumbers(vector <short>& vNumbers) //By refrence is prefered over making a copy then printing it.
	{

		for (short& Num : vNumbers)
		{
			cout << Num << "\n";
		}
		cout << endl;
	}

	void ReadEmployees(vector <stEmployee>& Employees)
	{

		char Again = 'y';

		stEmployee Employee;

		do
		{
			cout << "Enter First Name? ";
			cin >> Employee.FirstName;

			cout << "Enter Last Name? ";
			cin >> Employee.LastName;

			cout << "Enter Salary? ";
			cin >> Employee.Salary;

			Employees.push_back(Employee);

			cout << "\nDo you want to add more employees? Y/N ? ";
			cin >> Again;

		} while (Again == 'y' || Again == 'Y');
	}

	void PrinVectortEmployees(vector <stEmployee>& Employees)
	{

		cout << "\nEmployees vector:\n\n";

		for (stEmployee& Employee : Employees)
		{
			cout << Employee.FirstName << endl;
			cout << Employee.LastName << endl;
			cout << Employee.Salary << endl;

			cout << endl;
		}
	}

	void TestCreateReference()
	{

		int a = 10;
		int& x = a;

		cout << &a << endl;
		cout << x << endl;

		x = 19;		// Changing one will change the other. Because both have the same location in memory.

		cout << a << endl;
		cout << x << endl;
	}

	void TestPointer()
	{
		int a = 10;

		int* P = &a; // Here we defined a variable from pointer of integer kind, stored in P.

		cout << *P + 10;   //  Changing the value by pointer.

	}

	void SwapByPointersTest(int* n1, int* n2) // Sometimes within the function we need to make a variable points at another one at memory.
	{
		int Temp = 0;
		Temp = *n1;
		*n1 = *n2;
		*n2 = Temp;
	}

	void ArrayWithPointersTest(short arr[4])
	{
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;


		short* prr;

		prr = arr; //Equivalent to the address of arr[0].

		cout << *(prr);		// Value of arr[0];

		cout << *(prr + 1);	// Value of arr[1];
	}

	void StructuresWithPointersTest()
	{
		stName Name, * pst; //Assigning a Pointer from the structure type.

		Name.FirstName = "Ahmed";
		Name.LastName = "Kamel";
		Name.Salary = 5000;

		cout << &Name.FirstName;

		pst = &Name;

		cout << pst->LastName; //Accessing the value of structure through a pointer.
	}

	void voidPointerTest()
	{
		//This makes us able to make a data pointer pointing at different data types in the run time.

		void* ppr;	//Generic Pointer, a typeless pointer that can point at any type of data at the memory.

		float f1 = 10.5;
		int x = 50;

		ppr = &f1;

		cout << ppr;	//Note: Void Pointers can't print the value of the variable, because it's Generic that does not know its type.

		cout << *(static_cast<float*>(ppr)); //By this, compiler will cast this generic pointer to a float pointer (Exciplicit Casting), so it could print its value.

		ppr = &x;	//This transfered the pointer from pointing at the float f1 to integer x.

		cout << *(static_cast<int*>(ppr));
	}

	void DynamicMemoryAllocationTest()
	{
		int* prrx; // Pointer does not preserve a space in memory

		// Dynamically allocate memory in the run time.

		prrx = new int;	// A variable from integer type, then pointed at prrx.

		*prrx = 10;

		delete prrx; //Deallocate from the memory, for every "new" function, use "delete" in return.
	}

	void PointerNewArrayTest()
	{
		short NumberOfStudents = 4;

		float* prt;

		prt = new float[NumberOfStudents];

		delete[] prt;	// Deleting the array
	}

	void VectorsAccessElements()
	{
		vector <int> num{ 1,2,3,4,5 };

		cout << num.at(4);

		cout << num[4];
	}

	void VectorsIteratorTest()
	{
		vector <int>num{ 1, 2, 3, 4, 5 };


		//Declare iterator.
		vector <int>::iterator iter;	// Iterator must be the same type of vector.

		//Iterator with for loop.

						// First		/Last element in vector
		for (iter = num.begin(); iter != num.end(); iter++)
		{
			cout << *iter << "  ";  //Iter is pointing at element by element's pointer.
		}

	}

	void ExceptionHandlingTest()
	{
		vector<int>num{ 1,2,3,4,5 };

		try
		{
			cout << num.at(5);		// Any exception happens will not cause to crash the programme.
		}
		catch (...)
		{
			cout << "Out of bound\n";	// Any thing could cause an error put it in here.
		}


	}

	void StringObjectTest() // String Library should be used.
	{
		string s1 = "My Name is Ahmed, I like programming. ";

		cout << s1.length();		// Length

		cout << s1.at(3);			// Return the letter at position 3.

		s1.append("@It'sme.com");	//Add @It'sme.com to the end of string.

		s1.insert(7, " Test ");		// insert "test" at position 7.

		cout << s1.substr(16, 8);	// Print all the next 8 letters from position 16.

		s1.push_back('k');			// Add one character to the end of the string.

		s1.pop_back();				// Remove one character from the end of the string

		cout << s1.find("Test");	// Find "Test" in the string.

		cout << s1.find("test");	// Find "test" in the string.

		if (s1.find("test") == s1.npos) // No Position
		{
			cout << "\"test\" is not found";
		}

		s1.clear();					// Clear all string letters.


	}

	void cctypeFunctionsTest()
	{
		char x, w;

		x = toupper('a');	// From small to capital

		w = tolower('A');	// From capital to small

		cout << x << endl;
		cout << w << endl;

		cout << isupper('A');	// If it's uppercase, it'll return a positive number.

		cout << islower('a');   // if it's not lowercase, it'll return a negative number.

		cout << isdigit('9');   // Check if this chatacter is a digit or not, if not it'll return 0.

		cout << ispunct(';');	// Check it this is a punctuation, if not it'll return 0.

	}

	void WriteDataToFileTest()
	{
		fstream MyFile;			//Assign a variable from file stream.

		// Open the file by write mode. When using write mode. whatever exists in the file. C++ will erase it, then rewrite on.
		MyFile.open("AFile.txt", ios::out);		// Set the name of the file that would store on the SSD by the end of execution.

		if (MyFile.is_open())		// It means that code above works without errors.
		{
			MyFile << "Ali\n";	// For adding to MyFile instead of screen.
			MyFile << "Maher\n";
			MyFile << "Fadi\n";
			MyFile << "Shadi\n";
			MyFile << "Ali\n";
			MyFile << "Mohammed\n";

			MyFile.close();	// To avoid errors
		}

		// To open the file. Go to View dropdown, press Solution explorer, then right mouse click on the project, then open folder in file explorer.
	}

	void AppendModeTest()
	{
		fstream MyFile;

		// MyFile2.open("MyFileInAppenMode.txt", ios::app); : append mode.

		MyFile.open("MyFileInAppenMode.txt", ios::out | ios::app); // Check the file, if it's not existed, open it for Write or append mode, and give priority to append.

		// Every time we make run, the programme will append the Data.

		if (MyFile.is_open())
		{
			MyFile << "Append Test\n";
		}
	}

	void PrintFilesReadModeTest(string FileName)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::in);		// Read Mode: this make us able to read from the file. (can't adjust into it)

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))	// Read first line from "MyFile", and add it to this variable (Line). 
			{
				if (Line == "")
				{
					Line = '\n';
				}
				cout << Line << endl;	// Print the read line.
			}
			MyFile.close();
		}
	}

	void LoadDataFromFiletoVectorTest(string FileName, vector <string>& FileContent)
	{
		fstream MyFile;

		MyFile.open("AFile.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				FileContent.push_back(Line);
			}
			MyFile.close();
		}
	}

	void SaveVectorToFileTest(string FileName, vector <string>& FilledContent)
	{
		fstream VectorFile;

		VectorFile.open(FileName, ios::out);

		if (VectorFile.is_open())
		{
			for (string& C : FilledContent)
			{
				if (C != "")
				{
					VectorFile << C << endl;
				}
			}
			VectorFile.close();
		}
	}

	void DeleteRecordFromFile(string FileName, string Record)
	{
		vector <string> vFileContent;

		LoadDataFromFiletoVectorTest("AFile", vFileContent);

		for (string& Line : vFileContent)
		{
			if (Line == Record)
			{
				Line = "";
			}
		}
		SaveVectorToFileTest(FileName, vFileContent);
	}

	void UpdateRecordInFileTest(string FileName, string Record, string UpdateTo)
	{
		vector <string> vFileContent;
		LoadDataFromFiletoVectorTest(FileName, vFileContent);

		for (string& Line : vFileContent)
		{
			if (Line == Record)
			{
				Line = UpdateTo;
			}
		}
		SaveVectorToFileTest(FileName, vFileContent);

	}

	void DeleterecordFromFileTest()
	{
		WriteDataToFileTest();

		cout << "File Content Before Delete.\n";

		PrintFilesReadModeTest("AFile.txt");

		UpdateRecordInFileTest("AFile.txt", "Ali", "Omar");

		cout << "\n\nFile Content After Delete.\n\n";

		PrintFilesReadModeTest("AFile.txt");
	}

	void LocalGrinitchTimeTest()
	{
		// The library <ctime> is inherited from C language.

		time_t t = time(0);	  //Get time now.

		char* dt = ctime(&t);	// Convert in string form.

		cout << "Local date and time is: " << dt << '\n';

		tm* gmtm = gmtime(&t);		// Converting now to tm struct for UTC date/time. (Grinitch time/Universla time)

		dt = asctime(gmtm);			// Convert in string form.

		cout << "UTC date and time is: " << dt;
	}

	void  DatetiemStructureTest()
	{
		time_t t = time(0);	  //Get time now.

		tm* now = localtime(&t);  //tm is a structure from ctime library.

		cout << "Year: " << now->tm_year + 1900 << endl;	// tm_year is an element of the structure, it gives you how many years after 1900.
		cout << "Month: " << now->tm_mon + 1 << endl;
		cout << "Day: " << now->tm_mday << endl;
		cout << "Hour: " << now->tm_hour << endl;
		cout << "Min: " << now->tm_min << endl;
		cout << "Second: " << now->tm_sec << endl;
		cout << "Week Day (Days since sunday): " << now->tm_wday << endl;
		cout << "Year Day (Days since Jan 1st): " << now->tm_yday << endl;
		cout << "hours of daylight savings time: " << now->tm_isdst << endl;
	}












	int main()
	{
		srand((unsigned)time(NULL));

		return 0;
	}



	// function definition
	short Add(short a, short b)
	{
		return a + b;
	}












}


