#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include "CubeStatus.cpp"

using std::vector;
using std::deque;
using std::pair;

typedef pair<int,int> PII;

void Optimize(vector<Op> &OpStack){
    deque<pair<Op,PII>> st;
    for(auto p : OpStack){
        if(st.empty() || st.back().first!=Oface(p) && st.back().first!=Counter(Oface(p))){
        	int cnt=(p==Oface(p) ? 1 : -1);
        	if(int(Oface(p))<3) st.push_back(make_pair(Oface(p),PII(cnt,0)));
        	else st.push_back(make_pair(Counter(Oface(p)),PII(0,cnt)));
        }
        else{
            if(st.back().first==p) ++st.back().second.first;
            else if(st.back().first==inv(p)) --st.back().second.first;
            else if(st.back().first==Counter(p)) ++st.back().second.second;
			else --st.back().second.second;
			if(st.back().second.first==3) st.back().second.first=-1;
			if(st.back().second.second==3) st.back().second.second=-1;
			if(st.back().second.first==-3) st.back().second.first=1;
			if(st.back().second.second==-3) st.back().second.second=-1;
			if(!st.back().second.first && !st.back().second.second) st.pop_back();
        }
    }
    OpStack.clear();
    for(;!st.empty();){
        pair<Op,PII> t=st.front();st.pop_front();
        Op a=t.first;
        if(t.second.first<0) t.second.first*=-1,a=inv(a);
        for(;t.second.first--;OpStack.push_back(a));
        a=Counter(t.first);
        if(t.second.second<0) t.second.second*=-1,a=inv(a);
        for(;t.second.second--;OpStack.push_back(a));
    }
}
