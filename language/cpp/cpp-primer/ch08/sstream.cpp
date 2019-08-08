#include <iostream>
using std::cin; using std::cout; using std::cerr;
using std::istream; using std::ostream; using std::endl;

#include <sstream>
using std::ostringstream; using std::istringstream;

#include <vector>
using std::vector;

#include <string>
using std::string;

// members are public by default
struct PersonInfo {
    string name;
    vector<string> phones;
};

string format(const string &s) { return s; }

bool valid(const string &)
{
    return true;
}

vector<PersonInfo>
getData(istream &is)
{
    // will hold a line and word from input, respectively
    string line, word;

    // will hold all the records from the input
    vector<PersonInfo> people;

    // read the input a line at a time until end-of-file (or other error)
    while (getline(is, line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    return people;
}

ostream& process(ostream &os, vector<PersonInfo> people)
{
    // for each entry in people
    for (vector<PersonInfo>::const_iterator entry = people.begin();
            entry != people.end(); ++entry) {
        ostringstream formatted, badNums; // objects created on each loop

        // for each number
        for (vector<string>::const_iterator nums = entry->phones.begin();
                nums != entry->phones.end(); ++nums) {
            if (!valid(*nums)) {
                badNums << " " << *nums; // string in badNums
            } else {
                // `writes` to formatted's string
                formatted << " " << format(*nums);
            }
        }

        if (badNums.str().empty())          // there were no bad numbers
            os << entry->name << " "        // print the name
               << formatted.str() << endl;  // and formatted numbers
        else                                // otherwise, print the name and bad numbers
            cerr << "input error: " << entry->name
                 << " invalid number(s) " << badNums.str() << endl;
    }

    return os;
}

int main()
{
    process(cout, getData(cin));

    return 0;
}
