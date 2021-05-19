#include<iostream>
#include<vector>
#include<string>
#include <fstream>
using namespace std;
vector<int> SaftyAlgorithm(vector<vector<int>> need, vector<vector<int>> alloc, vector<int> available, int n, int m) {
	vector<int> work(m);
	vector<bool> finish(n, false);
	bool flag = true;
	vector<int>safe_state;
	for (int i = 0; i < m; i++) { work[i] = available[i]; }
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++) {
			if (finish[i] == false) {
				flag = true;
				for (int j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						flag = false;
					}
				}
				if (flag) {
					for (int j = 0; j < m; j++) {
						work[j] = work[j] + alloc[i][j];
					}
					finish[i] = true;
					safe_state.push_back(i);
				}
				
			}

		}

	for (int i = 0; i < n; i++) {
		if (finish[i] == false) {
			vector<int> v(n + 1);
			return v;
		}
	}
	safe_state.push_back(1);
	return safe_state;
}
vector<int> ResourceRequestAlgorithm(vector<vector<int> > &need, vector<vector<int> > &alloc, vector<int> &available,vector<int>request, int proccess,int n, int m) {
	bool flag = true;
	vector<int>safe_state;
	for (int j = 0; j < m; j++) {
		if ( (need[proccess][j] < request[j]) || (available[j] < request[j]) ) {
			flag = false;
		}

	}
	if (flag) {
		for (int i = 0; i < m;i++) {
			available[i] = available[i] - request[i];
			alloc[proccess][i] = alloc[proccess][i] + request[i];
			need[proccess][i] = need[proccess][i] - request[i];
		}
		safe_state = SaftyAlgorithm(need, alloc, available, n, m);
		if (!safe_state[n]) {
			for (int i = 0; i < m; i++) {
				available[i] = available[i] + request[i];
				alloc[proccess][i] = alloc[proccess][i] - request[i];
				need[proccess][i] = need[proccess][i] + request[i];
			}
			vector<int> v(n + 1);
			return v;
		}
		else { 
			safe_state.push_back(1);
			return safe_state; 

		}
		

	}
	else { 
		vector<int> v(n + 1);
		return v;
	}

}

int main() {
	int n, m;
	//**********************************
	//ifstream in;
	//in.open("t.txt");
	//streambuf* cinbuf = std::cin.rdbuf();
	//cin.rdbuf(in.rdbuf());
	//**********************************
	cout << "Enter n and m respectvely: " << endl;
	cin >> n >> m;
	vector<int> available(m);
	vector<vector<int>> max(n, vector<int>(m));
	vector<vector<int>> alloc(n, vector<int>(m));
	vector<vector<int>> need(n, vector<int>(m));
	cout << "Enter the allocation matrix: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> alloc[i][j];
		}
	}
	cout << endl;

	cout << "Enter the maximum matrix: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> max[i][j];
		}
	}
	cout << endl;
	cout << "Enter the available matrix: " << endl;
	for (int i = 0; i < m; i++) { cin >> available[i]; }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	cout << "**Need matrix** " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << need[i][j] << " ";
		}
		cout << endl;
	}
	cout << "*************** " << endl;

	vector<int> req(m);
	int num=1;
	int proccess=0;
	vector<int>ans;
	string s="";
	cout << "1)system safty enquiry" << endl;
	cout << "2)enquiry request of a proccess" << endl;
	while (true) {

		cout << "Enter 1 or 2"<<endl;
		cin >> num;
		if (num==1) {
			ans = SaftyAlgorithm(need, alloc, available, n, m);
		}
		else {
			cout << "Enter proccess num" << endl;
			cin >> proccess;
			cout << "Enter request" << endl;
			for (int i = 0; i < m;i++) {
				cin >> req[i];
			}
			ans = ResourceRequestAlgorithm(need, alloc, available, req, proccess, n, m);
		}
		cout << "******ANSWER*******" << endl;
		if (ans[n] == 0) {
			cout << "NO" << endl;
		}
		else {
			s = "YES,safe state<";
			for (int i = 0; i < n; i++) {
				if (i == (n - 1)) {
					s += "P" + to_string(ans[i]) + ">";
				}
				else {
					s += "P" + to_string(ans[i]) + ",";
				}
			}
			cout << s << endl;
		}
		cout << "******************" << endl;


	}
}
