# Secret
## The example of how does "move" works.
First of all you need to add "utility" library by `#include <utility>`
```c++
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
```
Using instead `move(s)`
```c++
vector<string> ReadStringsMove(istream& stream){
	vector <string> strings;
	string s;
	while(stream >> s){
		cout << "s = " << s << "\n";
		strings.push_back(move(s));
		cout << "s = " << s << ", strings.back =" << strings.back() << "\n";
	}
	return strings;
}
```
Using text generation function to profile the programm
```c++
string GenerateText(){
	const int SIZE = 1000000000;
	const int WORD_LENGTH = 100000;
	string text(SIZE, 'a');
	for(int i = WORD_LENGTH; i < SIZE; i += WORD_LENGTH){
		text[i] = ' ';
	}
	return text;
}
```
