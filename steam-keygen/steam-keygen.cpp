#include <iostream>
#include <string>
#include <chrono>

using namespace std;

void askForType()
{
    cout << "Выберите формат ключа:\n";
    cout << "[1] AAAAA-BBBBB-CCCCC\n"
         << "[2] AAAAA-BBBBB-CCCCC-DDDDD-EEEEEE\n"
         << "[3] 237ABCDGHJLPRST 23\n";
}

void askForCount()
{
    cout << "Сколько ключей нужно сгенерировать? ";
}

string randStr(const int len, static const char alphanum[])
{
    srand(rand() % (sizeof(alphanum) - rand() % rand()));

    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

string genSimple(int max)
{
    int i = 0;
    string result = "";

    while (i < max)
    {
        result += randStr(5, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        if (i < max - 1) result += "-";
        i++;
    }

    return result;
}

string genThird()
{
    srand(time(NULL) * rand() - rand() % rand());

    string result;

    result = to_string(rand() % (999 - 111 + 1) + 111)
            + randStr(12, "ABCDFGHJKLMNPQRSTVWXYZ")
            + " "
            + to_string(rand() % (99 - 11 + 1) + 11);

    return result;
}

inline bool isInteger(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    string input;

    askForType();
    getline(cin, input);

    while (input != "1" && input != "2" && input != "3") {
        cout << "Ошибка.\n\n";

        askForType();
        getline(cin, input);
    }

    string _count;
    int count;

    askForCount();
    getline(cin, _count);

    while (!isInteger(_count)) {
        cout << "Ошибка.\n\n";

        askForCount();
        getline(cin, _count);
    }

    count = stoi(_count);

    if (input == "1" || input == "2") {
        int i = 0;
        int max = 3;
        if (input == "2") max = 4;

        while (i < count) {
            cout << genSimple(max) << endl;
            i++;
        }
    }

    else if (input == "3") {
        int i = 0;
        while (i < count) {
            cout << genThird() << endl;
            i++;
        }
    }

    cout << endl;
    main();
}
