#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

string getName(){
	cout << "Kindly state your name for file drafting: ";
	string name;
	cin >> name;
	
	return name;
}

string getSemester(){
	cout << "What semester is this entry for: ";
	string semester;
	cin >> semester;
	
	return semester;
}

void fileChecking(string name, string fileName){
	ifstream checkFile(fileName);
    if (checkFile.good()) {
         cout << "\nWelcome back, " << name << "!" << "\n";
     } else {
         cout << "\nWelcome " << name << ", your file has been created!" <<endl;
     }
     checkFile.close();
     
     ofstream file(fileName, ios::app);
     file.close();
}



//This handles the entry intp the file
void fileSaving(string fileName, const vector<double>& grades, const vector<string>& courses, const vector<int>& units, double cgpa, int totalUnits, int totalQualityPoints, string semester)
{
    ofstream file(fileName, ios::app);


       //this is the way the outputs will be saved inside the file
    file << "\n--- CGPA Calculator---\n";
    file << "semester: " << semester << "\n";
    for (int i = 0; i < courses.size(); i++) {
        file << courses[i] << " (" << units[i] << " units) : " 
             << grades[i] << " GP\n";
    }
    file << "\nTotal Units: " << totalUnits << "\n"; 
    file << "\nTotal points acquired: " << totalQualityPoints << "\n";
    file << "CGPA: " << fixed << setprecision(2) << cgpa << "\n";
    file << "---------------------------------\n";
    
    file.close();
    cout << "Saved to " << fileName << endl;
}

double getGradePoint(int mark)
{
    if(mark >= 70) return 5.0;
    else if(mark >= 60) return 4.0;
    else if(mark >= 50) return 3.0;
    else if(mark >= 45) return 2.0;
    else if(mark >= 40) return 1.0;
    else return 0.0;
}



//Handles course, grade and unit entry, to perform function of calculating the cgpa
void getGrade(string name, string fileName)
{
	cout << "\n" << "Note: you're going to be inputing your courses alongside your grades, so please do that carefully";
	
	string semester = getSemester();
	
	vector<string> courses;
    vector<double> grades; 
    vector<int> units;
    char addMore = 'y';
	    
    while (addMore == 'y' || addMore == 'Y'){
     	cout << "\n Enter name of course: ";
	 	string course;
	 	cin >> course;
	    	
	 	cout << " Enter grade for the course:  ";
	 	int grade;
     	cin >> grade;
     	
     	cout<< "Enter unit for the course: ";
     	int unit;
     	cin >>unit;
     	
     	double gp = getGradePoint(grade);
	    	
	    	//stores the input in the array created in order
	    courses.push_back(course);
    	grades.push_back(gp);
    	units.push_back(unit);
	    	
		cout << "\nDo you wish to add more courses? (y/n): ";
        cin >> addMore;
    }
    
    
    double totalQualityPoints = 0.0;
    int totalUnits = 0;
    
    for(int i = 0; i < units.size(); i++){
        totalQualityPoints += units[i] * grades[i];   // Important: multiply by unit
        totalUnits += units[i];
    }
    
    double cgpa = (totalUnits > 0) ? totalQualityPoints / totalUnits : 0.0;

    cout << fixed << setprecision(2);
    cout << "\nYour CGPA for this semester is: " << cgpa << endl;
    
    
    fileSaving(fileName, grades, courses, units, cgpa, totalUnits, totalQualityPoints, semester);
}


int main ()
{
	string name = getName();
    string fileName = name + ".txt";
    fileChecking(name, fileName);
    
    getGrade(name, fileName);
    cout<<"\n We hope to see you again, olodo. lol";
    
    return 0;
}