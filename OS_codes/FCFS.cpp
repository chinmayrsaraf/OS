#include<bits/stdc++.h> using namespace std; 
 
 
void FCFS(vector<int> &v, int head){ 
    int size = v.size(); 
 
    int overhead_movement = 0; 
    for(auto i : v){ 
        overhead_movement += abs(head - i); 
        head = i; 
    } 
 
    cout << "Total overhead movement: " << overhead_movement << endl; 
 
} 
 
 
void SSTF(vector<int> &v, int head){     vector<pair<int, int >> temp; 
    for(auto i : v){         temp.push_back({i, 0}); 
    } 
 
    int size = v.size(); 
    int overhead_movement = 0; 
    int count = 0; 
int min = INT_MAX; 
    int break_count = 0;     vector<int> ans;     while(true){         int min = INT_MAX; 
        for(int i=0;i<size;i++){             if(temp[i].second == 0){                 if(abs(head - temp[i].first) < min){                     min = abs(head - temp[i].first);                     count = i; 
                } 
            } 
        } 
        int flag = 0;         for(int i=0;i<size;i++){             if(temp[i].second == 0){ 
                flag = 1;                 break; 
 
            } 
        } 
 
        if(flag == 0){             break; 
        } 
        ans.push_back(temp[count].first);         temp[count].second = 1;         if(break_count == size){ 
            break; 
        } 
        overhead_movement += min; 
        head = temp[count].first; 
 
 
    } 
 
 
    cout << "Sequence of execution requests: "; 
    for (auto i : ans){         cout << i << " "; 
    } 
    cout << endl; 
 
    cout << "Total overhead movement: " << overhead_movement << endl; 
 
} 
 
 
void SCAN(vector<int> &v, int head, int end){     vector<int> temp;     int _temp = head; 
    for(auto i : v){         if(i > _temp){             temp.push_back(i); 
        } 
    } 
    temp.push_back(end); 
 
    sort(temp.begin(), temp.end()); 
 
    vector<int> temp2;  
 
for(auto i : v){         if(i < head){             temp2.push_back(i); 
            head = i; 
        } 
    } 
    sort(temp2.begin(), temp2.end(), greater<int>()); 
 
    int overhead_movement = 0; 
 
    for(auto i : temp){         cout << i << " "; 
    } 
    cout << endl; 
 
    for(auto i : temp){         overhead_movement += abs(head - i); 
        head = i; 
    } 
 
 
    head = end; 
 
    for(auto i : temp2){ 
        cout << i << " "; 
    } 
    cout << endl; 
 
    for(auto i : temp2){         
        overhead_movement += abs(head - i); 
        head = i; 
    } 
 
 
    cout << "Total overhead movement: " << overhead_movement << endl; 
 
} 
 
 
 
void CSCAN(vector <int> v, int head, int end){     vector<int> temp1;     vector<int> temp2; 
 
 
    for(int i : v){         if(i > head){             temp1.push_back(i); 
        }         else{ 
            temp2.push_back(i); 
        } 
    } 
 
    temp1.push_back(end);     sort(temp1.begin(), temp1.end()); 
 
    int overhead_movement = 0; 
 
    for(auto i : temp1){         overhead_movement += abs(head - i); 
        head = i; 
} 
 
    head = 0;     sort(temp2.begin(), temp2.end());     overhead_movement += end; 
 
    for(auto i : temp2){         overhead_movement += abs(head - i); 
        head = i; 
    } 
 
    cout << "Total overhead movement: " << overhead_movement << endl; 
} 
 
 
void LOOK(vector<int> v, int head){     vector<int> temp1;     vector<int> temp2; 
 
    for(int i : v){         if(i > head){             temp1.push_back(i); 
        }         else{ 
            temp2.push_back(i); 
        } 
    } 
 
    sort(temp1.begin(), temp1.end());     sort(temp2.begin(), temp2.end(), greater<int>()); int overhead_movement = 0; 
    for(auto i : temp1){         overhead_movement += abs(head - i); 
        head = i; 
    } 
    head = temp1[temp1.size() - 1];     for(auto i : temp2){         overhead_movement += abs(head - i); 
        head = i; 
    } 
    cout << "Total overhead movement: " << overhead_movement << endl; 
} 
 
void CLOOK(vector<int> v, int head){     vector<int> temp1;     vector<int> temp2; 
 
    for(int i : v){         if(i > head){ 
            temp1.push_back(i); 
        }         else{ 
            temp2.push_back(i); 
        } 
    } 
    sort(temp1.begin(), temp1.end());     sort(temp2.begin(), temp2.end()); 
 
    int overhead_movement = 0; 
 
    for(auto i : temp1){ 
        overhead_movement += abs(head - i); 
        head = i; 
    } 
    overhead_movement += abs(head - temp2[0]);     head = temp2[0]; 
 
    for(int i=1;i<temp2.size();i++){         overhead_movement += abs(head - temp2[i]); 
        head = temp2[i]; 
    } 
 
    cout << "Total overhead movement: " << overhead_movement << endl; 
 
 
} 
 
 
int main(){     int head;     cout << "Enter the initial head position::";     cin >> head; 
 
    int n; 
    cout << "Enter the number of requests::"; 
    cin >> n; 
 
 
    vector<int> v;     cout << "Enter the requests::" << endl; 
    for(int i=0;i<n;i++){         int data; 
        cin >> data; 
        v.push_back(data); 
 
    } 
    FCFS(v, head); 
    SSTF(v, head); 
    SCAN(v, head, 199); 
    CSCAN(v, head, 199); 
    LOOK(v, head); 
    CLOOK(v, head); 
 
}
