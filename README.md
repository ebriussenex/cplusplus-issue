# Secret
    vector<string> ReadStrings(istream& stream){
        vector <string> strings;
        string s;
        while(stream >> s){
            cout << "s = " << s << "\n";
            strings.push_back(s);
            cout << "s = " << s << ", strings.back =" << strings.back() << "\n";
        }
        return strings;
    }
