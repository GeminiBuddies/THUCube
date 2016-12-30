#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include "CubeStatus.cpp"

using std::vector;
using std::deque;

void Optimize(vector<Op> &OpStack){
    deque<pair<Op,int>> st;
    for(auto p : OpStack){
        if(st.empty() || st.back().first!=p && st.back().first!=inv(p))
            st.push_back(make_pair(p,1));
        else{
            if(st.back().first==inv(p)){
                if(!--st.back().second) st.pop_back();
            }
            else{
                if(++st.back().second == 3) st.pop_back(),st.push_back(make_pair(inv(p),1));
            }
        }
    }
    OpStack.clear();
    for(;!st.empty();){
        pair<Op,int> t=st.front();st.pop_front();
        for(;t.second--;OpStack.push_back(t.first));
    }
}
