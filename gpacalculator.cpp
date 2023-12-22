#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>
using namespace std;

// function to convert a letter grade to GPA points
double converter(string grade){
    double newNum = 0;
        // special case because A and A+ share the same GPA
        if(grade == "A" || grade == "A+"){
            newNum = 4.0;
        } else if(grade == "A-"){
            newNum = 3.7;
        } else if(grade == "B+"){
            newNum = 3.3;
        } else if(grade == "B"){
            newNum = 3.0;
        } else if(grade == "B-"){
            newNum = 2.7;
        } else if(grade == "C+"){
            newNum = 2.3;
        } else if(grade == "C"){
            newNum = 2.0;
        } else if(grade == "C-"){
            newNum = 1.7;
        } else if(grade == "D+"){
            newNum = 1.3;
        } else if(grade == "D"){
            newNum = 1.0;
        } else if(grade == "D-"){
            newNum = 0.7;
        }
    return newNum;
}

// function to convert the grade percentage to a letter grade
string convertToLetter(double gradePercent){
    if(gradePercent >= 97){
        return "A+";
    } else if(gradePercent >= 93){
        return "A";
    } else if(gradePercent >= 90){
        return "A-";
    } else if(gradePercent >= 87){
        return "B+";
    } else if(gradePercent >= 83){
        return "B";
    } else if(gradePercent >= 80){
        return "B-";
    } else if(gradePercent >= 77){
        return "C+";
    } else if(gradePercent >= 73){
        return "C";
    } else if(gradePercent >= 70){
        return "C-";
    } else if(gradePercent >= 67){
        return "D+";
    } else if(gradePercent >= 63){
        return "D";
    } else if(gradePercent >= 60){
        return "D-";
    } else if(gradePercent >= 0){
        return "F";
    }
    
    // return N/A if an invalid percentage is inputted
    return "N/A";
}

// class to represent a new weighting based on a syllabus that a user inputs
class TempSyllabus {
    
public:
    // constructor
    TempSyllabus(){
        m_weight = 0;
        m_name = "";
        m_smallGrade = vector<double>();
        m_smallGname = vector<string>();
        m_actual = 0;
    }
    
    // the weight of the grade type based on the syllabus inputted
    void setWeight(double weight){
        m_weight = weight;
    }
    
    // name of the specific type of grade
    void setName(string name){
        m_name = name;
    }
    
    // the percentage that the particular weighting in the syllabus will contribute to the full grade
    void setActual(double actual){
        m_actual = actual;
    }
    
    // used to calculate grade
    double getWeight() const{
        return m_weight;
    }
    
    // get the name of the specific type of grade to be printed
    string getName() const{
        return m_name;
    }
    
    // get the actual contribution so that it can be added to the final percentage
    double getActual() const{
        return m_actual;
    }
    
    // used to display the syllabus
    void print() const{
        cout << m_name << " (" << fixed << setprecision(2) << m_weight << "%)" << endl;
    }
    
    // even smaller percentages based on the specific grade based on the syllabus
    void addSmallGrade(double smallGrade){
        m_smallGrade.push_back(smallGrade);
    }
    
    // even smaller names based on the specific grade based on the syllabus
    void addGname(string smallGname){
        m_smallGname.push_back(smallGname);
    }
    
    // append this string if there is an extra credit assignment
    void addExtraCredit(){
        m_smallGname.back() += " (EXTRA CREDIT)";
    }
    
    // used to print out all of names and grades of the even smaller grades
    void printSmall() const{
        cout << "----------------------------------" << endl;
        for(int i = 0; i < m_smallGname.size(); i++){
            cout << m_smallGname[i] << ": " << fixed << setprecision(2) << m_smallGrade[i] << '%' << endl;
        }
        cout << "-------------------------" << endl << endl;
    }
    
    
private:
    double m_weight;
    string m_name;
    vector<double> m_smallGrade;
    vector<string> m_smallGname;
    double m_actual;
};




int main() {
    
    for(;;){
        
        int choice = 0;
        
        // options for the user
        cout << "What do you want to do?" << endl << "----------------------------------" << endl;
        cout << "(1) Calculate class grade" << endl;
        cout << "(2) Calcuate cumulative GPA" << endl;
        cout << "(3) Quit" << endl;
        cout << "----------------------------------" << endl << "Please enter your input: ";
        
        // make sure that the user types a valid choice
        if(!(cin >> choice) || choice < 1 || choice > 3){
            cout << endl << "*******************************************" << endl << "That is not a valid input... try again" << endl << "*******************************************" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        
        // possible choices
        switch(choice){
            case 1:
            {
                for(;;){
                    
                    // the amount of weightings that the user will input
                    int classAmount = 0;
                    
                    // used to keep track of the amount of weightings put (will match classAmount)
                    int classCounter = 0;
                    
                    // used to make sure that the user's percentages in the syllabus add up to 100
                    double totalPercentage = 0;
                    
                    // used to determine if the user has made invalid inputs so that this for loop will reset
                    bool breakOut = false;
                    
                    // title
                    cout << endl << "I need to collect information about the weight of your grades." << endl << "-----------------------------------------------------" << endl;
                    cout << "Enter the amount of weightings: ";
                    
                    // make sure that the user types a valid choice
                    if(!(cin >> classAmount) || classAmount <= 0){
                        cout << endl << "*******************************************" << endl << "That is not a valid input... try again" << endl << "*******************************************" << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    
                    cout << endl;
                    
                    // dynamically allocate space for TempSyllabus in an array
                    TempSyllabus* syllabusArray = new TempSyllabus[classAmount];
                    
                    // do this loop until the class counter is the same as the classAmount
                    while(classCounter < classAmount){
                        
                        // do this because there was a cin before the getline
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                        string cName;
                        double cWeight;
                        
                        cout << "Enter the name of the weighting: ";
                        getline(cin, cName);
                        
                        // uppercase the first letter of the weighting name
                        cName[0] = toupper(cName[0]);
                        
                        cout << "Enter the weight % (do not include \"%\"): ";
                        
                        // make sure that the user types a valid choice
                        if(!(cin >> cWeight) || cWeight <= 0){
                            cout << endl << "*******************************************" << endl << "That is not a valid input... try again" << endl << "*******************************************" << endl << endl;
                            cin.clear();
                            
                            continue;
                        }

                        cout << endl;
                        
                        // set certain variables in the class based on the user input
                        syllabusArray[classCounter].setName(cName);
                        syllabusArray[classCounter].setWeight(cWeight);
                        
                        // used to calculate if the total percent is 100
                        totalPercentage += syllabusArray[classCounter].getWeight();
                        
                        classCounter++;
                        
                        // loop will early reset if the user types percentage values that are greater than 100
                        if(totalPercentage > 100){
                            cout << endl << "*************************************************" << endl << "The weightings do not add up to 100%... try again" << endl << "*************************************************" << endl << endl;
                            
                            // delete the array to prevent memory leaks
                            delete[] syllabusArray;
                            breakOut = true;
                            break;
                        }
                        
                    }
                    
                    // loop through the loop again if the user did not make valid inputs
                    if(breakOut){
                        breakOut = false;
                        continue;
                    }
                    
                    // if once the user finishes typing all their weightings and it does not add up to 100
                    if(totalPercentage != 100){
                        cout << endl << "*************************************************" << endl << "The weightings do not add up to 100%... try again" << endl << "*************************************************" << endl << endl;
                        
                        // delete the array to prevent memory leaks
                        delete[] syllabusArray;
                        continue;
                    }
                    
                    // display the syllabus weighting
                    cout << "This is your syllabus weighting:" << endl << "----------------------------------" << endl;
                    for(int i = 0; i < classAmount; i++){
                        syllabusArray[i].print();
                    }
                    cout << "----------------------------------" << endl;
                    
                    // before there was a cin, and after there will be getline, so do this
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    // final percentage
                    double finalPercentage = 0;
                   
                    // name of grade
                    string typeName;
                    
                    // points actually received and total points it is worth
                    double receivedPoints = 0;
                    double totalPoints = 0;
    
                    // iterate through all the weightings
                    for(int q = 0; q < classAmount; q++){
                        
                        // title for specific weighting
                        cout << endl << syllabusArray[q].getName() << " Grades" << endl << "----------------------------------" << endl;
                        
                        // total received points
                        double addingTotalSpecific = 0;
                        
                        // total total points
                        double addingTotal = 0;
                        
                        // keep looping until the user types =
                        for(;;){
                            cout << "Grade Name (\"=\" if done): ";
                            getline(cin, typeName);
                            
                            // uppcase the first letter of the specific grade names
                            typeName[0] = toupper(typeName[0]);
                            
                            // stop the loop
                            if(typeName == "="){
                                cout << endl;
                                break;
                            }
                            
                            // add a name to the vector in the class
                            syllabusArray[q].addGname(typeName);
                            
                            // loop until the user inputs a valid amount of points user received (can have more than the total points of the grade)
                            for(;;){
                                cout << "Points received: ";
                                if(!(cin >> receivedPoints)){
                                    cout << "That is not a valid input... try again" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }
                                break;
                            }
                            
                            // loop until user inputs a valid total poitns, if user types 0, then it will be considered as extra credit
                            for(;;){
                                cout << "Total points (\"0\" if EC): ";
                                if(!(cin >> totalPoints)){
                                    cout << "That is not a valid input... try again" << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }
                                break;
                            }
                            
                            cout << "***************" << endl;
                            
                            // do this because previously, there is a cin
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            
                            // this value will be adding up all of the points that they received (includes extra credit)
                            addingTotalSpecific += receivedPoints;
                            
                            // if there is extra credit, user will receive 100% for the specific grade
                            if(totalPoints == 0){
                                syllabusArray[q].addSmallGrade(100);
                                syllabusArray[q].addExtraCredit();
                            }
                            
                            // calculate totalSpecific (the percentage value of a specific grade) and add it to the vector in the TempSyllabus class
                            else{
                                double totalSpecific = receivedPoints / totalPoints * 100;
                                syllabusArray[q].addSmallGrade(totalSpecific);
                                
                                // add the total poitns that the user inputted
                                addingTotal += totalPoints;
                            }
                            
                            
                        }
                        
                        // case for if the user only included extra credit points to avoid dividng by 0
                        if(addingTotal == 0){
                            // add to the final percentage based on the points the user received times the weighting
                            finalPercentage = finalPercentage + addingTotalSpecific * syllabusArray[q].getWeight();
                            
                            // set the actual contribution of the grade to the amount that the user received times the weight of that grade
                            syllabusArray[q].setActual(addingTotalSpecific * syllabusArray[q].getWeight());
                        }
                        
                        else{
                            // calculate the final percentage by dividing what the user received by the total points all their assignments under a weighting times the weight
                            finalPercentage = finalPercentage + addingTotalSpecific / addingTotal * syllabusArray[q].getWeight();
                            
                            // calculate the actual contribution of the weighting
                            syllabusArray[q].setActual(addingTotalSpecific / addingTotal * syllabusArray[q].getWeight());
                        }
                    }
                    
                    
                    cout << endl;
                    
                    // title for grade distribution
                    cout << "##################" << endl << "GRADE DISTRIBUTION" << endl << "##################" << endl << endl;
                    
                    // display the actual grade contribution from the weighting and the percentage that the user received for each specific small grade
                    for(int m = 0; m < classAmount; m++){
                        cout << syllabusArray[m].getName() << " (" << syllabusArray[m].getActual() << "%)" << endl;
                        syllabusArray[m].printSmall();
                    }
                    
                    // display the final grade of the user in percentage and letter grade
                    cout << "****************************" << endl << "Class Grade: " << convertToLetter(finalPercentage) << " (" << fixed << setprecision(2) << finalPercentage << "%)" << endl << "****************************" << endl << endl;
                    
                    // delete the array to prevent memory leaks
                    delete[] syllabusArray;
                    break;
                    
                }
                
            }
                break;
            case 2:
            {
                // title
                cout << endl << "This will calculate your grade in the college GPA scale." << endl << "-----------------------------------------------------" << endl;
                
                // initialize number of classes
                int numClasses = 0;
                
                // initialize the GPA
                double GPA = 0.00;
                
                // intilize the total points received
                double total = 0;
                
                // initialize the number of classes
                int number = 0;
                string letterInput;
                
                // loop until the input is not negative
                for(;;){
                    
                    // prompt for if the user knows the amount of classes that they have
                    cout << "Type the amount of classes (0 if you don't know): ";
                    
                    // check if the input is invalid
                    if(!(cin >> numClasses) || numClasses < 0){
                        cout << endl << "*******************************************" << endl << "That is not a valid input... try again" << endl << "*******************************************" << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        
                    }else{
                        // break out of the loop if there is a valid input
                        break;
                    }
                }
                    
                
                if(numClasses == 0){
                    
                    // do this because there was a cin before the getline
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    for(;;){
                        
                        // loop until the user types done
                        for(;;){
                            cout << "Class " << number + 1 << " (\"done\" if done): ";
                            getline(cin, letterInput);
                            
                            // make lowercase letters work
                            letterInput[0] = toupper(letterInput[0]);
                            
                            // loop until there is a valid input
                            if(letterInput != "A+" && letterInput != "A" && letterInput != "A-" && letterInput != "B+" && letterInput != "B" && letterInput != "B-" && letterInput != "C+" && letterInput != "C" && letterInput != "C-" && letterInput != "D+" && letterInput != "D" && letterInput != "D-" && letterInput != "F" && letterInput != "Done"){
                                cout << "THAT IS NOT A VALID INPUT!" << endl;
                            }
                            else{
                                break;
                            }
                        }
                        
                        // stop the loop when the user types done
                        if(letterInput == "Done"){
                            break;
                        }
                        
                        // add up total gpa
                        total += converter(letterInput);
                        number++;
                    }
                    
                    // calculate gpa
                    if(number > 0){
                        GPA = total / number;
                    }
                    
                    // deal for when there are either single or multiple classes
                    if (number > 1){
                        cout << endl << "----------------" << endl << "For " << number << " Classes: " << endl << fixed << setprecision(2) << "GPA: " << GPA << endl << "----------------" << endl << endl;
                    } else{
                        cout << endl << "----------------" << endl << "For " << number << " Class: " << endl << fixed << setprecision(2) << "GPA: " << GPA << endl << "----------------" << endl << endl;
                    }
                } else{
                    
                    // do this because there was a cin before the getline
                    cin.ignore(10000, '\n');
                    
                    // loop through amount of classes
                    for(int k = 0; k < numClasses; k++){
                        for(;;){
                            cout << "Class " << number + 1 << ": ";
                            getline(cin, letterInput);
                            
                            // make lowercase letters work
                            letterInput[0] = toupper(letterInput[0]);
                            
                            // loop until there is a valid input
                            if(letterInput != "A+" && letterInput != "A" && letterInput != "A-" && letterInput != "B+" && letterInput != "B" && letterInput != "B-" && letterInput != "C+" && letterInput != "C" && letterInput != "C-" && letterInput != "D+" && letterInput != "D" && letterInput != "D-" && letterInput != "F"){
                                cout << "THAT IS NOT A VALID INPUT!" << endl;
                                
                            }
                            else{
                                break;
                            }
                        }
                        // add up gpa
                        total += converter(letterInput);
                        
                        // increment class number
                        number++;
                    }
                    
                    // calculate gpa
                    GPA = total / number;
                    
                    // deal for when there are either single or multiple classes
                    if (number > 1){
                        cout << endl << "----------------" << endl << "For " << number << " Classes: " << endl << fixed << setprecision(2) << "GPA: " << GPA << endl << "----------------" << endl << endl;
                    } else{
                        cout << endl << "----------------" << endl << "For " << number << " Class: " << endl << fixed << setprecision(2) << "GPA: " << GPA << endl << "----------------" << endl << endl;
                    }
                    
                }
                
            }
                break;
            // if the user types 3, the program will end
            case 3:
                return 0;
                break;
        }
        
    }
    return 0;
}
