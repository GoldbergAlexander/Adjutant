#include "AccountingLibrary.h"
//#define DEBUG


/* Main Library Classes */
/* Defined in header    */


/* Line */

Line::Line(){
        #ifdef DEBUG
        printf("[%s] [%s] [Normal Constructor]\n", __FILE__, __FUNCTION__);
        #endif
        _id = "<unset>";
        _account = "<unset>";
        _type = "<unset>";
        _amount = 0.00;
        _debit = 0;
        _credit = 0;
}


Line::~Line(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
}


void Line::set_id(std::string id){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id= id;
        sync();
}

void Line::set_account(std::string account){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _account = account;
}

void Line::set_type(std::string type){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _type = type;
}

void Line::set_amount(double amount){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _amount = amount;
}

void Line::set_credit(double credit){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _debit = 0.00;
        _credit = credit;
        sync();
}

void Line::set_debit(double debit){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _credit = 0.00;
        _debit = debit;
        sync();
}

void Line::set_date(std::time_t date){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _date = date;
        sync();
}

void Line::sync(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        if(debit() > credit()) {
                set_amount(debit());
                set_type("DEBIT");
        }else if (credit() > debit()){
                set_amount(credit());
                set_type("CREDIT");
        }else {
                set_type("<unset>");
        }
}

std::time_t Line::date(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::time_t str = _date;
        return str;

}


std::string Line::id(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _id;
        return str;
}

std::string Line::account(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _account;
        return str;
}

std::string Line::type(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _type;
        return str;
}

double Line::amount(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _amount;
}

double Line::debit(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _debit;
}

double Line::credit(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _credit;
}

bool Line::operator<(const Line &l2)const{
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        /* internal data
        *       for reference
        *       std::string _id;            //Unique ID
                std::string _account;       //Account ref.
                std::string _type;          //Debit or Credit
                double _amount;             //Value
                double _debit;
                double _credit;
        */
       /* Order of comparison */
       /* TYPE: Debits > credits
        * Amount: Greater > Smaller
        * Account: Alphabetical
        * ID: final comparison for identical lines
        */

       //Be Advised: A defined value in amount can and will cause the sort to end before reaching the account section.
       //If the desire is to filter a range by both a value and an account, the list should be filtered multiple times.

        Line line;
        int comp;
        if(line._date != l2._date){
                if(this->_date != l2._date){
                        return this->_date > l2._date;
                }
        }
        //TYPE
        if(l2._type.compare(line._type) != 0){
                comp = this->_type.compare(l2._type);
                if(comp != 0){
                        return comp > 0;
                }
        }
        //amount
        if(line._amount != l2._amount){
                if(this->_amount != l2._amount){
                        return this->_amount > l2._amount;
                }
        }

        //Account
        if(line._account.compare(l2._account) != 0){
                if(this->_account != l2._account){
                        return this->_account < l2._account;
                }
        }
        //ID
        if(line._id.compare(l2._id) != 0){
                comp = this->_id.compare(l2._id);
                if(comp != 0){
                        return comp < 0;
                }
        }
        return false;
}
bool Line::operator<=(const Line &l2) const{
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return (*this < l2 || *this == l2);
}
bool Line::operator>(const Line &l2) const{
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return !((*this<l2) || (*this==l2));
}
bool Line::operator>=(const Line &l2) const{
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return (*this == l2 )||( *this > l2);

}
bool Line::operator==(const Line &l2) const{
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif

        /* internal data
        *       for reference
        *       std::string _id;            //Unique ID
                std::string _account;       //Account ref.
                std::string _type;          //Debit or Credit
                double _amount;             //Value
                double _debit;
                double _credit;
        */
       /* Order of comparison */
       /* TYPE: Debits > credits
        * Amount: Greater > Smaller
        * Account: Alphabetical
        * ID: final comparison for identical lines
        */

       //get defaults (don't compare on filter defaults)
       Line line;
       int comp;
       //Date
       if(line._date != l2._date){
               if(this->_date != l2._date){
                       return this->_date < l2._date;
               }
       }
       //TYPE
       if(l2._type.compare(line._type) != 0){
               comp = this->_type.compare(l2._type);
               if(comp != 0){            // C before D so reverse Alphabetical
                       return false;
               }
       }

       //amount
       if(line._amount != l2._amount){
               if(this->_amount != l2._amount){
                       return false;
               }
       }

       //Account
       if(line._account.compare(l2._account) != 0){
               comp = this->_account.compare(l2._account);
               if(comp != 0){
                       return false;
               }
       }

       //ID
       if(line._id.compare(l2._id) != 0){
               comp = this->_id.compare(l2._id);
               if(comp != 0){
                       return false;
               }           // We will return true in all other cases since this is the last comparison
       }

       return true;
}


/* Entry */

Entry::Entry(){
        _id = "<unset>";
        _memo = "<unset>";
        _date = NULL;
        _value = 0.00;
        _error = 0.00;
        _debit = 0.00;
        _credit = 0.00;
}

Entry::~Entry(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
}

void Entry::set_id(std::string id){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id = id;
}

void Entry::set_memo(std::string memo){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _memo = memo;
        sync();
}

void Entry::set_date(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _date = time(0);
        sync();
}

void Entry::set_date(std::time_t date){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _date = date;
        sync();
}

void Entry::set_value(double value){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _debit = 0.00;
        _credit = 0.00;
        _value = value;
}

void Entry::set_error(double error){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _error = error;
}

void Entry::set_credit(double credit){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _credit = credit;
}

void Entry::set_debit(double debit){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _debit = debit;
}

void Entry::set_lines(std::vector<Line> lines){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _lines = lines;
        sync();
}

void Entry::add_line(Line line){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _lines.push_back(line);
        sync();
}

void Entry::remove_line(Line line){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        //TODO Convert to std::algs
        for(int i = 0; i < _lines.size();i++){
                if(_lines[i] == line){
                        _lines.erase(_lines.begin() + i);
                }
        }
        sync();
}

void Entry::modify_line(Line line_a, Line line_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        //TODO Convert to std::algs
        for(int i = 0; i < _lines.size();i++){
                if(_lines[i] == line_a){
                        _lines[i] = line_b;
                }
        }
        sync();
}

void Entry::sync(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        for(Line l: lines()) {
                set_credit(this->credit() + l.credit());
                set_debit(this->debit() + l.debit());
        }
        if(debit() > credit()) {
                set_value(debit());
                set_error(debit() - credit());
        }else if (credit() > debit()) {
                set_value(credit());
                set_error(credit() - debit());
        }else{
                set_value(credit());
                set_error(0.00);
        }
        std::sort(this->_lines.begin(),this->_lines.end());
}

std::string Entry::id(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _id;
        return str;
}

std::string Entry::memo(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _memo;
        return str;
}

std::time_t Entry::date(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::time_t str = _date;
        return str;

}

double Entry::value(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _value;
}

double Entry::error(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _error;
}

double Entry::debit(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _debit;
}

double Entry::credit(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _credit;
}

Line Entry::line(Line line){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        Line return_line;
        //TODO Convert to std::algs
        for(int i = 0; i < _lines.size();i++){
                if(_lines[i] == line){
                        return_line = _lines[i];
                        return return_line;
                }
        }
        return return_line; //NULL
}
std::vector<Line> Entry::lines(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Line> return_lines = _lines;
        return return_lines;
}

std::vector<Line> Entry::lines(Line line){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Line> return_lines;
        //TODO Convert to std::algs
        for(int i = 0; i < _lines.size();i++){
                if(_lines[i] == line){
                        return_lines.push_back(_lines[i]);
                }
        }
        return return_lines;
}

std::vector<Line> Entry::lines(Line line_a, Line line_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Line> return_lines;
        //TODO Convert to std::algs
        for(int i = 0; i < _lines.size();i++){
                if((_lines[i] <= line_a) && (_lines[i] >= line_b)){
                                return_lines.push_back(_lines[i]);
                        }
        }
        return return_lines;
}

bool Entry::operator<(const Entry &e2) const{
        /*
        _id = "<unset>";
        _memo = "<unset>";
        _date = NULL;
        _value = 0;
        _error = 0;
        _debit = 0;
        _credit = 0;
         */

        /* order of Sort
        Date
        Value
        Memo
        ID
        */
       //Get defaults
       Entry entry;
       if(entry._date != e2._date){
               if(this->_date != e2._date){
                       return this->_date < e2._date;
               }
       }
       if(entry._value != e2._value){
               if(this->_value != e2._value){
                       return this->_value < e2._value;
               }
       }
       if(entry._memo != e2._memo){
               if(this->_memo != e2._memo){
                       return this->_memo < e2._memo;
               }
       }
       if(entry._id != e2._id){
               if(this->_id != e2._id){
                       return this->_id < e2._id;
               }
       }
       return true;
}
bool Entry::operator<=(const Entry &e2) const{
        return (*this < e2 || *this == e2);

}
bool Entry::operator>(const Entry &e2)const{
        return !(*this < e2 || *this == e2);
}
bool Entry::operator>=(const Entry &e2)const{
        return !(*this < e2);
}
bool Entry::operator==(const Entry &e2)const{
        Entry defaults;
        if(e2._date != defaults._date){
        if(this->_date != e2._date){
                return false;
        }
        }
        if(e2._value != defaults._value){
        if(this->_value != e2._value){
                return false;
        }
        }
        if(e2._memo != defaults._memo){
        if(this->_memo.compare(e2._memo) != 0){
                return false;
        }
        }
        if(e2._id != defaults._id){
        if(this->_id.compare(e2._id) != 0){
                return false;
        }
        }

        return true;
}

/*Journal */

Journal::Journal(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id = "<unset>";
        _name = "<unset>";
        _entry_count = 0;
}

Journal::~Journal(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
}

void Journal::set_id(std::string id){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id= id;
        sync();
}

void Journal::set_name(std::string name){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif

        _name = name;
        sync();
}

void Journal::set_entry_count(double entry_count){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif

        _entry_count = entry_count;
}

void Journal::set_entries(std::vector<Entry> entries){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _entries = entries;
        sync();
}

void Journal::add_entry(Entry entry){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _entries.push_back(entry);
        sync();
}

void Journal::remove_entry(Entry entry){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        for(int i = 0; i < _entries.size(); i++){
                if(_entries[i] == entry){
                        _entries.erase(_entries.begin() + i);
                }
        }
        sync();
}

void Journal::modify_entry(Entry entry_a, Entry entry_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        for(int i = 0; i < _entries.size(); i++){
                if(_entries[i] == entry_a){
                        _entries[i] = entry_b;
                }
        }
        sync();
}

void Journal::sync(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        set_entry_count(entries().size());
        std::sort(this->_entries.begin(),this->_entries.end());
}

double Journal::entry_count(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _entry_count;
}

std::string Journal::id(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _id;
        return str;
}

std::string Journal::name(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _name;
        return str;
}

Entry Journal::entry(Entry entry){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        Entry return_entry;
        for(int i = 0; i < _entries.size(); i++){
                if(_entries[i] == entry){
                        return_entry = _entries[i];
                        return return_entry;
                }
        }
        return return_entry; //NULL
}

std::vector<Entry> Journal::entries(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Entry> return_entries = _entries;
        return return_entries;
}

std::vector<Entry> Journal::entries(Entry entry){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Entry> return_entries;
        for(int i = 0; i < _entries.size(); i++){
                if(_entries[i] == entry){
                        return_entries.push_back(_entries[i]);
                }
        }
        return return_entries;
}

std::vector<Entry> Journal::entries(Entry entry_a, Entry entry_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Entry> return_entries;
        for(int i = 0; i < _entries.size(); i++){
                if(_entries[i] >= entry_a || _entries[i] <= entry_a){
                        return_entries.push_back(_entries[i]);
                }
        }
        return return_entries;
}
/* Account */

Account::Account(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id = "<unset>";
        _name = "<unset>";
        _type = "<unset>";
        _balance = 0;
}

Account::~Account(){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
}

void Account::set_id(std::string id){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _id = id;
}

void Account::set_name(std::string name){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _name = name;
}

void Account::set_type(std::string type){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _type = type;
}

void Account::set_balance(double balance){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _balance = balance;
}
void Account::set_lines(std::vector<Line> lines){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _lines = lines;
}
void Account::set_entries(std::vector<Entry> entries){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _entries = entries;
}
void Account::set_journals(std::vector<Journal> journals){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _journals = journals;
        std::vector<Entry> entries;
        std::vector<Line> lines;
        for(Journal j: _journals){
                for(Entry e : j.entries()){
                        for(Line l : e.lines()){
                                if(l.account() == this->_name){
                                        entries.push_back(e);
                                        l.set_date(e.date());
                                        lines.push_back(l);
                                }
                        }
                }
        }
        set_entries(entries);
        set_lines(lines);
}

void Account::add_sub_account(Account account){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        _accounts.push_back(account);
}

void Account::remove_sub_account(Account account){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        for(int i = 0; i < _accounts.size(); i++){
                if(_accounts[i] == account){
                        _accounts.erase(_accounts.begin() + i);
                }
        }
}

void Account::modify_sub_account(Account account_a, Account account_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        for(int i = 0; i < _accounts.size(); i++){
                if(_accounts[i] == account_a){
                        _accounts[i] = account_b;
                }
        }
}

void Account::sync(void){
        //Journals -> Entries ref to Account -> lines set to entry date

}

std::string Account::id(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _id;
        return str;
}

std::string Account::name(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _name;
        return str;
}

std::string Account::type(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::string str = _type;
        return str;
}

double Account::balance(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        return _balance;
}
std::vector<Line> Account::lines(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Line> return_lines = _lines;
        return return_lines;
}

std::vector<Entry> Account::entries(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Entry> return_entries = _entries;
        return return_entries;
}
std::vector<Journal> Account::journals(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Journal> return_journals = _journals;
        return return_journals;
}

std::vector<Account> Account::accounts(void){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Account> return_accounts = _accounts;
        return return_accounts;
}

std::vector<Account> Account::accounts(Account account){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Account> return_accounts;
        for(Account a : _accounts){
                if(a == account){
                        return_accounts.push_back(a);
                }
        }
        return return_accounts;
}

std::vector<Account> Account::accounts(Account account_a, Account account_b){
        #ifdef DEBUG
        printf("[%s] [%s]\n", __FILE__, __FUNCTION__);
        #endif
        std::vector<Account> return_accounts;
        for(Account a : _accounts){
                if(a >= account_a && a <= account_b){
                        return_accounts.push_back(a);
                }
        }
        return return_accounts;
}

bool Account::operator<(const Account &a2) const{
        /* Vars
        std::string _id;                       //Unique Account ID
        std::string _name;                     //Account Name
        std::string _type;                     //Account Type (Asset, Liablity, Equity, Expence, etc
        double _balance;                       //Current Account balance
        std::vector<Entry> _entries;           //Entries refering to account
        std::vector<Account>  _accounts;       //Child or sub accounts
        */
       Account defaults;
       if(a2._type.compare(defaults._type) != 0){
               if(this->_type < a2._type){
                       return true;
               }
       }
       if(a2._name.compare(defaults._name) != 0){
               if(this->_name < a2._name){
                       return true;
               }
       }
       if(a2._id.compare(defaults._id) != 0){
               if(this->_id < a2._id){
                       return true;
               }
       }
       return false;

}
bool Account::operator<=(const Account &a2) const{
        return this < &a2 || this == &a2;
}
bool Account::operator>(const Account &a2)const{
        return !(this < &a2) && !(this == &a2);
}
bool Account::operator>=(const Account &a2)const{
        return !(this < &a2) || (this == &a2);
}
bool Account::operator==(const Account &a2)const{
        /* Vars
        std::string _id;                       //Unique Account ID
        std::string _name;                     //Account Name
        std::string _type;                     //Account Type (Asset, Liablity, Equity, Expence, etc
        double _balance;                       //Current Account balance
        std::vector<Entry> _entries;           //Entries refering to account
        std::vector<Account>  _accounts;       //Child or sub accounts
        */
       Account defaults;
       if(a2._type.compare(defaults._type) != 0){
               if(this->_type != a2._type){
                       return false;
               }
       }
       if(a2._name.compare(defaults._name) != 0){
               if(this->_name != a2._name){
                       return false;
               }
       }
       if(a2._id.compare(defaults._id) != 0){
               if(this->_id != a2._id){
                       return false;
               }
       }
       return true;
}

/* Display */
Display::Display(){
        width = 100;
        columnOne = width/6;
        columnTwo = width/2 -3;
        columnThree = width/6;
        columnFour = width/6;

}
Display::~Display(){

}

std::string Display::to_string(Line line){
        return NULL;
}
std::string Display::to_string(Entry entry){
        return NULL;
}
std::string Display::to_string(Journal journal){
        return NULL;
}
std::string Display::to_string(Account account){
        return NULL;
}
void Display::to_screen(Line line){
        std::cout << '+' << std::setfill('-') << std::setw(width-2) << '+'<<std::endl;
        std::cout << std::setfill(' ')
        <<std::right << '|' << std::setw(columnOne);
        if(line.type().compare("DEBIT") == 0){
                std::cout
                << '|' << std::left << std::setw(columnTwo) << line.account();
        }else{
                std::cout
                << '|' << std::left << "     " << std::setw(columnTwo-5) <<line.account();
        }
        std::cout
        << '|' << std::setw(columnThree) << std::right << std::fixed << std::setprecision(2) << line.debit()
        << '|' << std::setw(columnFour) << line.credit() << '|' << std::endl;
        std::cout << '+' << std::setfill('-') << std::setw(width-2) << '+'<<std::endl;
}

void Display::to_screen(Entry entry){
        to_screen_internal(entry);
        std::cout << '+' << std::setfill('-') << std::right << std::setw(width-2) << '+'<< std::endl;
}
void Display::to_screen_internal(Entry entry){

        //Print Date on first line
        bool date = false;
        time_t myTime = entry.date() + 10000;
        tm *formatTime = localtime(&myTime);
        std::string str1 = std::to_string(1+formatTime->tm_mon);
        std::string str2 = std::to_string(formatTime->tm_mday);
        std::string str3 = std::to_string(1900+formatTime->tm_year);
        std::string stringDate = str1 + '/' + str2 + '/' + str3;
        //Print Lines
        for(Line line: entry.lines()){
                std::cout << '+' << std::setfill('-') << std::setw(width-2) << '+'<<std::endl;
                if(line.type().compare("DEBIT") == 0){
                        std::cout << std::setfill(' ');
                        if(!date){
                                std::cout << '|' <<std::left << std::setw(columnOne-1) << stringDate;
                                date = true;
                        }else {
                                std::cout << '|' << std::setw(columnOne);
                        }
                        std::cout
                        << '|' << std::left << std::setw(columnTwo) << line.account();
                }else{
                        std::cout << std::setfill(' ');
                        if(!date){
                                std::cout << '|' <<std::left << std::setw(columnOne-1) << stringDate;
                                date = true;
                        }else {
                                std::cout << '|' << std::setw(columnOne);
                        }
                        std::cout
                        << '|' << std::left << "     " << std::setw(columnTwo-5) <<line.account();
                }
                std::cout
                << '|' << std::setw(columnThree) << std::right << std::fixed << std::setprecision(2) << line.debit()
                << '|' << std::setw(columnFour) << line.credit()
                << '|' << std::endl;
                //
        }
        //Print Memo at end
        Entry defEntry;
        if(defEntry.memo() != entry.memo()){
                std::cout << '+' << std::setfill('-') << std::setw(width-2) << '+'<<std::endl;
                std::cout << '|' <<std::setfill(' ') <<std::left << std::setw(width-3) << entry.memo() << '|' << std::endl;
        }
}

void Display::to_screen(Journal journal){
        std::cout << '+' << std::setfill('-') << std::setw(width-2) << '+'<< std::endl;
        std::cout << '|'  << std::setfill(' ') << std::setw(width-3) << journal.name() << '|' << std::endl;
        for(Entry entry:journal.entries()){
                to_screen_internal(entry);
        }
        std::cout << '+' << std::setfill('-') << std::right << std::setw(width-2) << '+' << std::endl;
}
void Display::to_screen(Account account){

}
