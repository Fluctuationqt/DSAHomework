#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>
using namespace std;

int main () {
    int n;
    cin >> n;
    unordered_map<string,int> names(n);
    unordered_set<string> prefixes(n);

    string name;
    bool renamed;
    for (int i = 0; i < n; i++) {
	        renamed = false;
	        cin >> name;
    
	        for (int k = 0; k < name.length(); k++) {
	            string subs = name.substr(0, k + 1);
	            bool prefix_exist = prefixes.find(subs) != prefixes.end();
	            if (renamed == false && prefix_exist == false) {
		              cout << subs << endl;
		              names.insert(pair<string,int>(name,1));
		              renamed = true;
	            }
	    
	            if (prefix_exist == false)
		              prefixes.insert(subs);
	        }

          if (renamed == false) {
                auto name_count = names.find(name);
                if (name_count == names.end()) {
                      names.insert(pair<string,int>(name, 1));
                      cout << name << endl;
                }
                else {
                      int count = name_count->second + 1;
                      cout << name + " " << to_string(count) << endl;
                      names[name] = count;
                }
            }
    }
}