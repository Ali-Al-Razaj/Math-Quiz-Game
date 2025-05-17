// Math Quiz Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////
enum enQuestionLevel { easyLevel = 1, medLevel = 2, hardLevel = 3, mixLevel = 4 };
enum enOperationType { add = 1, sub = 2, mult = 3, divide = 4, mixOp = 5 };
////////////////////////////////////////////////////////////////////////////////////////////////////
string getOpTypeSymbol(enOperationType opType)
{
    switch (opType)
    {
    case enOperationType::add:
        return "+";
    case enOperationType::sub:
        return "-";
    case enOperationType::mult:
        return "x";
    case enOperationType::divide:
        return "/";
    default:
        return "Mix";
    }
}
string GetQuestionLevelText(enQuestionLevel questionLevel)
{
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevelText[questionLevel - 1];
}
int randomNumber(int from, int to)
{
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void setScreenColor(bool right)
{
    if (right)
        system("color 2f");
    else
    {
        system("color 4f");
        cout << "\a";
    }
}
short readHowManyQuestions()
{
    short numberOfQuestions;
    do
    {
        cout << "How Many Question Do You To Answer? ";
        cin >> numberOfQuestions;
    } while (numberOfQuestions < 1 || numberOfQuestions > 10);
    return numberOfQuestions;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
enQuestionLevel readQuestionsLevel()
{
    short questionLevel = 0;
    do
    {
        cout << "Enter Questions Level [1]-Easy [2]-Med [3]-Hard [4]-Mix ? ";
        cin >> questionLevel;
    } while (questionLevel < 1 || questionLevel > 4);
    return (enQuestionLevel)questionLevel;
}
enOperationType readOpType()
{
    short opType = 0;
    do
    {
        cout << "Enter Operation Type [1]-Add [2]-Sub [3]-Mul [4]-Div [5]-Mix ? ";
        cin >> opType;
    } while (opType < 1 || opType > 5);
    return (enOperationType)opType;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
struct stQuestion
{
    int number1 = 0;
    int number2 = 0;
    enQuestionLevel questionLevel;
    enOperationType oprationType;
    int correctAnswer = 0;
    int playerAnswer = 0;
    bool answerResult = false;
};
struct stQuizz
{
    stQuestion questionList[100];
    short numberOfQuestions;
    enQuestionLevel questionsLevel;
    enOperationType oprationsType;
    short numberOfWrongAnswers = 0;
    short numberOfRightAnswers = 0;
    bool isPass = false;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
int simpleCalculator(int Number1, int Number2, enOperationType opType)
{
    switch (opType)
    {
    case enOperationType::add:
        return Number1 + Number2;
    case enOperationType::sub:
        return Number1 - Number2;
    case enOperationType::mult:
        return Number1 * Number2;
    case enOperationType::divide:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
enOperationType getRandomOperationType()
{
    int op = randomNumber(1, 4);
    return (enOperationType)op;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
stQuestion generateQuestion(enQuestionLevel questionLevel, enOperationType opType)
{
    stQuestion question;


    if (questionLevel == enQuestionLevel::mixLevel)
    {
        questionLevel = (enQuestionLevel)randomNumber(1, 3);
    }
    if (opType == enOperationType::mixOp)
    {
        opType = getRandomOperationType();
    }


    question.oprationType = opType;

    switch (questionLevel)
    {
    case enQuestionLevel::easyLevel:
        question.number1 = randomNumber(1, 10);
        question.number2 = randomNumber(1, 10);
        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.oprationType);
        question.questionLevel = questionLevel;
        return question;

    case enQuestionLevel::medLevel:
        question.number1 = randomNumber(10, 50);
        question.number2 = randomNumber(10, 50);
        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.oprationType);
        question.questionLevel = questionLevel;
        return question;

    case enQuestionLevel::hardLevel:
        question.number1 = randomNumber(50, 100);
        question.number2 = randomNumber(50, 100);
        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.oprationType);
        question.questionLevel = questionLevel;
        return question;
    }

    return question;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void generateQuizzQuestions(stQuizz& quizz)
{
    for (short question = 0; question < quizz.numberOfQuestions; question++)
    {
        quizz.questionList[question] = generateQuestion(quizz.questionsLevel, quizz.oprationsType);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int readQuestionAnswer()
{
    int answer = 0;
    cin >> answer;
    return answer;
}

void printTheQuestion(stQuizz& quizz, short questionNumber)
{
    cout << endl;
    cout << "Question [" << questionNumber + 1 << "/" << quizz.numberOfQuestions << "] \n\n";
    cout << quizz.questionList[questionNumber].number1 << endl;
    cout << quizz.questionList[questionNumber].number2 << " ";
    cout << getOpTypeSymbol(quizz.questionList[questionNumber].oprationType);
    cout << "\n_________" << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void correctTheQuestionAnswer(stQuizz& quizz, short questionNumber)
{
    if (quizz.questionList[questionNumber].correctAnswer != quizz.questionList[questionNumber].playerAnswer)
    {
        quizz.questionList[questionNumber].answerResult = false;
        quizz.numberOfWrongAnswers++;

        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer Is: ";
        cout << quizz.questionList[questionNumber].correctAnswer;
        cout << endl;
    }
    else
    {
        quizz.questionList[questionNumber].answerResult = true;
        quizz.numberOfRightAnswers++;

        cout << "Right Answer :-) \n";
    }
    cout << endl;

    setScreenColor(quizz.questionList[questionNumber].answerResult);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.numberOfQuestions; QuestionNumber++)
    {
        printTheQuestion(Quizz, QuestionNumber);
        Quizz.questionList[QuestionNumber].playerAnswer = readQuestionAnswer();
        correctTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.numberOfRightAnswers >= Quizz.numberOfWrongAnswers);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
string getFinalResultText(bool pass)
{
    if (pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}
void printQuizzResults(stQuizz quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is " << getFinalResultText(quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions: " << quizz.numberOfQuestions << endl;
    cout << "Questions Level    : " << GetQuestionLevelText(quizz.questionsLevel) << endl;
    cout << "OpType             : " << getOpTypeSymbol(quizz.oprationsType) << endl;
    cout << "Number of Right Answers: " << quizz.numberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << quizz.numberOfWrongAnswers << endl;
    cout << "______________________________\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void playMathGame()
{
    stQuizz quizz;

    quizz.numberOfQuestions = readHowManyQuestions();
    quizz.questionsLevel = readQuestionsLevel();
    quizz.oprationsType = readOpType();

    generateQuizzQuestions(quizz);
    AskAndCorrectQuestionListAnswers(quizz);
    printQuizzResults(quizz);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void startGame()
{
    char playAgain = 'Y';
    do
    {
        ResetScreen();
        playMathGame();

        cout << endl << "Do you want to play again? Y/N? ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    srand((unsigned)time(NULL));

    startGame();

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

