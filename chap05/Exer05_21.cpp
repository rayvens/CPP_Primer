#include <iostream>
#include <cctype>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
	string s, sLast;
	bool repeated = false;
	while(cin >> s && !s.empty())
	{
		if(!isupper(s[0]))
			continue;
		if(s == sLast)
		{
			cout << s << endl;
			repeated = true;
			break;
		}
		else
			sLast = s;
	}
	if(!repeated)
		cout << "No word was repeated." << endl;
	return 0;
}