#include <ncurses.h>
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

// class that stores linked list node data
class Node
{
    public:
        // class members
        Node* next;
        int data;
        // class constructor
        Node(int new_data)
        {
            data = new_data;
            next = NULL;
        }
};

// class that stores linked list's head and overall structure
class Linked_List
{
    public:
        // keeps track of Linked_List head
        Node* head;
        // class constructor for void head
        Linked_List()
        {
            head = NULL;
        }
        // adds new Node at end of list
        void add_node(int data)
        {
            Node* new_node = new Node(data);
            if(head != NULL)
            {
                add_node(head, NULL, new_node);
            }
            else
            {
                head = new_node;
                add_successful(head);
            }
        }

        void add_node(Node* current_node, Node* previous_node, Node* new_node)
        {
            if(current_node == NULL)
            {
                current_node = new_node;
                previous_node->next = current_node;
                add_successful(current_node);
            }
            else
            {
                add_node(current_node->next, current_node, new_node);
            }
        }

        void add_successful(Node* current_node)
        {
            clear();
            printw("Node %d successfuly added to the list!\n",
                    current_node->data);
            printw("Press any key to continue . . .");
            getch();
        }

        // deletes node from list
        void delete_node(int delete_this)
        {
            if(head != NULL)
            {
                delete_node(head, NULL, delete_this);
            }
            else
            {
                clear();
                printw("The list is empty!\nPress any key to continue . . .");
                getch();
            }
        }

        // deletes node from list, helper function
        void delete_node(Node* current_node, Node* previous_node, int delete_this)
        {
            if(previous_node == NULL &&
                    current_node->data == delete_this)
            {
                head = current_node->next;
                delete_successful(delete_this);
            }
            else if(previous_node != NULL &&
                    current_node->data == delete_this)
            {
                previous_node->next = current_node->next;
                current_node = NULL;
                delete_successful(delete_this);
            }
            else if (current_node->next != NULL)
            {
                delete_node(current_node->next, current_node, delete_this);
            }
            else
            {
                printw("\nNode does not exist!\nPress any key to continue . . .");
                getch();
            }
        }
        void delete_successful(int node)
        {
            clear();
            printw("Node %d successfuly deleted!\n"
                    "Press any key to continue . . .", node);
            getch();
        }

        // print contents of linked list
        void get_data()
        {
            if(head == NULL)
            {
                clear();
                printw("The list is empty!\nNothing to print.\n");
                printw("Press any key to continue . . .");
                getch();
                return;
            }
            clear();
            printw("Linked List: ");
            printw("%d", head->data);
            if(head->next != NULL)
            {
                printw(", ");
                get_data(head->next);
            }
            else
            {
                printw("\n");
            }
            printw("\nPress any key to continue . . .");
            getch();
        }

        // traverses the linked list and prints contents
        void get_data(Node* current_node)
        {
            printw("%d", current_node->data);
            if(current_node->next != NULL)
            {
                printw(", ");
                get_data(current_node->next);
            }
            else
            {
                printw("\n");
            }
        }
};

class Menu
{
    public:
        char node[80];
        string node_input;
        int new_int;
        Linked_List user_list;

        Menu()
        {
            prompt();
            endwin();
        }
        void prompt()
        {
            // init ncurses
            initscr();
            clear();
            echo();
            // main menu prompt
            printw("Welcome to Joanne's Linked List Program (JLLP)!\n");
            printw("Please choose from the following menu: \n");
            printw("\t1. Add Node\n");
            printw("\t2. Delete Node\n");
            printw("\t3. Print Linked List\n");
            printw("\t4. Quit\n");
            printw("Input: ");

            switch(getch())
            {
                // case for adding node
                case '1':
                    clear();
                    printw("Press 'Backspace' key to go back to main menu . . .");
                    printw("\nInt to add: ");
                    try
                    {
                        getstr(node);
                    }
                    catch(...)
                    {
                        clear();
                        printw("Error! Invalid input!");
                        getch();
                    }
                    try
                    {
                        user_list.add_node(stoi(char_array_to_string(node)));
                    }
                    catch(...)
                    {
                        clear();
                        printw("Error! Invalid input!");
                        getch();
                    }
                    prompt();
                    break;
                // case for deleting node
                case '2':
                    clear();
                    printw("Press 'Backspace' key to go back to main menu . . .");
                    printw("Int to delete: ");
                    try
                    {
                        getstr(node);
                    }
                    catch(...)
                    {
                        clear();
                        printw("Error! Invalid input!");
                    }
                    try
                    {
                        user_list.delete_node(stoi(char_array_to_string(node)));
                    }
                    catch(...)
                    {
                        clear();
                        printw("Error! Invalid input!");
                    }
                    prompt();
                    break;
                case '3':
                    clear();
                    user_list.get_data();
                    prompt();
                    break;
                case '4':
                    clear();
                    printw("Are you sure you want to quit( y / n )?");
                    switch(getch())
                    {
                        case 'n':
                            prompt();
                            break;
                        case 'y':
                            endwin();
                            return;
                        default:
                            printw("That's not a valid entry. Please enter \
                                    'y' to quit and 'n' to go back");
                            prompt();
                            break;
                    }
            }
        }

        // converts char array to string for stoi function
        string char_array_to_string(char *array)
        {
            string return_this = "";
            int size = sizeof(array)/sizeof(char);
            for (int i = 0; i < size; i++)
            {
                return_this = return_this + array[i];
            }
            return return_this;
        }
};

// main function
int main()
{
    Menu menu;
    return 0;
}
