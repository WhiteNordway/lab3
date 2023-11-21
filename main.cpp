// Variant 1

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;


bool cmp(string s1, string s2)
{
    string name1, name2;
    for (char &c: s1)
    {
        if (c)
            name1 += c;
        else
            break;
    }
    for (char &c: s2)
    {
        if (c)
            name2 += c;
        else
            break;
    }
    return name1 <= name2;
}


void fill_with_data(string file_name)
{   
    string temp;
    std::ofstream ouf(file_name);
    while (getline(std::cin, temp))
        ouf << temp << std::endl;
    ouf.close();
}


void sort_file(string file_name)
{
    std::ifstream inf(file_name);
    string temp_string;
    vector<string> temp_vector;
    while (std::getline(inf, temp_string))
        temp_vector.push_back(temp_string);
    inf.close();
    std::sort(temp_vector.begin(), temp_vector.end(), cmp);

    std::ofstream ouf("output.txt");
    for (string s: temp_vector)
        ouf << s << std::endl;
    ouf.close();
}


void search(string file_name, string s)
{
    std::ifstream inf(file_name);
    string temp;
    while (std::getline(inf, temp))
    {
        string name;
        auto cur = temp.begin();
        while (!*cur)
            name += *cur++;
        if (s != name)
            continue;

        string result;
        for (auto end = temp.end(); cur != end; ++cur)
            result += *cur;
        std::ofstream ouf("output.txt");
        ouf << result << std::endl;
        ouf.close();

        break;
    }
    
    inf.close();
}


void get_data(string file_name, char choice, unsigned state)
{
    std::ifstream inf(file_name);
    std::ofstream ouf("output.txt");
    string temp;
    while (std::getline(inf, temp))
    {
        string name;
        auto cur = temp.begin();
        while (!*cur)
            name += *cur++;

        string price_str;
        while (!*cur)
            price_str += *cur++;
        int price = std::stoi(price_str);

        string quantity_str;
        for (auto end = temp.end(); cur != end; ++cur)
            quantity_str += *cur;
        int quantity = std::stoi(quantity_str);
        
        if (choice == '1' && price <= state || choice == '2' && quantity <= state)
            ouf << name << ' ' << price << ' ' << quantity << std::endl;
    }

    inf.close();
    ouf.close();
}


int main()
{
    const string FILE_NAME = "products.txt";
    std::cout << "Input option from list:" <<
    "\n'1' - Creating and filling file with input data" <<
    "\n'2' - Searching and sorting in file" <<
    "\n'3' - Adding data to the file" <<
    "\n'4' - Output specified data" <<
    "\n'5' - Exit" <<
    std::endl;
    char choice0;

    while (true)
    {   
        std::cout << "Enter the number:" << std::endl;
        std::cin >> choice0;
        switch (choice0)
        {
            // Creating and filling file with input data 
            case '1':
                {
                    std::cout << "Enter the data about products" << std::endl;
                    fill_with_data(FILE_NAME);
                }
                break;

            // Searching and sorting in file
            case '2':
                {
                    sort_file(FILE_NAME);
                    std::cout << "Enter the name of product you want to get info of" << std::endl;
                    string s;
                    std::getline(std::cin, s);
                    search(FILE_NAME, s);
                }
                break;

            // Adding data to the file
            case '3':
                {
                    std::ofstream ouf;
                    ouf.open(FILE_NAME, std::ios::app);
                    std::cout << "Enter new product" << std::endl;

                    string temp;
                    std::cin >> temp;
                    ouf << temp << std::endl;
                }
                break;

            // Output specified data
            case '4':
                {
                    std::cout << "If you want to get data by price -- enter '1'" <<
                    '\n' << "If you want to get data by quantity -- enter '2'" <<
                    std::endl;

                    char choice;
                    while (true)
                    {
                        std::cin >> choice;
                        if (choice == '1' || choice == '2')
                        {
                            unsigned state;
                            std::cin >> state;
                            get_data(FILE_NAME, choice, state);
                            break;
                        }
                    }
                }
                break;
            case '5':
                std::cout << "Goodbye." << std::endl;
                return EXIT_SUCCESS;
        }
    }
}
