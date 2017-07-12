/* AccountingLibrary.h */

/* Import Protection */
#ifndef ACCOUNTING_LIBRARY_H
#define ACCOUNTING_LIBRARY_H

/* External Library Imports */
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

/*************************************/
/* Main Libary Classes and Functions */
/*************************************/


/* File Class */
/* Handles reading and writing to files
 * in the needed formats */


/* Line Class */
/* Individule line items that make up entry */

class Line {
private:
        std::string _id;            //Unique ID
        std::string _account;       //Account ref.
        std::string _type;          //Debit or Credit
        double _amount;             //Value
        double _debit;
        double _credit;
        std::time_t _date;              //Date -- used for account
public:
        Line();
        ~Line();
        virtual void set_id(std::string id);
        virtual void set_account(std::string account);
        virtual void set_type(std::string type);
        virtual void set_amount(double amount);
        virtual void set_debit(double debit);
        virtual void set_credit(double credit);
        virtual void set_date(std::time_t date);
        virtual void sync(void);
        virtual std::time_t date(void);
        virtual std::string id(void);
        virtual std::string account(void);
        virtual std::string type(void);
        virtual double amount(void);
        virtual double debit(void);
        virtual double credit(void);
        bool operator<(const Line &l2) const;
        bool operator<=(const Line &l2) const;
        bool operator>(const Line &l2)const;
        bool operator>=(const Line &l2)const;
        bool operator==(const Line &l2)const;
};



/* Entry Class */
/* Contains Lines (at least two)*/
class Entry {
private:
        std::string _id;                //Unique ID
        std::string _memo;              //Memo
        std::time_t _date;              //Date
        double _value;                  //Value transfered
        double _error;                  //Error between debits and credits (shouldn't exist)
        double _credit;
        double _debit;
        std::vector<Line> _lines;       //Line vector
public:
        Entry();
        ~Entry();
        virtual void set_id(std::string id);
        virtual void set_memo(std::string memo);
        virtual void set_date(void);
        virtual void set_date(std::time_t date);
        virtual void set_value(double value);
        virtual void set_error(double error);
        virtual void set_debit(double debit);
        virtual void set_credit(double credit);
        virtual void set_lines(std::vector<Line> lines);    //Set entire line vector
        virtual void add_line(Line line);                   //Add a line
        virtual void remove_line(Line line);                //Remove the first matching line
        virtual void modify_line(Line line_a, Line line_b); //Replace line_a with line_b
        virtual void sync(void);
        virtual std::string id(void);
        virtual std::string memo(void);
        virtual std::time_t date(void);
        virtual double value(void);
        virtual double error(void);
        virtual double debit(void);
        virtual double credit(void);
        virtual Line line(Line line);                               //Get first line matching line
        virtual std::vector<Line> lines(void);                      //Get entire line vector
        virtual std::vector<Line> lines(Line line);                 //Get all lines matching line
        virtual std::vector<Line> lines(Line line_a, Line line_b);  //Get lines between line_a and line_b
        bool operator<(const Entry &e2) const;
        bool operator<=(const Entry &e2) const;
        bool operator>(const Entry &e2)const;
        bool operator>=(const Entry &e2)const;
        bool operator==(const Entry &e2)const;
};

/* Journal Class */
/* Contains entries */
class Journal {
private:
        std::string _id;                //Unique ID
        std::string _name;              //Name
        double _entry_count;            //Count of entries
        std::vector<Entry> _entries;    //Entires
public:
        Journal();
        ~Journal();
        virtual void set_id(std::string id);
        virtual void set_name(std::string name);
        virtual void set_entry_count(double entry_count);
        virtual void set_entries(std::vector<Entry> entries);    //Set entire entry vector
        virtual void add_entry(Entry entry);                     //Add an entry to the entry vector
        virtual void remove_entry(Entry entry);                  //Remove a matching entry
        virtual void modify_entry(Entry entry_a, Entry entry_b); //Replace the first entry matching entry_a with entry_b
        virtual void sync(void);
        virtual double entry_count(void);                        //Count of entires
        virtual std::string id(void);
        virtual std::string name(void);
        virtual Entry entry(Entry entry);                        //Get first entry matching entry
        virtual std::vector<Entry> entries(void);
        virtual std::vector<Entry> entries(Entry entry);         //Get all entries matching entry
        virtual std::vector<Entry> entries(Entry entry_a, Entry entry_b);   //Get entries between entry_a and entry_b
};

/* Account Class */
/* Contains data on account
 * currently only used for handling names for journal */
class Account {
private:
        std::string _id;                       //Unique Account ID
        std::string _name;                     //Account Name
        std::string _type;                     //Account Type (Asset, Liablity, Equity, Expence, etc
        double _balance;                       //Current Account balance
        std::vector<Journal> _journals;        //Journals to search for
        double _journal_count;               //Count of journals
        std::vector<Entry> _entries;           //Entries refering to account
        double _entry_count;                   //Count of entries
        std::vector<Line> _lines;              //FInal lines of account with dates added
        double _line_count;
        std::vector<Account>  _accounts;       //Child or sub accounts
public:
        Account();
        ~Account();
        virtual void set_id(std::string id);
        virtual void set_name(std::string name);
        virtual void set_type(std::string type);
        virtual void set_balance(double balance);
        virtual void set_lines(std::vector<Line> lines);
        virtual void set_entries(std::vector<Entry> entries);
        virtual void set_journals(std::vector<Journal> journals);
        virtual void add_sub_account(Account account);
        virtual void remove_sub_account(Account account);
        virtual void modify_sub_account(Account account_a, Account account_b);
        virtual void sync(void);
        virtual std::string id(void);
        virtual std::string name(void);
        virtual std::string type(void);
        virtual double balance(void);
        virtual std::vector<Line> lines(void);
        virtual std::vector<Entry> entries(void);
        virtual std::vector<Journal> journals(void);
        virtual std::vector<Account> accounts(void);
        virtual std::vector<Account> accounts(Account account);
        virtual std::vector<Account> accounts(Account account_a, Account account_b);

        bool operator<(const Account &a2) const;
        bool operator<=(const Account &a2) const;
        bool operator>(const Account &a2)const;
        bool operator>=(const Account &a2)const;
        bool operator==(const Account &a2)const;
};

/* Display Class */
/* Displays all other classes based on need */

class Display {
private:
        int width, columnOne, columnTwo, columnThree, columnFour;
        std::string format;
public:
        Display();
        ~Display();
        virtual std::string to_string(Line line);
        virtual std::string to_string(Entry entry);
        virtual std::string to_string(Journal journal);
        virtual std::string to_string(Account account);
        virtual void to_screen(Line line);
        virtual void to_screen(Entry entry);
        virtual void to_screen(Journal journal);
        virtual void to_screen(Account account);
        virtual void to_screen_internal(Entry entry);
};





#endif
