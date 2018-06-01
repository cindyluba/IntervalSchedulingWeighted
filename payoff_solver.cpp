#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct interval {
	int start;
	int finish;
	int payroll;
};

bool compareTime(interval i1, interval i2) {
	return (i1.finish < i2.finish);
}

int bin_search(int i, vector <interval> intervals) {
	int low = 0;
	int high = i -1;
	while(low <= high) {
		int mid = (low + high) / 2;
		if(intervals[mid].finish <= intervals[i].start) {
			if(intervals[mid+1].finish <= intervals[i].start) {
				low = mid + 1;
			} else {
				return mid;
			}
		} else {
			high = mid - 1;
		}
	}
	return -1;
}


int main() {
	int start;
	int finish;
	int payroll;
	vector <interval> intervals;

	while(cin >> start) {
		cin >> finish;
		cin >> payroll;
		interval job = {start, finish, payroll};
		intervals.push_back(job);
	}

	int n = intervals.size();
	sort(intervals.begin(), intervals.end(), compareTime);

	int latestNoConflictJob [n];
	int maxPayoff [n];
	vector<vector<interval>> schedule(intervals.size());

	latestNoConflictJob[0] = -1;
	maxPayoff[0] = intervals[0].payroll;
	schedule[0].push_back(intervals[0]);


	for (int i = 1; i < n; i++) {
		latestNoConflictJob[i] = bin_search(i, intervals);
		int currPayroll = intervals[i].payroll;
		if(latestNoConflictJob[i] != -1)
			currPayroll += maxPayoff[latestNoConflictJob[i]];
		maxPayoff[i] = max(currPayroll, maxPayoff[i-1]);

		if(latestNoConflictJob[i] == -1 && intervals[i].payroll > maxPayoff[i-1]) {
			schedule[i].push_back(intervals[i]);
		} else if(latestNoConflictJob[i] == -1 && intervals[i].payroll < maxPayoff[i-1]) {
			for(interval a: schedule[i-1]){
				schedule[i].push_back(a);
			}
		} else if(latestNoConflictJob[i] != -1 && currPayroll > maxPayoff[i-1]) {
			for(interval a: schedule[latestNoConflictJob[i]]){
				schedule[i].push_back(a);
			}
			schedule[i].push_back(intervals[i]);
		} else {
			for(interval a: schedule[i-1]){
				schedule[i].push_back(a);
			}
		}
		
	}

	cout << "Maximum Payoff: " << maxPayoff[n-1] << endl;

	for(interval a : schedule[n-1]) {
		cout << a.start << " " << a.finish << " " << a.payroll << endl;
	}

} 






