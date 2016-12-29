#pragma once

#include <vector>
#include "CubeStatus.cpp"
#include "CubeDebugger.cpp"

using std::vector;

static char colorOfFace[6];

void SolveBottom(Cube &, vector<Op> &);
void SolveMiddle(Cube &, vector<Op> &);
void SolveTop(Cube &, vector<Op> &);

vector<Op> Solve(Cube *_status)
{
	Cube & status = *_status;
	vector<Op> OpStack;

	for(int i=0;i<6;i++) colorOfFace[i]=status[i][4];

	//step1: Fix the bottom part
	SolveBottom(status,OpStack);

	//step2: Fix the middle part
	SolveMiddle(status,OpStack);

	//step3: Fix the top part
	SolveTop(status,OpStack);

	return OpStack;
}

#define ROTATE(OP) (OpStack.push_back(OP),status.push_back(OP))

inline Op inv(Op a){return int(a)>=6 ? a-6 : a+6;}

void SolveBottom(Cube &status, vector<Op> & OpStack)
{
	// step1.1: Edge pieces
	for(int i=1;i<=4;i++){
		PFPos ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
		PFPosColor neighbor=status.EdgeGetNeighbor(ppos);
		if(ppos.face==Face::D){
			ROTATE(neighbor.face);ROTATE(neighbor.face);
		}
		else if(ppos.face!=Face::U){
			if(neighbor.face==Face::D) ROTATE(ppos.face);
			if(neighbor.face==Face::U){
				PFPos dumper;
				for(int j=1;j<8;j+=2) if(status[int(Face::D)][innerFaceOrder[j]] != colorOfFace[int(Face::D)]){
					dumper=PFPos(Face::D,j);break;
				}
				int cnt=0;
				while(status.EdgeGetNeighbor(dumper).face!=ppos.face) ROTATE(Face::D),cnt++;
				ROTATE(inv(ppos.face));
				for(;cnt--;ROTATE(inv(Face::D)));
			}
			ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
			neighbor=status.EdgeGetNeighbor(ppos);
			if(neighbor.pos==3){
				ROTATE(neighbor.face);ROTATE(Face::U);ROTATE(inv(neighbor.face));
			}
			else{
				ROTATE(inv(neighbor.face));ROTATE(Face::U);ROTATE(neighbor.face);
			}
		}
		ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
		while(int(status.EdgeGetNeighbor(ppos).face)!=i) ROTATE(Face::U),ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
		ROTATE(Face(i));ROTATE(Face(i));
	}

	// step1.2: Cornor pieces

}

void SolveMiddle(Cube &status, vector<Op> & OpStack)
{
	//TODO
}

void SolveTop(Cube &status, vector<Op> & OpStack)
{
	//TODO
}
