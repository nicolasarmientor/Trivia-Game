// Project 4
// Nicolas Sarmiento
// 904275018
// nzs0102
// project4_Sarmiento_nzs0102.cpp

// Needed some help to comprehend how to properly insert input data into nodes. Used stackoverflow as a resource to implement it (Line 146).
// Had compiling issues on the AU Server, used 'nullptr' and had to replace this for 'NULL'

// How to compile version 1: g++ -DUNIT_TESTING -o project4_Sarmiento_nzs0102 project4_Sarmiento_nzs0102.cpp
// How to compile version 2: g++ -o project4_Sarmiento_nzs0102 project4_Sarmiento_nzs0102.cpp
// How to execute both versions: ./project4_Sarmiento_nzs0102

//------- Library imports -------//

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

//------- Flag boolean variable for differing displaying purposes -------//

bool flag = true;

//------- Structure creation for nodes -------//

struct trivia_node {
    string question;
    string answer;
    int points;
    trivia_node* next; // Pointer allowing the trivia_node structure to be used as a linked list

    trivia_node(string q, string a, int p) : question(q), answer(a), points(p), next(NULL) {} // Constructor for the node structure
};

//------- Structure creation for question list -------//

struct trivia_list {
    trivia_node* head;

    trivia_list() : head(NULL) {} // List constructor

    //------- Addition of a new node and linking process to current node -------//

    void add_node(string question, string answer, int points) {
        trivia_node* newNode = new trivia_node(question, answer, points);
        newNode->next = head;
        head = newNode;
    }

    //------- Default questions, answers, and points (In case user inputs less that 3 required) -------//

    void initialize() {
        add_node("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
        add_node("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
        add_node("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)", "Wii Sports", 20);
    }

    //------- Destructor for the current linked list -------//

    ~trivia_list() {
        while (head != NULL) {
            trivia_node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

//------- User question prompt function for both versions-------//

int prompt_questions(trivia_list& list, int number_of_questions) {
    trivia_node* current = list.head;
    int total_points = 0;

    //------- Loop for question, answer, and points prompt -------//

    for (int i = 0; i < number_of_questions && current != NULL; ++i) {

        //------- Version 2 display loop -------//

        if (flag) {
            cout << " " << endl;
            cout << "Question: " << current->question << endl;
            cout << "Answer: ";
            string user_answer;
            getline(cin, user_answer);

            //------- Conditional statement to determine if answer is correct or incorrect -------//

            if (user_answer == current->answer) {
                cout << "Your answer is correct! You receive " << current->points << " points." << endl;
                total_points += current->points;
            } else {
                cout << "Your answer is wrong. The correct answer is " << current->answer << endl;
            }

            current = current->next;
            cout << "Your total points: " << total_points << endl;
        } else {

            //------- Version 1 display loop -------//

            cout << "Question: " << current->question << endl;
            cout << "Answer: ";
            string user_answer;
            getline(cin, user_answer);

            //------- Conditional statement to determine if answer is correct or incorrect -------//

            if (user_answer == current->answer) {
                cout << "Your answer is correct! You receive " << current->points << " points." << endl;
                total_points += current->points;
            } else {
                cout << "Your answer is wrong. The correct answer is " << current->answer << endl;
            }

            current = current->next;
            cout << "Your total points: " << total_points << endl;
        }
    }

    //------- Warning message when user attempts to input no questions -------//

    if (number_of_questions == 0) {
        cout << "Warning - the number of trivia to be asked must equal to or be larger than 1" << endl;
    }

    //------- Warning message when user attempts to input more than 3 questions -------//

    if (current == NULL && number_of_questions > 3) {
        cout << "Warning - There are only 3 trivia questions in the list." << endl;
    }
    return total_points;
}

//***------- VERSION 1 (Debugging version)-------***//

//------- Debugging test driver for each code case -------//

void test_driver() {
    trivia_list list;
    list.initialize();

    cout << " " << endl;
    cout << "*** This is a Debugging Version ***" << endl;
    cout << " " << endl;

    //------- Case 1: No questions are asked -------//

    cout << "Unit test Case 1: Ask no question. The program should give a warning message." << endl;
    int points = prompt_questions(list, 0);
    assert(points == 0);
    cout << "Case 1 Passed" << endl;
    cout << " " << endl;

    //------- Case 2.1: 1 question asked and answered wrong -------//

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    points = prompt_questions(list, 1);
    assert(points == 0);
    cout << " " << endl;
    cout << "Case 2.1 passed" << endl;
    cout << " " << endl;

    //------- Case 2.2: 1 question asked and answered right -------//

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    points = prompt_questions(list, 1);
    assert(points > 0);
    cout << " " << endl;
    cout << "Case 2.2 passed" << endl;
    cout << " " << endl;

    //------- Case 3: 3 questions asked -------//

    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list." << endl;
    points = prompt_questions(list, 3);
    assert(points >= 0);
    cout << " " << endl;
    cout << "Case 3 passed" << endl;
    cout << " " << endl;

    //------- Case 4: 5 questions asked -------//

    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    points = prompt_questions(list, 5);
    assert(points >= 0);
    cout << "Case 4 passed" << endl;
    cout << " " << endl;

    cout << "*** End of the Debugging Version ***" << endl;
    cout << " " << endl;
}

//***------- VERSION 2 (Product version)-------***//

//------- Execution of inquiry and compilation of data -------//

void run() { // Used external help (stackoverflow) for properly storing data into respective nodes
    trivia_list list;
    list.initialize();

    string question;
    string answer;
    int points;
    string ctn;

    //------- Loop to prompt, retrieve, and add user questions and answers into respective nodes -------//

    cout << " " << endl;
    cout << "*** Welcome to Sarmiento's trivia quiz game ***" << endl;
    cout << " " << endl;  

    do {
        cout << "Enter a question: ";
        getline(cin, question);
        cout << "Enter an answer: ";
        getline(cin, answer);
        cout << "Enter award points: ";
        cin >> points;
        cin.ignore();

        list.add_node(question, answer, points);

        cout << "Continue? (Yes/No): ";
        getline(cin, ctn);
    } while (ctn == "Yes" || ctn == "yes");

    prompt_questions(list, 3); // Limit of question to be asked

    cout << " " << endl;
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***" << endl;
    cout << " " << endl;
}

//------- Main function of the program -------//

int main () {

    //------- Code version manipulation -------//

    #ifdef UNIT_TESTING // Version 1: Debugging and test cases with questions and answers
        test_driver();
    #else
        run();  // Version 2: Regular operation and execution of program
    #endif
        return 0;
}