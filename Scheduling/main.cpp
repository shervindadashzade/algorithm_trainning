#include<iostream>
using namespace std;

struct Job{
    int deadline,profit;
};
// sort by profits decreasing
void sort_jobs_profit(int n,Job* jobs){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(jobs[i].profit < jobs[j].profit){
                Job temp = jobs[j];
                jobs[j] = jobs[i];
                jobs[i] = temp;
            }
        }
    }
}
// sort by deadlines increasing
void sort_jobs_deadline(int n,Job* jobs){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(jobs[i].deadline > jobs[j].deadline){
                Job temp = jobs[j];
                jobs[j] = jobs[i];
                jobs[i] = temp;
            }
        }
    }
}
// sort with jobs
void printJobs(int n,Job* jobs){
    cout<<"Job\tDeadline\tProfit"<<endl;
    for(int i=0;i<n;i++){
        cout<<i+1<<'\t'<<jobs[i].deadline<<'\t'<<jobs[i].profit<<endl;
    }
}


bool is_feasible(int m,int *set,int n,Job* jobs){
    int set_copy[m];
    bool feasible = true;
    for(int i=0;i<m;i++){
        set_copy[i] = set[i];
    }
    //sort set_copy by increasing jobs deadline
    for(int i=0;i<m;i++){
        for(int j=i;j<m;j++){
            if(jobs[set_copy[i]].deadline > jobs[set_copy[j]].deadline){
                int temp = set_copy[i];
                set_copy[i] = set_copy[j];
                set_copy[j] = temp;
            }
        }
    }
    for(int i=0;i<m;i++){
        if(jobs[set_copy[i]].deadline < i+1){
            feasible = false;
            break;
        }
    }
    return feasible;
}
void schedule(int n,Job* jobs,int *set,int &m){
    int i=0;
    sort_jobs_profit(n,jobs);
    while(i<n){
        set[m]=i;
        m++;
        if(!is_feasible(m,set,n,jobs)){
            m--;
        }
        i++;
    }
}

void printResult(int m,int* set,Job* jobs){
    Job res[m];
    for(int i=0;i<m;i++){
        res[i] = jobs[set[i]];
    }
    sort_jobs_deadline(m,res);
    printJobs(m,res);
}

int main(){
    int n=7;
    int m=0;
    int set[n];
    Job jobs[n];
    // add jobs for example
    jobs[0].deadline = 3;
    jobs[0].profit = 40;

    jobs[1].deadline = 1;
    jobs[1].profit = 35;

    jobs[2].deadline = 1;
    jobs[2].profit = 30;

    jobs[3].deadline = 3;
    jobs[3].profit = 25;

    jobs[4].deadline = 1;
    jobs[4].profit = 20;

    jobs[5].deadline = 3;
    jobs[5].profit = 15;

    jobs[6].deadline = 2;
    jobs[6].profit = 10;

    printJobs(n,jobs);
    cout << "Scheduling Algorithem Running...."<<endl;
    schedule(n,jobs,set,m);
    cout<< "Result Set is :";
    for(int i=0;i<m;i++){
        cout<<set[i]+1<<'\t';
    }
    cout<<endl;

    printResult(m,set,jobs);
    return 0;
}