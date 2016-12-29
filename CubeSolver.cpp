#pragma once

#include "CubeStatus.cpp"
#include "CubeDebugger.cpp"

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

void SolveTop(Cube &status, vector<Op> & OpStack)
{
	// step1.1: Edge pieces
	for(int i=1;i<=4;i++){
		PFPos ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
	}

	// step1.2: Cornor pieces
}
