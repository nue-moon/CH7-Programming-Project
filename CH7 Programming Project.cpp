#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

// Reads answers from a file into an array
void readAnswers(const string& filename, char answers[], int size) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        file >> answers[i];
    }
    file.close();
}

// Compares correct vs student answers, returns number missed, and fills arrays
int gradeExam(const char correct[], const char student[],
    int missed[], char missedCorrect[], char missedStudent[],
    int size) {
    int missedCount = 0;
    for (int i = 0; i < size; ++i) {
        if (correct[i] != student[i]) {
            missed[missedCount] = i + 1; // question number
            missedCorrect[missedCount] = correct[i];
            missedStudent[missedCount] = student[i];
            missedCount++;
        }
    }
    return missedCount;
}

// Writes the exam report
void writeReport(const int missed[], const char missedCorrect[], const char missedStudent[],
    int missedCount, int totalQuestions) {
    cout << "\nExam Report Details\n";
    cout << "Number questions missed: " << missedCount << endl;

    if (missedCount > 0) {
        cout << "Missed questions and correct answers:\n";
        cout << "Question   Correct Answer   Your Answer\n";
        for (int i = 0; i < missedCount; ++i) {
            cout << setw(5) << missed[i]
                << setw(15) << missedCorrect[i]
                << setw(15) << missedStudent[i] << endl;
        }
    }

    double score = ((totalQuestions - missedCount) / static_cast<double>(totalQuestions)) * 100.0;
    cout << fixed << setprecision(2);
    cout << "\nTest score: " << score << "%\n";
    cout << (score >= 70.0 ? "You passed the exam." : "You failed the exam.") << endl;
}

int main() {
    const int NUM_QUESTIONS = 20;
    char correct[NUM_QUESTIONS], student[NUM_QUESTIONS];
    int missed[NUM_QUESTIONS];
    char missedCorrect[NUM_QUESTIONS], missedStudent[NUM_QUESTIONS];

    // Read both files into arrays
    readAnswers("CorrectAnswers.txt", correct, NUM_QUESTIONS);
    readAnswers("StudentAnswers.txt", student, NUM_QUESTIONS);

    // Grade the exam
    int missedCount = gradeExam(correct, student, missed, missedCorrect, missedStudent, NUM_QUESTIONS);

    // Write the report
    writeReport(missed, missedCorrect, missedStudent, missedCount, NUM_QUESTIONS);

    return 0;
}