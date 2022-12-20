/**************************************************************
 *                    To Do List Manager
 *
 * Author:        Jameson Watson  
 * StID:          201695569
 * Course:        COMP 1633
 * Assignment:    4 part 2
 * Instructor:    Paul Pospisil
 * Due Date::     March 29, 2021
 *
 * Source File:   a4p2.cpp
 *
 * Purpose: 
 * This application helps a user create and manage a "to do" list.
 * 
 * List Structure:
 * 1. The list consists of a series of items, each of which is 
 *    assigned a priority (HIGH, MEDIUM, LOW). 
 *    High priority items are stored at the front of the list, 
 *    followed by medium priority and finally low priority items.
 * 2. An empty To Do list is valid.
 *
 * The exact method of implementing the list is done in a list library.
 * However, this program creates and maintains a head pointer to the
 * the list which if of type To_Do_Item_Ptr.
 *
 * List Initialization:
 * When the program begins execution, the user has two options 
 * for initializing the To Do list:
 * 1. read an existing list from an ASCII file (user is prompted
 *    for the input file name)
 * 2. begin with an empty list (user presses ENTER when prompted
 *    for the input file name)
 *
 * Menu Options:
 * The user may select from one of five options for managing the 
 * list:
 *     d - display the list under priority headings (the item
 *         number and description is shown for each entry on the
 *         list)
 *     a - add a new item to the list (the user is prompted for 
 *         the item description and priority)
 *     r - remove an item from the list (the user is asked to
 *         confirm the request for deletion)
 *     u - modify an existing item's priority (the user is
 *         asked to confirm the request for update and the new
 *         priority, if necessary
 *     q - exit the program (the user is prompted for the name
 *         of a file to which the list contents will be written)
 *
 * Supporting Modules:
 *     list.cpp   - for all list processing functions
 *     ioutil.cpp - for reliable reading of input from the keyboard
 *
 * Error Checking and Data Validation:
 * The following constraints apply:
 *     input file name  = string length 0 to 29 (arbitrary)
 *     output file name = string length 1 to 29
 *     item description = string length 1 to 60
 *     item priority    = one of high ('h' converted to 3),
 *                               medium ('m' converted to 2),
 *                               or low ('l' converted to 1)
 *     item number      = integer > 0
 *
 * Format of the Input File:
 * This program does not check for errors in the input file
 * data. The following format is assumed:
 * 1. each line in the input file represents one item and has
 *    the following structure:
 *          integer   (one of 3, 2, or 1)
 *          space
 *          string    (length 1 - 60)
 *          newline
 * 2. the file contains items in order of priority: 
 *         all items with priority = 3
 *         followed by all items with priority = 2
 *         followed by all itmes with priority = 1 
 * 3. there may be no items in a priority category
 * 4. an empty file is valid
 *
 * Input routines and EOF
 * 
 * all input is done using the routines supplied by the ioutil
 * library. All of these routines return an eof flag. Since when
 * set the library restores the input state to good it is 
 * possible to ignore the flag, however, the value returned in
 * the input variables will be undefined.
 * 
 * Therefore, this program operates under the assumption that
 * should the user ever enter a ctrl-d they are requesting the
 * termination of the program. As such, this is the way the 
 * main program handles an eof.
 **************************************************************/


#include <fstream>
#include <cstring>
// 1 
// #include "todo_list.h"
#include "ToDoList.h"
#include "ioutil.h"
using namespace std;

void show_menu();
// 2
// void do_display (To_Do_Item_Ptr head);
// this should seem wrong, but at the current time it is required
void do_display (const ToDoList &list);
// 3
// void do_add (To_Do_Item_Ptr &head, bool & eof);
void do_add (ToDoList &list, bool & eof);
// 4
// void do_remove (To_Do_Item_Ptr &head, bool & eof);
void do_remove (ToDoList &list, bool & eof);
// 5
// void do_update (To_Do_Item_Ptr &head, bool & eof);
void do_update (ToDoList &list, bool & eof);

// 6
// void do_quit (To_Do_Item_Ptr &head);
void do_quit (ToDoList &list);

int get_priority (bool & eof);
int get_position (bool & eof);

const char ADD       = 'a';      // Menu Options
const char REMOVE    = 'r';
const char DISPLAY   = 'd';
const char UPDATE    = 'u';
const char QUIT      = 'q';
const char HIGH_CH   = 'h';      // User input priority levels
const char MEDIUM_CH = 'm';
const char LOW_CH    = 'l';

const int INVALID_POSITION = -99;// value returned if eof entered in get_postion
const int FILENAME_LENGTH = 30;
const int CHAR_LENGTH     = 2;   // length of array used to read in a char
                                 //  using ioutil
const int EXTRA           = 20;  // needed for extra space
                                 //  when creating a custom prompt
const int PROMPT_LENGTH   = DESCRIPTION_LENGTH + EXTRA + 1;

int main ()
{
    char           inputFileName[FILENAME_LENGTH+1];
    ifstream       inFile;
    char           choice[CHAR_LENGTH];
// 7
//  To_Do_Item_Ptr ToDoList = NULL;
    ToDoList       list;
    bool           goodToGo = false,
	save_done = false,
	eof;
    
    readString ("Enter name of input file: ", inputFileName, FILENAME_LENGTH, 
		0, eof);
  if (eof)
  {
    cout << "\nEOF entered for input filename -- program terminating" << endl;
  }
  else
  {
    if (strlen(inputFileName) == 0)
    {
      goodToGo = true;
    }
    else
    {
      inFile.open(inputFileName);
      if (inFile.fail())
      {
        cout << "Unable to open " << inputFileName << " for input - Exiting" 
             << endl;
      }
      else
      {
// 8
//        load (inFile, ToDoList);
        list.load (inFile);
        inFile.close();
        goodToGo = true;
      }
    }
    if (goodToGo)
    {
      do
      {
        show_menu();
        readString("\nchoice:  ", choice, CHAR_LENGTH-1, CHAR_LENGTH-1, eof);
        if (eof)
        {
          cout << "EOF entered for menu selection - program terminating" 
               << endl;
          choice[0] = QUIT;
        }
        else
        {
          choice[0] = static_cast <char> (tolower(choice[0]));
        }
        switch (choice[0])
        {
        case DISPLAY:
// 9
//          do_display (ToDoList);
          do_display (list);
          break;
        case ADD:
// 10
//          do_add (ToDoList, eof);
          do_add (list, eof);
          break;
        case REMOVE:
// 11
//          do_remove (ToDoList, eof);
          do_remove (list, eof);
          break;
        case UPDATE:
// 12
//          do_update (ToDoList, eof);
          do_update (list, eof);
          break;
        case QUIT:
// 13
//          do_quit (ToDoList);
          do_quit (list);
          save_done = true;
          break;
        default         : cout << "Invalid menu choice - Try again" << endl;
          break;
        }
        if (eof && !save_done)
        {
// 14
//          do_quit (ToDoList);
          do_quit (list);
          choice[0] = QUIT;
        }
      }
      while (choice[0] != QUIT);
// 15
//      destroy_list(ToDoList);
    }
  }
  return 0;
}

void show_menu()
{
  cout << endl;
  cout << "To Do List Manager:" << endl << endl;
  cout << "d) display list" << endl;
  cout << "a) add item" << endl;
  cout << "r) remove item" << endl;
  cout << "u) update item priority" << endl;
  cout << "q) quit" << endl << endl;
 
  return;
}

// 16
//void do_display (To_Do_Item_Ptr head);
void do_display (const ToDoList &list)
{
// 17
//  display_list (head, cout);
  list.display (cout);
  return;
}

// 18
// void do_add (To_Do_Item_Ptr &head, bool & eof)
void do_add (ToDoList &list, bool & eof)
{
// 19
// To_Do_Item_Ptr temp;
  char description[DESCRIPTION_LENGTH+1];
  int priority;
   
  readString("describe new item (1-60 chars): ", description,
             DESCRIPTION_LENGTH+1, DESCRIPTION_MIN, eof);
  if (eof)
  {
    cout << "\nEOF entered for description - insert cancelled" << endl;
  }
  else
  {
    priority = get_priority(eof);

    if (!eof)
    {
// 20
//      temp = create_node(description, priority);
//      insert_item(head, temp);
      list.addItem(description, priority);
    }
    else
    {
      cout << "\nEOF entered for priority - insert cancelled" << endl;
    }
  }

  return;
}

// 21
// void do_remove (To_Do_Item_Ptr &head, bool &eof)
void do_remove (ToDoList &list, bool & eof)
{
  int position;
// 22
//  To_Do_Item_Ptr temp;
  char prompt[PROMPT_LENGTH];
  bool confirm, found;
// 23
  char description[DESCRIPTION_LENGTH+1];
  int priority;

  position = get_position(eof);
  if (eof)
  {
    cout << "\nEOF entered for item number - remove cancelled" << endl;
  }
  else
  {
// 24
//    search (head, position, temp, found);
    list.lookup(position, description, priority, found);
    if (!found)
    {
      cout << "Item " << position << " is not on your To Do list" << endl
           << endl;
    }
    else
    {
      strncpy (prompt, "Remove \"", PROMPT_LENGTH);
// 25
//      strncat (prompt, temp->description, PROMPT_LENGTH-strlen(prompt));
      strncat (prompt, description, PROMPT_LENGTH-strlen(prompt));
      strncat (prompt, "\" (y/n)? ", PROMPT_LENGTH-strlen(prompt));
      confirm = readBool(prompt, eof);
      if (!eof)
      {
        if (confirm)
        {
// 26
//          remove_item(head, temp);
          list.removeItem(position);
        }
        else
        {
          cout << "Remove operation terminated by user" << endl;
        }
      }
      else
      {
        cout << "\nEOF entered for confirmation - remove cancelled" << endl;
      }
    }
  }
  return;
}

// 27
// void do_update (To_Do_Item_Ptr &head, bool &eof)
void do_update (ToDoList &list, bool & eof)
{
  int position;
// 28
//  To_Do_Item_Ptr temp;
//  To_Do_Item_Ptr temp2;
  char prompt[PROMPT_LENGTH];
  bool confirm, found;
// 29
  char description[DESCRIPTION_LENGTH+1];
  int priority;

  position = get_position(eof);
  if (eof)
  {
    cout << "\nEOF entered for item number - update cancelled" << endl;
  }
  else
  {
// 30
//    search (head, position, temp, found);
    list.lookup(position, description, priority, found);
    if (!found)
    {
      cout << "Item " << position << " is not on your To Do list" << endl
           << endl;
    }
    else
    {
      strncpy (prompt, "Reprioritize \"", PROMPT_LENGTH);
// 31 
//      strncat (prompt, temp->description, PROMPT_LENGTH-strlen(prompt));
      strncat (prompt, description, PROMPT_LENGTH-strlen(prompt));
      strncat (prompt, "\" (y/n)? ", PROMPT_LENGTH-strlen(prompt));
      confirm = readBool(prompt, eof);
      if (!eof)
      {
        if (confirm)
        {
// 32
//          temp2 = new To_Do_Item;
//          strncpy (temp2->description, temp->description, DESCRIPTION_LENGTH);
//          temp2->priority = get_priority(eof);
          priority = get_priority(eof);
          if (!eof)
          {
// 33
//            remove_item(head, temp);
//            insert_item(head, temp2);
            list.removeItem(position);
            list.addItem(description, priority);
          }
          else
          {
            cout << "\nEOF entered for priority - update cancelled" << endl;
          }
        }
      }
      else
      {
        cout << "\nEOF entered for confirmation - update cancelled" << endl;
      }
    }
  }
  return;
}

// 34
// void do_quit (To_Do_Item_Ptr &head)
void do_quit (ToDoList &list)
{
  char OutFileName[FILENAME_LENGTH+1];
  ofstream OutputFile;
  bool eof;

  readString ("Enter name of output file: ", OutFileName, 
              FILENAME_LENGTH+1, 1, eof);
  while (eof)
  {
    readString
      ("Entering EOF for the name of output file is not allowed\nPlease try again: ",
       OutFileName, FILENAME_LENGTH+1, 1, eof);
  }

  OutputFile.open(OutFileName);
  if (OutputFile.fail())
  {
    cout << "Unable to open " << OutFileName << " for output - Exiting" << endl;
  }
  else
  {
// 35
//    write (OutputFile, head);
    list.write(OutputFile);
    OutputFile.close();
  }

  return;
}

int get_priority (bool &eof)
{
  int priority;
  char input, inString[CHAR_LENGTH];
  bool inputOK;

  do {
    readString("enter priority (h/m/l): ", inString, CHAR_LENGTH-1, 
               CHAR_LENGTH-1, eof);
    if (!eof)
    {
      input = inString[0];
      inputOK = ((input == 'h') || (input == 'm') || (input == 'l'));
      if (!inputOK)
      {
        cout << "**** Priority must be one of h(igh), m(edium) or l(ow) ****"
             << endl;
      }
    }
    else
    {
      inputOK = true;
      priority = 0;
    }
  } while (!inputOK);

  if (!eof)
  {
    switch (input)
    {
    case HIGH_CH:    priority = 3;
      break;
    case MEDIUM_CH:  priority = 2;
      break;
    case LOW_CH:     priority = 1;
      break;
    }
  }
  return priority;
}

int get_position (bool &eof)
{
  int position;
  bool positionOK;

  do {
    position = readInt("enter item number: ", eof);
    if (!eof)
    {
      positionOK = (position > 0);
      if (!positionOK)
        cout << "**** Item number must be greater than 0 ****" << endl;
    }
    else
    {
      positionOK = true;
      position = INVALID_POSITION;
    }
  } while (!positionOK);
  return position;
}
