/* TestAccountingLibrary.cc */
/* Test file for accounting library */
/* Include library header */
#include "../libs/AccountingLibrary.h"
#include <random>

int main(int argc, char** argv){
	#ifdef DEBUG
	printf("[%s] [%s] Loaded Tester.\n",__FILE__,__FUNCTION__);
	#endif

	//Class Tests
	printf("Basic Access Test\n\n");
	//Line
	printf("Line:\n");
	std::string test_string = "<test_value>";
	double test_value = 100.00;
	Line line0;
	line0.set_id(test_string);
	line0.set_account(test_string);
	line0.set_type(test_string);
	line0.set_amount(test_value);
	line0.set_debit(test_value);
	line0.set_credit(test_value);
	printf("\tset_id() & id():\t\t");
	(line0.id().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_account() & account():\t");
	(line0.account().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_type() & type():\t");
	(line0.type().compare("CREDIT") == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_amount() & amount():\t");
	(line0.amount() == test_value ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_debit() & debit():\t\t");
	(line0.debit() == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_credit() & credit():\t");
	(line0.credit() == test_value ? printf("Passed\n") : printf("Failed\n"));
	//Entry
	printf("Entry:\n");
	Entry entry0;
	std::time_t test_time = 43;
	entry0.set_id(test_string);
	entry0.set_memo(test_string);
	entry0.set_date(test_time);
	entry0.set_value(test_value);
	entry0.set_error(test_value);
	entry0.set_debit(test_value);
	entry0.set_credit(test_value);
	printf("\tset_id() & id():\t\t");
	(entry0.id().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_memo() & memo():\t\t");
	(entry0.memo().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_date() & date():\t\t");
	(entry0.date() == test_time ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_value() & value():\t\t");
	(entry0.value() == test_value ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_error() & error():\t\t");
	(entry0.error() == test_value ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_debit() & debit():\t\t");
	(entry0.debit() == test_value ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_credit() & credit():\t");
	(entry0.credit() == test_value ? printf("Passed\n") : printf("Failed\n"));

	//Journal
	printf("Journal:\n");
	Journal journal0;
	journal0.set_id(test_string);
	journal0.set_name(test_string);
	journal0.set_entry_count(test_value);
	printf("\tset_id() & id():\t\t");
	(journal0.id().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_name() & name():\t\t");
	(journal0.name().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_e_count() & e_count():\t");
	(journal0.entry_count()  == test_value ? printf("Passed\n") : printf("Failed\n"));

	//Account
	printf("Account:\n");
	Account account0;
	account0.set_id(test_string);
	account0.set_name(test_string);
	account0.set_type(test_string);
	account0.set_balance(test_value);
	printf("\tset_id() & id():\t\t");
	(account0.id().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_name() & name():\t\t");
	(account0.name().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_type() & type():\t\t");
	(account0.type().compare(test_string) == 0 ? printf("Passed\n") : printf("Failed\n"));
	printf("\tset_balance() & balance():\t");
	(account0.balance() == test_value ? printf("Passed\n") : printf("Failed\n"));

	printf("Visual Testing:\n");

	Display display;

	Line line;
	char cstring[10] = {};
	//Display Lines
	std::vector<Line> lineSet;
	for(int i = 0; i < 50; i++){
		if(i %2 == 0){
			line.set_debit(rand()%1000 + 1);
		}else{
			line.set_credit(rand()%1000 + 1);
		}
		for(int j = 0; j < 9; j++){
			cstring[j] = 'A' + rand() % 26;
		}
		cstring[9] = '\0';
		line.set_account(cstring);
		lineSet.push_back(line);
	}

	printf("Pre Sorted List:\n");
	for(Line l : lineSet){
		display.to_screen(l);
	}

	//Adding lines to entry
	printf("Full Entry:\n");
	Entry entry;
	entry.set_date();
	entry.set_lines(lineSet);
	display.to_screen(entry);

	printf("Filters:\n");
	printf("Test One:\n");
	Line filter;
	//filter.set_type("CREDIT");
	//filter.set_amount(99);
	filter.set_account("AYAXZFBJB");
	lineSet = entry.lines(filter);
	for(Line l : lineSet){
		display.to_screen(l);
	}
	printf("Test Two:\n");
	Line filterLow, filterHigh;
	//filterLow.set_amount(15.5);
	//filterHigh.set_amount(500);
	//filterLow.set_type("CREDIT");
	//filterHigh.set_type("CREDIT");
	filterLow.set_account("O");
	filterHigh.set_account("L");
	lineSet = entry.lines(filterLow,filterHigh);
	for(Line l : lineSet){
		display.to_screen(l);
	}

	//Set up potential entries
	std::vector<Entry> entrySet;
		for(int j = 0; j < 50; j++){
			int value1;
			value1 = rand()%1000 + 1;
			lineSet.erase(lineSet.begin(),lineSet.end());
			entry.set_value(0);
			for(int i = 0; i < 2; i++){
				if(i == 0){
					line.set_debit(value1);
				}else{
					line.set_credit(value1);
				}
				for(int k = 0; k < 9; k++){
					cstring[k] = 'A' + rand() % 26;
				}
				cstring[9] = '\0';
				line.set_account(cstring);
				lineSet.push_back(line);
			}
			entry.set_lines(lineSet);

			time_t myTime = time(0);
			//entry.set_date(myTime + rand()%3153600000);
			entry.set_date();
			entrySet.push_back(entry);
		}
	//Set up journal
	printf("Printing Generated Journal:\n");
	Journal journal;
	journal.set_entries(entrySet);
	display.to_screen(journal);


	//Test accounts
	std::vector<Entry> entrySet2;
		for(int j = 0; j < 50; j++){
			int value1;
			value1 = rand()%1000 + 1;
			lineSet.erase(lineSet.begin(),lineSet.end());
			entry.set_value(0);
			for(int i = 0; i < 2; i++){
				if(i == 0){
					line.set_debit(value1);
				}else{
					line.set_credit(value1);
				}
				for(int k = 0; k < 9; k++){
					cstring[k] = 'A';
				}
				cstring[9] = '\0';
				line.set_account(cstring);
				lineSet.push_back(line);
			}
			entry.set_lines(lineSet);
			time_t myTime = time(0);
			entry.set_date(myTime + rand()%3153600000);
			entrySet2.push_back(entry);
		}

	Journal journal2;
	journal2.set_entries(entrySet2);
	display.to_screen(journal2);
	Account account;
	account.set_name(cstring);
	std::vector<Journal> journals;
	journals.push_back(journal2);
	account.set_journals(journals);
	std::cout << "Account Balance: " << account.balance() << std::endl;

}
