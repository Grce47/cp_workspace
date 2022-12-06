#include <bits/stdc++.h>
using namespace std;

const int no_of_files = 10;

int main()
{
    time_t my_time = time(NULL);
    vector<string> msg;
    string line;
    ifstream input_file("cp_layout.cpp");

    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            msg.push_back(line);
        }
        input_file.close();
    }
    else
        cout << "Unable to open file" << endl;
    string out = "../CP/A.cpp";
    string rem = "../CP/A";
    string rem2 = "../CP/A.exe";
    int idx = 6;
    out[idx] = (out[idx] - 1);
    rem[idx] = out[idx];
    rem2[idx] = out[idx];
    for (int i = 0; i < no_of_files; i++)
    {
        out[idx] = (out[idx] + 1);
        rem[idx] = out[idx];
        remove(rem.c_str());
        rem2[idx] = out[idx];
        remove(rem2.c_str());
        ofstream output_file(out.c_str());

        // output_file << "    CodeForce : Gr47\n    CodeChef : gr47ace\n    HackerRank : gracesharma47\n*/\n";
        for (string ele : msg)
        {
            output_file << ele << endl;
        }
        output_file << "\n/*\n    " << ctime(&my_time);
        output_file << "    File : " << out.substr(idx) << "\n*/\n";
        output_file.close();
    }
    return 0;
}