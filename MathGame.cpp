#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

struct stQuizInfo {
	int numOfQuestions = 0;
	int quizLevel = 0;
	string quizLevel_txt = " ";
	int operationType = 0;
	string operationType_txt = " ";
	int numOfCorrect = 0;
	int numOfWrong = 0;
	string finalResult = " ";
};

void redScreen() {
	system("color 40");
	cout << "\a";
}

void greenScreen() {
	system("color 20");
}

void resetDisplay() {
	system("Color 0F");
	system("cls");
}

int readPositiveNumber(string massege) {
	int num = 0;
	do {
		cout << massege;
		cin >> num;
	} while (num <= 0 || num > 8);
	return num;
}

int randomNumber(int from, int to) {
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

int questionLevel(int qLevel) {

	if (qLevel == 1) {
		return randomNumber(1, 10);
	}
	else if (qLevel == 2) {
		return randomNumber(10, 20);
	}
	else if (qLevel == 3) {
		return randomNumber(20, 99);
	}
	else if (qLevel == 4) {
		return questionLevel(randomNumber(1, 3));
	}
}

int questionOperationType(int opType, int qLevel) {

	int num1 = questionLevel(qLevel), num2 = questionLevel(qLevel);
	if (opType == 1) {
		cout << num1 << endl << num2 << " +\n" << "____________\n";
		return num1 + num2;
	}
	else if (opType == 2) {
		cout << num1 << endl << num2 << " -\n" << "____________\n";
		return num1 - num2;
	}
	else if (opType == 3) {
		cout << num1 << endl << num2 << " *\n" << "____________\n";
		return num1 * num2;
	}
	else if (opType == 4) {
		cout << num1 << endl << num2 << " /\n" << "____________\n";
		return num1 / num2;
	}
	else if (opType == 5) {
		return questionOperationType(randomNumber(1, 4), qLevel);
	}
}

void answerResult(stQuizInfo& quizInfo, int correctAnswer, int userAnswer) {

	bool result = userAnswer == correctAnswer;
	if (result) {
		greenScreen();
		cout << "Correct :-)" << endl;
		quizInfo.numOfCorrect++;
	}
	else {
		cout << "The right answer is: " << correctAnswer << endl;
		redScreen();
		cout << "Wrong :-(" << endl;
		quizInfo.numOfWrong++;
	}
}

void showQuestion(stQuizInfo& quizInfo, int opType, int qLevel) {

	int correctAnswer = questionOperationType(opType, qLevel);
	int userAnswer = 0;
	cin >> userAnswer;

	answerResult(quizInfo, correctAnswer, userAnswer);
}

void showQuizResults(stQuizInfo& quiz) {

	if (quiz.numOfCorrect >= quiz.numOfWrong) {
		greenScreen();
		quiz.finalResult = "PASS :-)";
	}
	else {
		redScreen();
		quiz.finalResult = "FAIL :-(";
	}


	cout << "\n-----------------------------------\n";
	cout << "Final results is: " << quiz.finalResult;
	cout << "\n-----------------------------------\n";
	cout << "Number Of Questions: " << quiz.numOfQuestions << endl;
	cout << "Questions Level    : " << quiz.quizLevel_txt << endl;
	cout << "Operation Type     : " << quiz.operationType_txt << endl;
	cout << "Number of Right Answers: " << quiz.numOfCorrect << endl;
	cout << "Number of Wrong Answers: " << quiz.numOfWrong << endl;
	cout << "\n-----------------------------------\n";
}

void enterQuizInfo(stQuizInfo& quiz) {

	quiz.numOfQuestions = readPositiveNumber("Enter how many Questions do you want?: ");
	quiz.quizLevel = readPositiveNumber("Choose The level of Quiz: [1]Easy - [2]Med - [3]Hard - [4]Mix? -> ");
	quiz.operationType = readPositiveNumber("Select Type Of Operations: [1]Add - [2]Sub - [3]Mul - [4]Div - [5]Mix? -> ");

	switch (quiz.quizLevel) {
	case 1: quiz.quizLevel_txt = "Easy";
	case 2: quiz.quizLevel_txt = "Med";
	case 3: quiz.quizLevel_txt = "Hard";
	case 4: quiz.quizLevel_txt = "Mix";
	}
	switch (quiz.operationType) {
	case 1: quiz.operationType_txt = " + ";
	case 2: quiz.operationType_txt = " - ";
	case 3: quiz.operationType_txt = " * ";
	case 4: quiz.operationType_txt = " / ";
	case 5: quiz.operationType_txt = "Mix";
	}
}

void startSession() {

	stQuizInfo quiz;
	enterQuizInfo(quiz);
	for (int question = 1; question <= quiz.numOfQuestions; question++) {

		cout << "\nQuestion [" << question << "/" << quiz.numOfQuestions << "]  : \n\n";

		showQuestion(quiz, quiz.operationType, quiz.quizLevel);
	}
	showQuizResults(quiz);
}

void startQuiz() {

	char replay;
	do {
		resetDisplay();
		startSession();
		cout << "do you Want to start another Quiz? Y/N: ?:";
		cin >> replay;

	} while (replay == 'y' || replay == 'Y');

}

int main() {

	srand((unsigned)time(NULL));

	startQuiz();
}
