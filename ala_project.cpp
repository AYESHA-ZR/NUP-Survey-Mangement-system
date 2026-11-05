#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <sstream>
#include<stdexcept>

using namespace std;

template <typename T>
class Get {
public:
    virtual T getRating(const string& question) = 0;
    virtual string getMaskedPassword() = 0;
    virtual string getRecommendation(float avg) = 0;
};

class Set : public Get<int> {
public:
    int getRating(const string& question)  {
        int choice;
        while (true) {
            try {
                cout << question << endl;
                cout << "Select an option"<<endl;
                cout << "1. Very Poor"<<endl;
                cout << "2. Poor\n"<<endl;
                cout << "3. Average"<<endl;
                cout << "4. Good"<<endl;
                cout << "5. Excellent"<<endl;
                cout << "Enter your choice (1-5)"<<endl;
                if (!(cin >> choice)) {
                    throw invalid_argument("Invalid input type.");
                }
                if (choice < 1 || choice > 5) {
                    throw out_of_range("Choice must be between 1 and 5.");
                }
                return choice;
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    string getMaskedPassword()  {
        string password;
        char ch;
        cout << "\nEnter admin password: ";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                password += ch;
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }

    string getRecommendation(float avg)  {
        if (avg >= 3.5)
            return "Advanced Programming Course";
        else if (avg >= 2.5)
            return "Intermediate Problem Solving Course";
        else
            return "Beginner's Guide to Programming";
    }
};

class Question {
public:
    string questionText;
    vector<int> ratings;
};

struct StudentData {
    string name;
    string email;
    int id;
    float avgRating;
    vector<int> answers;
};

class Restrictions {
protected:
    bool isValidName(const string& name) {
        if (name.length() < 2) return false;
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ')
                return false;
        }
        return true;
    }

    bool isValidEmail(const string& email) {
        bool hasAt = false, hasDot = false;
        for (char ch : email) {
            if (ch == '@') hasAt = true;
            if (ch == '.') hasDot = true;
        }
        return hasAt && hasDot && email.find(' ') == string::npos && email.length() >= 6;
    }

    bool isValidID(int id) {
        return id >= 1000 && id <= 9999;
    }

    void inputValidUser(string& name, string& email, int& id) {
        cin.ignore();
        bool valid;

        do {
            cout << "Enter Name: ";
            getline(cin, name);
            valid = isValidName(name);
            if (!valid) cout << "Invalid name Only letters and spaces allowed."<<endl;
        } while (!valid);

        do {
            cout << "Enter Email: ";
            getline(cin, email);
            valid = isValidEmail(email);
            if (!valid) cout << "Invalid email format."<<endl;
        } while (!valid);

        do {
            cout << "Enter ID (1000 - 9999): ";
            if (cin >> id && isValidID(id)) break;
            cout << "Invalid ID. Must be between 1000 and 9999."<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } while (true);
    }
};

class Survey : public Set, public Restrictions {
private:
    vector<Question> questions;
    vector<StudentData> studentRecords;

public:
    void readQuestionsFromFile() {
        ifstream file("questions.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open questions.txt"<<endl;
            exit(1);
        }

        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                Question q;
                q.questionText = line;
                questions.push_back(q);
            }
        }
        file.close();
    }

    void loadQuestionRatings() {
        ifstream file("question_ratings.txt");
        string line;
        int i = 0;
        while (getline(file, line) && i < questions.size()) {
            istringstream iss(line);
            int r;
            while (iss >> r) questions[i].ratings.push_back(r);
            i++;
        }
        file.close();
    }

    void saveQuestionRatings() {
        ofstream file("question_ratings.txt");
        for (const auto& q : questions) {
            for (int r : q.ratings) file << r << " ";
            file << "\n";
        }
        file.close();
    }

    void Video() {
        int result = system("start \"\" \"C:\\Users\\MoNaRcH_DyNeStY\\Desktop\\project\\NUP Survey.mp4\"");
        if (result != 0) {
            cout << "Error: Unable to play the video. Please check the file path."<<endl;
        } else {
            cout << "[Playing video... Please wait 10 seconds.]"<<endl;
            Sleep(10000);
        }
    }

    void playVideo() {
        int result = system("start \"\" \"C:\\Users\\MoNaRcH_DyNeStY\\Desktop\\project\\Process Video.mp4\"");
        if (result != 0) {
            cout << "Error: Unable to play the video. Please check the file path."<<endl;
        } else {
            cout << "[Playing video... Please wait 10 seconds.]"<<endl;
            Sleep(10000);
        }
    }
    void pic(){
    	   system("start \"\" \"C:\\Users\\MoNaRcH_DyNeStY\\Desktop\\project\\img 2.png\"");
       
	}

    void conductSurveyForStudent(int studentIndex) {
        string name, email;
        int id;

        cout << "\n--- Student " << studentIndex + 1 << " ---"<<endl;
    string ch;
    do {
        cout << "Do you want to see the introduction video? (yes/no): ";
        cin >> ch;

        if (ch == "y" || ch == "yes" || ch == "Y" || ch == "YES" || ch == "Yes") {
            Video();
            break;
        } else if (ch == "n" || ch == "no" || ch == "N" || ch == "NO" || ch == "No") {
            cout << "Okay, skipping the video." << endl;
            break;
        } else {
            cout << "Invalid input. Please enter a valid input." << endl;
        }
    } while (true);

    cout << endl;

    string watch;
    do {
        cout << "Do you want to watch the process video? (yes/no): ";
        cin >> watch;

        if (watch == "y" || watch == "yes" || watch == "Y" || watch == "YES" || watch == "Yes") {
            playVideo();
            break;
        } else if (watch == "n" || watch == "no" || watch == "N" || watch == "NO" || watch == "No") {
            cout << "Okay, skipping the process video." << endl;
            break;
        } else {
            cout << "Invalid input. Please enter a valid input." << endl;
        }
    } while (true);

    string pi;
    do {
        cout << "Do you want to see a related pic about this (yes/no)? ";
        cin >> pi;

        if (pi == "y" || pi == "yes" || pi == "Y" || pi == "YES" || pi == "Yes") {
            pic();
            break;
        } else if (pi == "n" || pi == "no" || pi == "N" || pi == "NO" || pi == "No") {
            cout << "Okay, skipping the picture." << endl;
            break;
        } else {
            cout << "Invalid input. Please enter a valid input." << endl;
        }
    } while (true);

    
       
     
        inputValidUser(name, email, id);

        vector<int> answers;
        for (size_t i = 0; i < questions.size(); ++i) {
            int rating = getRating(questions[i].questionText);
            questions[i].ratings.push_back(rating);
            answers.push_back(rating);
        }

        float sum = 0;
        for (int r : answers) 
		{
			sum += r;
		}
        float avg = sum / answers.size();
        
        cout << endl;
        for (int i = 0; i < 20; i++) 
		{
		cout << "*";
	}
        cout << "\nAverage Rating for " << name << ": " << fixed << " \t " << avg << endl;
        for (int i = 0; i < 20; i++) 
		{
			cout << "*";
		}
        cout << endl;

        cout << "\n--- Recommendation ---"<<endl;
        cout << "Recommendation: " << getRecommendation(avg) << endl;

        StudentData student = {name, email, id, avg, answers};
        studentRecords.push_back(student);

        ofstream file("student_results.txt", ios::app);
        file << "Name: " << name << ", Email: " << email << ", ID: " << id << ", Avg Rating: " << avg << endl;
        for (size_t i = 0; i < questions.size(); ++i) {
            file << "Q" << i + 1 << ": " << questions[i].questionText << " => " << answers[i] << endl;
        }
        file << "-----------------------------------------\n";
        file.close();

        cout << "--------------------------------------------------------\n";
    }

    void startSurvey() {
        int totalStudents;
        while (true) {
            cout << "Enter number of students: ";
            if (cin >> totalStudents && totalStudents > 0) break;
            else {
                cout << "Invalid input. Enter a valid number."<<endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        for (int i = 0; i < totalStudents; ++i) {
            conductSurveyForStudent(i);
        }

        saveQuestionRatings();
    }

    void logAdminAttempt(const string& password) {
        ofstream log("admin_log.txt", ios::app);
        time_t now = time(0);
        log << "Login attempt at " << ctime(&now) << "Password entered: [REDACTED]"<<endl;
        log.close();
    }

    void viewResultsAsAdmin() {
        float universitySum = 0;
        int totalResponses = 0;
        for (const auto& q : questions) {
            for (int r : q.ratings) {
                universitySum += r;
                totalResponses++;
            }
        }

        if (totalResponses == 0) {
            cout << "No data available yet."<<endl;
            return;
        }

        float universityRating = universitySum / totalResponses;
        cout << "\n=============================="<<endl;
        cout << "Admin View - Overall University Rating: " << fixed << "\t" << universityRating << endl;
        cout << "=============================="<<endl;
    }

    void viewIndividualReports() {
        if (studentRecords.empty()) {
            cout << "No student data available.\n";
            return;
        }

        for (const auto& student : studentRecords)
		 {
            cout << "\n--- Report for " << student.name << " ---"<<endl;
            cout << "Email: " << student.email << ", ID: " << student.id << endl;
            cout << "Average Rating: " << fixed << " \t " << student.avgRating << endl;

            for (size_t i = 0; i < student.answers.size(); ++i)
			 {
                cout << "Q" << i + 1 << ": " << questions[i].questionText
                     << " => " << student.answers[i] << endl;
            }

            cout << "Recommendation: " << getRecommendation(student.avgRating) << endl;
            cout << "----------------------------------------"<<endl;
        }
    }

    void viewAverageRatingPerQuestion()
	 {
        cout << "\n--- Average Rating Per Question ---\n";
        for (size_t i = 0; i < questions.size(); ++i) 
		{
            const auto& q = questions[i];
            float sum = 0;
            for (int r : q.ratings) {
                sum += r;
            }
            float avg = (q.ratings.empty()) ? 0 : sum / q.ratings.size();
            cout << "Q" << i + 1 << ": " << q.questionText << "\n";
            cout << "Average Rating: " << fixed << " \t " << avg << "\n";
            cout << "----------------------------------------\n";
        }
    }
};

int main() {
    try {
        cout << "    -----------------------------------------------            " << endl;
        for (int i = 0; i < 50; i++) {
            cout << "*";
        }
        cout << endl;
        cout << "    NATIONAL UNIVERSITY OF PAKISTAN - STUDENT SURVEY SYSTEM\n";
        for (int i = 0; i < 50; i++) {
            cout << "*";
        }
        cout << endl;
        cout << "    -----------------------------------------------            " << endl;

        Survey* s = new Survey;


        try {
            s->readQuestionsFromFile();
            s->loadQuestionRatings();
        } catch (const exception& e) {
            cerr << "Error while loading questions or ratings: " << e.what() << endl;
            delete s;
            return 1;
        }

        char again;
        do {
            try {
                
               char role;
           do {
              cout << "\nAre you a Student or Admin? (s/a): ";
             cin >> role;
             cin.ignore();

            if (role == 's' || role == 'a') {
              break;
              } else {
               cout << "Invalid input. Please enter a valid input (s for Student, a for Admin).\n";
      
              }
             } while (true);
                if (tolower(role) == 's') {
                    s->startSurvey();
                } else if (tolower(role) == 'a') {
                    string enteredPass = s->getMaskedPassword();
                    s->logAdminAttempt(enteredPass);

                    if (enteredPass == "admin123") {
                        cout << "\n--- Admin Access Granted ---\n";
                        int choice;
                        do {
                            cout << "\nAdmin Menu:\n";
                            cout << "1. View Overall University Rating\n";
                            cout << "2. View Individual Student Reports\n";
                            cout << "3. View Average Rating per Question\n";
                            cout << "4. Exit Admin Panel\n";
                            cout << "Enter your choice: ";

                            if (!(cin >> choice)) {
                                throw runtime_error("Invalid input. Please enter a number.");
                            }

                            switch (choice) {
                                case 1:
                                    s->viewResultsAsAdmin();
                                    break;
                                case 2:
                                    s->viewIndividualReports();
                                    break;
                                case 3:
                                    s->viewAverageRatingPerQuestion();
                                    break;
                                case 4:
                                    cout << "Exiting Admin Panel...\n";
                                    break;
                                default:
                                    cout << "Invalid choice. Please select from the menu.\n";
                            }
                        } while (choice != 4);
                    } else {
                        cout << "Incorrect Password. Access Denied.\n";
                    }
                } else {
                    cout << "Invalid role entered. Please enter 's' or 'a'.\n";
                }

                cout << "\nDo you want to use the system again? (y/n): ";
                cin >> again;
            }
            catch (const exception& e) {
                cerr << "An error occurred: " << e.what() << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                again = 'y'; 
            }

        } while (tolower(again) == 'y');

        cout << "Thank you for using the Student Survey System. Goodbye!\n";

        delete s;
    }
    catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
