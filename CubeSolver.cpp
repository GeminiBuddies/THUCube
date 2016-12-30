#pragma once

#include <vector>
#include <utility>
#include "CubeStatus.cpp"
#include "CubeDebugger.cpp"

using std::vector;
using std::pair;

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

#ifndef DEBUG
#define ROTATE(OP) (OpStack.push_back(OP),status.Rotate(OP))
#else
#define ROTATE(OP) (OpStack.push_back(OP),status.Rotate(OP),printCube(status),puts(""))
#endif

inline Op inv(Op a){return Op(int(a)>=6 ? int(a)-6 : int(a)+6);}
inline bool Any(PFPos &a, PFPos b, PFPos c, Face target){
	return a.face==target ? true
							: b.face==target ? a=b,true
											: c.face==target ? a=c,true
															: false;
}
inline bool Any(PFPos &a, PFPos b, Face target){
	return a.face==target ? true
							: b.face==target ? a=b,true
											: false;
}

inline int UDoppo(int pos){
	if(pos==2) return 8;
	if(pos==8) return 2;
	if(pos==0) return 6;
	if(pos==6) return 0;
}
inline int Left(int c){return c%4+1;}
inline int Right(int c){return (c+2)%4+1;}

void SolveBottom(Cube &status, vector<Op> & OpStack)
{
	// step1.1: Edge pieces
	for(int i=1;i<=4;i++){
		PFPos ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i]);
		PFPosColor neighbor=status.EdgeGetNeighbor(ppos);
		if(ppos.face==Face::D){
			if(neighbor.face==Face(i)) continue;
			ROTATE(neighbor.face);ROTATE(neighbor.face);
		}
		else if(ppos.face!=Face::U){
			if(neighbor.face==Face::D) ROTATE(ppos.face);
			if(neighbor.face==Face::U){
				PFPos dumper;
				for(int j=1;j<8;j+=2) if(status[int(Face::D)][innerFaceOrder[j]] != colorOfFace[int(Face::D)]){
					dumper=PFPos(Face::D,innerFaceOrder[j]);break;
				}
				int cnt=0;
				char domColor=status[int(Face::D)][dumper.pos];
				char auxColor=status.EdgeGetNeighbor(dumper).color;
				while(status.EdgeGetNeighbor(dumper).face!=ppos.face) ROTATE(Face::D),dumper=status.SeekPiece(domColor,auxColor),cnt++;
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

	for(int i=1;i<=4;i++){
		int nFace=Left(i),targetPos;
		if(i==1) targetPos=8;
		if(i==2) targetPos=2;
		if(i==3) targetPos=0;
		if(i==4) targetPos=6;

		for(;;){
			PFPos ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i],colorOfFace[nFace]);
			pair<PFPosColor,PFPosColor> t=status.CornerGetNeighbor(ppos);
			if(ppos.face==Face::D && t.first.face==Face(i) && t.second.face==Face(nFace)) break;
			if(Any(ppos,t.first.getPFPos(),t.second.getPFPos(),Face::D)){
				t=status.CornerGetNeighbor(ppos);
				if(t.first.pos==6){
					ROTATE(t.first.face);ROTATE(Face::U);ROTATE(inv(t.first.face));
				}
				else{
					ROTATE(inv(t.first.face));ROTATE(Face::U);ROTATE(t.first.face);
				}
				ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i],colorOfFace[nFace]);
				t=status.CornerGetNeighbor(ppos);
			}
			Any(ppos,t.first.getPFPos(),t.second.getPFPos(),Face::U);
			for(;ppos.pos!=UDoppo(targetPos);){
				ROTATE(Face::U);
				ppos=status.SeekPiece(colorOfFace[int(Face::D)],colorOfFace[i],colorOfFace[nFace]);
				t=status.CornerGetNeighbor(ppos);
				Any(ppos,t.first.getPFPos(),t.second.getPFPos(),Face::U);
			}

			ROTATE(Face(i));ROTATE(Face::U);ROTATE(inv(Face(i)));
		}
	}
}

void SolveMiddle(Cube &status, vector<Op> & OpStack)
{
	for(int i=1;i<=4;i++){
		int leftFace=Left(i),rightFace=Right(i);
		PFPos ppos=status.SeekPiece(colorOfFace[i],colorOfFace[rightFace]);
		PFPosColor neighbor=status.EdgeGetNeighbor(ppos);
		if(ppos.face==Face(i) && neighbor.face==Face(rightFace)) continue;
		if(ppos.face!=Face::U && neighbor.face!=Face::U){
			Face l=Face(Left(int(ppos.face))),r=Face(Right(int(ppos.face)));
			if(ppos.pos==5){
				ROTATE(Face::U);ROTATE(r);
				ROTATE(Face::Ui);ROTATE(inv(r));
				ROTATE(Face::Ui);ROTATE(inv(ppos.face));
				ROTATE(Face::U);ROTATE(ppos.face);
			}
			else{
				ROTATE(Face::Ui);ROTATE(inv(l));
				ROTATE(Face::U);ROTATE(l);
				ROTATE(Face::U);ROTATE(ppos.face);
				ROTATE(Face::Ui);ROTATE(inv(ppos.face));
			}
			ppos=status.SeekPiece(colorOfFace[i],colorOfFace[rightFace]);
			neighbor=status.EdgeGetNeighbor(ppos);
		}
		if(ppos.face!=Face::U){
			for(;ppos.face!=Face(i);){
				ROTATE(Face::U);
				ppos=status.SeekPiece(colorOfFace[i],colorOfFace[rightFace]);
				neighbor=status.EdgeGetNeighbor(ppos);
			}
			ROTATE(Face::U);ROTATE(Face(rightFace));
			ROTATE(Face::Ui);ROTATE(inv(Face(rightFace)));
			ROTATE(Face::Ui);ROTATE(inv(Face(i)));
			ROTATE(Face::U);ROTATE(Face(i));
		}
		else{
			for(;neighbor.face!=Face(rightFace);){
				ROTATE(Face::U);
				ppos=status.SeekPiece(colorOfFace[i],colorOfFace[rightFace]);
				neighbor=status.EdgeGetNeighbor(ppos);
			}
			ROTATE(Face::Ui);ROTATE(inv(Face(i)));
			ROTATE(Face::U);ROTATE(Face(i));
			ROTATE(Face::U);ROTATE(Face(rightFace));
			ROTATE(Face::Ui);ROTATE(inv(Face(rightFace)));
		}
	}
}

void SolveTop(Cube &status, vector<Op> & OpStack)
{
	//TODO
}
