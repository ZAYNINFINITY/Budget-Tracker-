#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Date {
public:
    int d, m, y;
    Date(int dd = 1, int mm = 1, int yy = 2000) : d(dd), m(mm), y(yy) {}
    void getDate() {
        cout << "date" << endl;
        cin >> d >> m >> y;
    }
    void showDate() const {
        cout << d << "/" << m << "/" << y << endl;
    }
};

class Transaction {
protected:
    float amt;
    string cat, plc;
    Date dt;
public:
    virtual void get() {
        cout << "amt" << endl;
        cin >> amt;
        cout << "cat" << endl;
        cin >> cat;
        cout << "place" << endl;
        cin >> plc;
        dt.getDate();
    }
    virtual void show() const {
        cout << amt << " " << cat << " " << plc << " ";
        dt.showDate();
    }
    float getAmt() const { return amt; }
};

class Income : public Transaction {
public:
    void get() override {
        cout << "income" << endl;
        Transaction::get();
    }
};

class Expense : public Transaction {
public:
    void get() override {
        cout << "expense" << endl;
        Transaction::get();
    }
};

class User {
private:
    string uname, pass;
    float bal;
    Income in[50];
    Expense ex[50];
    int inCnt, exCnt;
public:
    User() : bal(0.0), inCnt(0), exCnt(0) {}
    void signup() {
        cout << "uname" << endl;
        cin >> uname;
        cout << "pass" << endl;
        cin >> pass;
        save();
        cout << "created" << endl;
    }
    bool login() {
        string u, p;
        cout << "uname" << endl;
        cin >> u;
        cout << "pass" << endl;
        cin >> p;
        return (u == uname && p == pass);
    }
    void save() {
        ofstream f(uname + ".txt");
        f << pass << endl << bal << endl;
        f.close();
    }
    void load(string u) {
        uname = u;
        ifstream f(uname + ".txt");
        if (f) {
            getline(f, pass);
            f >> bal;
        }
        f.close();
    }
    void addIn() {
        if (inCnt < 50) {
            in[inCnt].get();
            bal += in[inCnt].getAmt();
            inCnt++;
        }
    }
    void addEx() {
        if (exCnt < 50) {
            ex[exCnt].get();
            bal -= ex[exCnt].getAmt();
            exCnt++;
        }
    }
    void viewBal() const {
        cout << "bal: " << bal << endl;
    }
    void viewAll() const {
        cout << "incomes" << endl;
        for (int i = 0; i < inCnt; i++) in[i].show();
        cout << "expenses" << endl;
        for (int i = 0; i < exCnt; i++) ex[i].show();
    }
};

int main() {
    User u;
    int ch;
    string user;

    cout << "1 signup" << endl << "2 login" << endl;
    cin >> ch;
    if (ch == 1) {
        u.signup();
    } else {
        cout << "uname" << endl;
        cin >> user;
        u.load(user);
        if (!u.login()) {
            cout << "wrong" << endl;
            return 0;
        }
    }

    do {
        cout << "1 in" << endl << "2 ex" << endl << "3 bal" << endl << "4 all" << endl << "5 exit" << endl;
        cin >> ch;
        switch (ch) {
            case 1: u.addIn(); break;
            case 2: u.addEx(); break;
            case 3: u.viewBal(); break;
            case 4: u.viewAll(); break;
            case 5: u.save(); cout << "bye" << endl; break;
            default: cout << "wrong" << endl;
        }
    } while (ch != 5);

    return 0;
}
