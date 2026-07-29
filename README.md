
```markdown
# 🏦 C++ Digital Bank & ATM Simulator

Hello! 👋 Welcome to my C++ ATM and Banking System project. 

I built this console-based application to apply and solidify my knowledge of C++ fundamentals, specifically focusing on **File I/O operations**, **Data Encryption**, and **System Architecture**. It mimics a real-world digital bank with separate, secure environments for standard customers and system administrators.

## ✨ Key Features

### 👤 Customer Features
* **Account Management:** Users can create a new account, securely log in, and update their credentials.
* **Core Banking:** Deposit cash, withdraw funds, and check current balances safely.
* **Money Transfers:** Transfer funds instantly to other registered users in the system.
* **Personalized History:** Each user can view their own private transaction history.

### 🛡️ Administrator Features (Secured)
* **Two-Factor Authentication (2FA):** Admins must enter their password AND a randomly generated 8-digit OTP (One Time Password) to access the control panel.
* **Global Audit Log:** Admins can view a comprehensive, chronological history of *every* transaction made in the bank by *all* users.
* **Account Control:** Admins have the authority to temporarily suspend user accounts or permanently delete them from the database.
* **Bank Liquidity:** Instantly view the total amount of money currently held inside the entire bank.

### 🔒 Security & Data Persistence
* **XOR Encryption:** Sensitive data (usernames, passwords, and transaction logs) are never saved in plain text. They are encrypted using an XOR algorithm before being written to the database.
* **File-Based Database:** The system uses lightweight `.txt` files (`ATMData.txt`, `Admins.txt`, `dataHistory.txt`) to store and persist data across different sessions.

## 🚀 How to Run the Project

1. Make sure you have a C++ compiler installed on your machine (like `g++` via MinGW, or GCC).
2. Download or clone this repository.
3. **Important:** Ensure all the `.txt` files (even if they are empty) are located in the exact same folder as the `.cpp` source file.
4. Open your terminal and compile the code:
   ```bash
   g++ "ATM English.cpp" -o ATM

```
 5. Run the generated executable:
   * On Windows: ATM.exe
   * On Mac/Linux: ./ATM
### 🔑 Default Admin Access
If you are running this program for the first time and the Admins.txt database is empty, the system is designed to automatically generate a default admin account so you don't get locked out. You can use these credentials to log in:
 * **Username:** Mohammed_Al-Obadi
 * **Password:** 123@pMp123@#$
*Thank you for checking out my project! Feel free to test the encryption, try the admin controls, and explore the code.*
```

```
