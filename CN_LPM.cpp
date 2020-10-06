#include<bits/stdc++.h>
using namespace std;
vector< string > split(string str, char c);
struct information
{
    string destination_subnet;
    string subnet_mask;
    string outgoing_interface;

    int a_A, a_B, a_C, a_D;
    int b_A, b_B, b_C, b_D;
    int network_part;

    void set_network_part(string s)
    {
        vector< string > strings = split(s,'.');
        network_part=0;

        for(string str : strings)
        {
            bitset< 8 > bits(stoi(str));
            network_part+=bits.count();
        }
        return;
    }
    void get_range(string d)
    {
        vector< string > strings = split(d,'.');
        a_A = stoi(strings[0]);
        a_B = stoi(strings[1]);
        a_C = stoi(strings[2]);
        a_D = stoi(strings[3]);
        string temp = "";
        for(string str : strings)
        {
            bitset< 8 > bits(stoi(str));
            temp+=bits.to_string();
            temp+=".";
        }
        temp.pop_back();

        for(int i = (network_part+(network_part/8));i<temp.size();i++)
        {
            if(temp[i]!='.') temp[i]='1';
        }
        strings = split(temp,'.');
        b_A = stoi(strings[0],0,2);
        b_B = stoi(strings[1],0,2);
        b_C = stoi(strings[2],0,2);
        b_D = stoi(strings[3],0,2);
        return;
    }

    information(string d, string s, string o)
    {
        destination_subnet = d;
        subnet_mask = s;
        outgoing_interface = o;
        set_network_part(s);
        get_range(d);
    }

    void show_ranges()
    {
        printf("%d.%d.%d.%d - %d.%d.%d.%d\n",a_A,a_B,a_C,a_D,b_A,b_B,b_C,b_D);
        return;
    }
    void show_info()
    {
        cout << destination_subnet << " " << subnet_mask << " " << outgoing_interface << endl;
    }
};

vector< string > split(string str, char x)
{
    vector< string > strings;
    string temp = "";
    for(char c : str)
    {
        if(c==x)
        {
            if(temp.size())
                strings.push_back(temp);
            temp="";
        }
        else
            temp+=c;
    }
    if(temp.size())
        strings.push_back(temp);
    return strings;
}

string default_path="no path available!!";
vector< information > forwarding_table;

void LPM(string str)
{
    vector< string > strings = split(str,'.');
    string path = "";
    int max_network_part = 0;

    for(information x : forwarding_table)
    {
        if(x.a_A<=stoi(strings[0]) && x.b_A>=stoi(strings[0]) && x.a_B<=stoi(strings[1]) && x.b_B>=stoi(strings[1]) && x.a_C<=stoi(strings[2]) && x.b_C>=stoi(strings[2]) && x.a_D<=stoi(strings[3]) && x.b_D>=stoi(strings[3]))
        {
            if(x.network_part>max_network_part)
            {
                max_network_part = x.network_part;
                path = x.outgoing_interface;
            }
        }
    }

    path.size() == 0 ? cout << default_path << endl : cout << path << endl;
    return;
}
int main()
{
    #ifdef TarekHasan
        freopen("input.txt","r",stdin);
    #endif // TarekHasan

    int tt; cin >> tt;
    while(tt--)
    {
        string a,b,c; cin >> a;
        if(a=="default")
        {
            cin >> default_path;
            continue;
        }
        cin >> b >> c;
        forwarding_table.push_back(information(a,b,c));
    }

    /*for(information x : forwarding_table)
        x.show_info();
    if(default_path!="no path available!!")
        cout << "\tdefault            " << default_path << endl;*/

    string query;

    while(cin >> query)
    {
        LPM(query);
    }
    return 0;
}

/*
input:
5
128.96.170.0 255.255.254.0 interface_0
128.96.168.0 255.255.254.0 interface_1
128.96.166.0 255.255.254.0 R2
128.96.164.0 255.255.252.0 R3
default R4
128.96.171.92
128.96.167.151
128.96.169.192
128.96.165.121
*/
