#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <string.h>
#include <cstdlib>
#include <random> // For secure random number generation
using namespace std;

// ==========================================
// 1. GLOBAL VARIABLES & VECTORS
// ==========================================
vector<string> adminUsernames = {"Mohammed_Al-Obadi"};
vector<string> adminPasswords = {"123@pMp123@#$"};
vector<string> usernames;
vector<string> passwords;
vector<float> money;
vector<string> history;

// ==========================================
// 2. HELPER FUNCTIONS
// ==========================================

// Function to encrypt and decrypt strings using XOR algorithm
string encryptDecrypt(string input){
  char key = 'S'; // Encryption key
  string output = input;
  for(int i = 0; i <input.size(); i++)
  {
    output[i] = input[i] ^ key;
  }
  return output;
}

// Function to generate an 8-digit random number (Used as OTP for Admin)
int generateRandomNumber()
{
  random_device rd;
  mt19937 gen(rd()); // Advanced random number generator engine
  uniform_int_distribution<int> dist(10000000, 99999999); // 8-digit range
  return dist(gen);
}

// ==========================================
// 3. AUTHENTICATION SYSTEMS
// ==========================================

int currentUser; // To track the currently logged-in user

// Customer login system
bool login()
{ 
  int attempts = 3; // Allow exactly 3 attempts
  bool passed = false;
  
  while(attempts > 0  && passed == false)
  {
    cout <<"Username: ";
    string user;
    cin >> user;
    bool isFound = false;
    
    // Search for the user in the database
    for(int i = 0; i < usernames.size(); i++)
    {
      if(user == usernames[i])
      {
        isFound = true;
        
        // Check if the account is suspended by the Admin
        if(passwords[i] =="SUSPENDED_ACCOUNT")
        {
          system("cls");
          cout <<"\nAccess Denied: Your account has been suspended by the Admin!\n\n";
          return false;
        }
        
        cout <<"\nPassword: ";
        string pass;
        cin >> pass;
        
        // Verify the password
        if(pass == passwords[i])
        {
          system("cls");
          cout << "\nWelcome To Our Bank " << user <<"!\n\n" ;
          currentUser = i; // Save the current user's index
          passed = true;
          return true;
        }
        else // In case of wrong password
        {
          system("cls");
          attempts--;
          if(attempts == 0)
          {
            cout << "Account locked due to multiple failed login attempts!\n\n";
            return false;
          }
          else {cout <<"Access denied. password's wrong! Try again.\nAttempts left: "<<attempts<<"\n\n";}
        }
        break;
      }
    }
    
    // If the username is not found at all
    if(!isFound)
      {
        system("cls");
        attempts--;
        if(attempts == 0)
        {
          cout << "Account locked due to multiple failed login attempts!\n\n";
          return false;
        }
        else {cout <<"\nSorry, this user does not exist or has been deleted! Try again\nAttempts left: "<< attempts<<"\n\n";}
      }
  }
  return false ;
}

// Admin login system (Requires 2FA)
bool adminLogin()
{
  cout <<"Enter the Admin's Username: ";
  string adminUser;
  cin >> adminUser;
  bool isFound = false;
  
  for(int i = 0; i < adminUsernames.size(); i++ )
  {
    if(adminUser == adminUsernames[i])
    {
      isFound = true;
      cout <<"\nEnter Your Password: ";
      string adminPass;
      cin >> adminPass;
      
      if(adminPass == adminPasswords[i])
      {
        // Generate and print a temporary OTP
        int code = generateRandomNumber();
        cout <<"\n\t\t\t\t\t\t\tcode: "<< code <<"\n";
        cout <<"Enter the Code: ";
        long int adminCode;
        cin >> adminCode;
        
        if(adminCode == code)
        {
          // Print admin panel interface upon successful verification
          system("cls");
          return true;
        }
        else{
          cout <<"\nAccess denied. Code is invalid\n";
          return false;
        }
      }
      else{
        cout <<"Access denied. Password is wrong."<<"\n";
        return false;
      }
    }
  }
   if(!isFound)
    {
      cout <<"\nAdmin was Not Found!\n";
      return false;
    }
  return false;
}

// ==========================================
// 4. ADMIN CONTROL PANEL
// ==========================================
void saveAllData(); // FOR USING IT HERE.
void adminSettings()
{
  bool continuing = true;
  while(continuing)
  {
    ifstream adminscreenFile("adminscreen.txt");
    string line;
    while(getline(adminscreenFile, line)){
      cout <<line <<"\n";
    }
    cout <<"\nPlease choose from 0 to 6: ";
    int operation;
    cin >> operation;
    
    // Variables used inside the Admin panel
    string newAdmin;
    string newAdminPass;
    string lookingFor;
    string searchKey;
    int deleteOrSuspend;
    string deleteOrSuspendUser;
    bool foundHistory;
    bool isFound = false;
    float totalMoney = 0;
    bool istaken = false;
    
    switch(operation)
    {
      case 0: // Add a new admin
        system("cls");
        cout <<"Please enter your username: ";
        cin >> newAdmin;
          
          // Check if the admin username already exists
        for(int i =0; i < adminUsernames.size(); i++)
        {
          if(newAdmin == adminUsernames[i])
          {  
            system("cls");
            istaken = true;
            cout <<"This username is already taken. Please choose another one.\n\n";
              break;
          }
        }
          
          if(istaken == false)
          {
            adminUsernames.push_back(newAdmin);
            cout <<"\nPlease enter your password: ";
            cin >> newAdminPass;
            adminPasswords.push_back(newAdminPass);
            system("cls");
            saveAllData();
            cout <<"\nWelcome To Our Bank " << newAdmin <<"!\n";
            cout <<"This admin account was created successfully!\n";
          }
          break;
          
      case 1: // View total bank liquidity (safe)
        system("cls");
        for(int i =0; i < money.size(); i++)
        {
          totalMoney += money[i];
        }
        cout <<"The bank's safe contains: "<< totalMoney <<"$\n";
        break;
        
      case 2: // View all registered customer names
        system("cls");
        for(int i=0; i< usernames.size(); i++)
        {
          cout << usernames[i] <<"\n";
        }
        break;
        
      case 3: // Search for a specific customer and display details/history
        system("cls");
        cout <<"Please Enter the Username of the Customer: ";
        cin >> lookingFor;
        for(int i=0; i < usernames.size(); i++)
        {
          if(lookingFor == usernames[i])
          {
            cout <<usernames[i]<<" | "<< passwords[i] <<" | "<< money[i] <<"\n";
            cout <<"==============================\n";
            cout<<"---Transaction History for " << usernames[i] <<"---\n";
            
              foundHistory = false;
              for(int k = 0; k < history.size(); k++)
              {
                searchKey = usernames[i] +" |";
                if(history[k].find(searchKey) == 0)
                {
                  cout << history[k] << "\n";
                  foundHistory = true;
                }
              }
              if(foundHistory == false)
              {
                cout <<"No previous transactions found.\n";
              }
          }
        }
        break;
        
      case 4: // Comprehensive report for all customers and transactions (Global Audit Log)
        system("cls");
        
        // Print all customer balances first
        for(int i = 0; i < usernames.size(); i++)
        {
          cout <<usernames[i] <<" | " << money[i] <<"$\n";
        }
        cout <<"=================================\n";
        
        // Print each customer's transactions sequentially
        for(int j=0; j < usernames.size(); j++)
        {
          foundHistory = false;
          searchKey = usernames[j] +" |";
          
          for(int i = 0; i < history.size(); i++)
          {
            if(history[i].find(searchKey) == 0)
            {
              cout << history[i] << "\n";
              foundHistory = true;
            }
          }
          
          if(foundHistory == false)
          {
            cout <<"No previous transactions found for " << usernames[j]<<"\n";
          }
          cout <<"===============================\n";
        }
        break;
        
      case 5: // Suspend or permanently delete a customer account
        system("cls");
        cout <<"To Suspend the an account press '1'\nTo delete an account press'2'\n";
        cin >> deleteOrSuspend;
        cout <<"Write the Username for that account: ";
        cin >> deleteOrSuspendUser;
         system("cls");
        switch(deleteOrSuspend)
        {
          case 1: // Suspension process (by changing password)
            isFound = false;
            for(int i=0; i <usernames.size(); i++)
            {
              if(deleteOrSuspendUser == usernames[i])
              {
                isFound = true;
                passwords[i] ="SUSPENDED_ACCOUNT";
                cout <<"\nAccount for "<<usernames[i]<<" was suspended successfully!\n";
                break;
              }
            }
            if(!isFound)
            {
              cout <<"\nUser was not found!\n";
            }
            break;
            
          case 2: // Permanent deletion process
            isFound = false;
            for(int i=0; i <usernames.size(); i++)
            {
              if(deleteOrSuspendUser == usernames[i])
              {
                isFound = true;
                cout <<"\nAccount for "<<usernames[i]<<" was deleted successfully!\n";
                
                // Erase customer data from all vectors
                usernames.erase(usernames.begin() + i);
                passwords.erase(passwords.begin() + i);
                money.erase(money.begin() + i);
                break;
              }
            }
            if(!isFound)
            {
              cout <<"\nUser was not found!\n";
            }
            break;
        }
        break;
      case 6: // Exit admin panel
      default:
        system("cls");
        cout <<"Returning to Main Menu...\n";
        continuing = false;
        cin.ignore();
        cin.get();
        system("cls");
        break;
    }
  }
}

// ==========================================
// 5. CORE BANKING OPERATIONS
// ==========================================

float withdrawnMoney;
// Cash withdrawal function
void withdrawCash()
{
  cout <<"How much money do you want to withdraw?\n";
  cin >> withdrawnMoney;
  system("cls");
  
  if(money[currentUser] >= withdrawnMoney && withdrawnMoney >=0)
  {
    money[currentUser] -= withdrawnMoney;
    cout <<"You just withdraw " << withdrawnMoney << "$ from your Account successfully!\n\n";
    // Document the transaction in history as plain text
    history.push_back(usernames[currentUser]+ " | withdrew: " + to_string(withdrawnMoney) +"$");
  }
  else if(withdrawnMoney < 0)
  {
    cout <<"value has to be positive!\n\n";
  }
  else{cout <<"You only have " << money[currentUser] << "$.\n\n";}
}

float depositedMoney;
// Cash deposit function
void depositCash()
{
  cout <<"How much money to want to deposite?\n";
  cin >> depositedMoney;
  system("cls");
  
  if(depositedMoney > 0)
  {
    money[currentUser] += depositedMoney;
    cout << depositedMoney << "$ was added to your acount successfully!\n\n";
    // Document the transaction in history
    history.push_back(usernames[currentUser]+ " | Deposit: " + to_string(depositedMoney) +"$");
  }
  else{cout <<"value has to be positive!\n\n";}
}

// Function to change username or password
void changePasswordOrUsername()
{
  cout <<"Previous Username: ";
  string user;
  cin >> user;
  bool isFound = false;
  
  for(int i = 0; i < usernames.size(); i++)
  {
    if(user == usernames[i])
    {
      isFound = true;
      cout <<"\nPrevious Password: ";
      string pass;
      cin >> pass;
      
      if(pass == passwords[i])
      {
        system("cls");
        cout <<"\nWelcome " << user <<"\n";
        cout <<"For changing your username choose'1'\nFor changing your password choose'2'\n";
        int request;
        cin >> request;
        system("cls");
        string editedUsername;
        string editedPassword;
        
        switch(request)
        {
          case 1:
            cout <<"Enter you new uesrname: ";
            cin >> editedUsername;
            usernames[i] = editedUsername;
            cout <<"\nYour username was changed successfully!\n\n";
            break;
          case 2:
            cout <<"Enter you new password: ";
            cin >> editedPassword;
            passwords[i] = editedPassword;
            cout <<"\nYour password was changed successfully!\n\n";
            break;
          default: cout <<"\nError! Wrong operation.\n\n";
        }
      }
      else
      {
        system("cls");
        cout <<"Access denied. password was wrong!\n\n";
      }
      break;
    }
  }
   if(!isFound)
    {
      system("cls");
      cout <<"\nSorry, this user does not exist!\n\n";
    }
}

// Fund transfer function between accounts
void transaction()
{
  cout <<"Please enter the username of the account you want to send money to: ";
  string sendToUser;
  cin >> sendToUser;
  bool isFound = false;
  
  for(int i =0; i < usernames.size(); i++)
  {
    if(sendToUser == usernames[i])
    {
      system("cls");
      isFound = true;
      cout <<"\nPlease enter how much money you want to transform to "<< sendToUser<<": ";
      float transformedMoney;
      cin >> transformedMoney;
      
      if(money[currentUser] >= transformedMoney && transformedMoney > 0)
      {
        system("cls");
        // Deduct amount from sender and add to receiver
        money[currentUser] -= transformedMoney;
        money[i] += transformedMoney;
        cout <<"\nTransaction was done successfully!\n\n";
        
        // Record transaction in both accounts
        history.push_back(usernames[currentUser] + " | Transformed: " + to_string(transformedMoney) +"$ to "+ sendToUser);
        history.push_back(sendToUser + " | Received: " + to_string(transformedMoney) +"$ from "+ usernames[currentUser]);
      }
      else {cout <<"\nYou only have " <<money[currentUser]<<"$\n\n";}
      break;
    }
  }
  
  if(!isFound)
  {
    cout <<"\nThe user you want to send the moeny to does not exist.\n";
  }
}

// ==========================================
// 6. DATA PERSISTENCE
// ==========================================

// Function to save and encrypt all data to external files
void saveAllData()
{
  // Save customer data
  ofstream usersFile("ATMData.txt");
  for(int i = 0; i < usernames.size(); i++)
  {
    usersFile <<  encryptDecrypt(usernames[i]) <<"\n" <<  encryptDecrypt(passwords[i]) <<"\n" << money[i] <<"\n";
  }
  usersFile.close();

  // Save transaction history
  ofstream historyFile("dataHistory.txt");
  for(int i = 0; i < history.size(); i++)
  {
    historyFile << encryptDecrypt(history[i]) <<"\n";
  }
  historyFile.close();

  // Save admin data
  ofstream adminFile("Admins.txt");
  for(int i=0; i < adminUsernames.size(); i++)
  {
    adminFile <<encryptDecrypt(adminUsernames[i]) <<"\n" <<encryptDecrypt(adminPasswords[i]) <<"\n";
  }
  adminFile.close();
}

// Function to load and decrypt data on program startup
void loadAllData()
{
  // Load customer data
  ifstream userFile("ATMData.txt");
    if(userFile.is_open())
    {
      usernames.clear();
      passwords.clear();
      money.clear();
      string userN, passW;
      float moneyC;
      while(userFile >> userN >> passW >> moneyC){
        usernames.push_back( encryptDecrypt(userN));
        passwords.push_back( encryptDecrypt(passW));
        money.push_back(moneyC);
      }
      userFile.close();
    }
    else{cout <<"Eroor: could not open ATMData.txt\n";}

  // Load transaction history
  ifstream historyFile("dataHistory.txt");
    if(historyFile.is_open())
    {
      history.clear();
      string line;
      while(getline(historyFile, line))
      {
        history.push_back(encryptDecrypt(line));
      }
      historyFile.close();
    }
    else{cout <<"Eroor: could not open dataHistory.txt\n";}

  // Load admin data
  ifstream adminFile("Admins.txt");
  if(adminFile.is_open())
  {
    adminUsernames.clear();
    adminPasswords.clear();
    string adUser, adPass;
    while(getline(adminFile, adUser)&& getline(adminFile, adPass)){
      adminUsernames.push_back(encryptDecrypt(adUser));
      adminPasswords.push_back(encryptDecrypt(adPass));
    }
    adminFile.close();
  }
  
  // Default protection: Create a default admin if the admin file is empty
  if(adminUsernames.empty()){
    adminUsernames.push_back("Mohammed_Al-Obadi");
    adminPasswords.push_back("123@pMp123@#$");
  }
}

// ==========================================
// 7. MAIN PROGRAM EXECUTION
// ==========================================

int main()
{
  loadAllData(); // Load data immediately upon system startup
  bool startAgain = true;
  
  // Main loop to keep the program running
  while(startAgain == true)
  {
    int operation;
  
    // Print the main user interface from the text file
    ifstream atmFile("ATM.txt");
    string line;
    while(getline(atmFile, line)){
      cout << line << "\n";
    }
    
     cout <<"Please choose from 0 to 7: ";
     cin >> operation;
     system("cls");
     
     string newUser;
     string newUserPassword;
     float newMoney = 0;
     bool istaken = false;
     
    switch(operation)
    {
      case 0: // Admin login
        if(adminLogin())
        {
          adminSettings();
        }
        saveAllData(); // Save any changes made by the admin
        break;
        
      case 1: // Create a new bank account
        cout <<"Please enter your username: ";
        cin >> newUser;
        
        // Check for duplicate usernames
        for(int i =0; i < usernames.size(); i++)
        {
          if(newUser == usernames[i])
          {  
            system("cls");
            istaken = true;
            cout <<"This username is already taken. Please choose another one.\n\n";
            break;
          }
        }
        
        if(istaken == false)
        {
          usernames.push_back(newUser);
          cout <<"\nPlease enter your password: ";
          cin >> newUserPassword;
          passwords.push_back(newUserPassword);
          money.push_back(newMoney);
          system("cls");
          cout <<"\nWelcome To Our Bank " << newUser <<"!\n";
          cout <<"Your account was created successfully!\n";
          saveAllData(); // Save the new account immediately
        }
        break;
        
      case 2: // Withdraw funds
        if(login())
        {
          withdrawCash();
        }
        saveAllData();
        break;
        
      case 3: // Deposit funds
        if(login())
        {
          depositCash();
        }
        saveAllData();
        break;
        
      case 4: // Update account details
        changePasswordOrUsername();
        saveAllData();
        break;
        
      case 5: // Check balance and view personal history
        if(login())
        {
          system("cls");
          cout <<"You have " << money[currentUser] << "$ in your account.\n\n";
          cout <<"Do you want to see your procedures history? If yes, enter '1'\n\n";
          int displayhistory;
          cin >> displayhistory;
          
          if(displayhistory == 1)
          {
            system("cls");
            cout<<"---Transaction History for " << usernames[currentUser] <<"---\n";
            bool foundHistory = false;
            
            // Search and print current user's transactions only
            for(int i = 0; i < history.size(); i++)
            {
              string searchKey = usernames[currentUser] +" |";
              if(history[i].find(searchKey) == 0)
              {
                cout << history[i] << "\n";
                foundHistory = true;
              }
            }
            if(foundHistory == false)
            {
              cout <<"No previous transactions found.\n";
            }
            cout <<"==================================\n\n";
          }
          else{ cout <<"Ok! moving on\n\n";}
        }
        saveAllData();
        break;
        
      case 6: // Fund transfer service
        if(login())
        {
          transaction();
        }
        saveAllData();
        system("cls");
        break;
        
      case 7: // Exit system
        system("cls");
        cout <<"Thanks for using our digital bank!\n\n";
        startAgain = false;
        break;
        
      default:
        cout <<"Incorrect operation. Please choose again.\n\n";
        break;
    }
  }
  
  // Pause screen before final exit to ensure messages are read
  cout <<"Click any key to exit...\n";
  cin.ignore();
  cin.get();
  saveAllData(); // Final save to ensure data integrity
  return 0;
}
