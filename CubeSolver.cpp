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
inline Face Left(Face c){return Face(int(c)%4+1);}
inline Face Right(Face c){return Face((int(c)+2)%4+1);}
inline Face Counter(Face c){
	switch (c) {
		case Face::U: return Face::D;
		case Face::B: return Face::F;
		case Face::R: return Face::L;
		case Face::F: return Face::B;
		case Face::L: return Face::R;
		case Face::D: return Face::U;
	}
}

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

	// step1.2: Corner pieces

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

void SolveTopCross(Cube &, vector<Op> &);
void SolveTopCorners(Cube &, vector<Op> &);
void FixTopCorners(Cube &, vector<Op> &);
void FixTopCross(Cube &, vector<Op> &);

void SolveTop(Cube &status, vector<Op> &OpStack)
{
	SolveTopCross(status,OpStack);
	SolveTopCorners(status,OpStack);
	FixTopCorners(status,OpStack);
	FixTopCross(status,OpStack);
}

void SolveTopCross(Cube &status, vector<Op> &OpStack){
	int cnt=0;
	for(int i=1;i<8;i+=2) if(status[int(Face::U)][innerFaceOrder[i]]==colorOfFace[int(Face::U)]) cnt++;
	if(cnt==0){
		ROTATE(Face::F);ROTATE(Face::U);ROTATE(Face::R);
		ROTATE(Face::Ui);ROTATE(Face::Ri);ROTATE(Face::Fi);
		cnt+=2;
	}
	if(cnt==2){
		int i;
		while(status[int(Face::U)][7]==colorOfFace[int(Face::U)]) ROTATE(Face::U);
		for(i=1;i<8;i+=2) if(status[int(Face::U)][innerFaceOrder[i]]==colorOfFace[int(Face::U)]) break;
		if(innerFaceOrder[i]!=1){
			ROTATE(Face::F);ROTATE(Face::R);ROTATE(Face::U);
			ROTATE(Face::Ri);ROTATE(Face::Ui);ROTATE(Face::Fi);
		}
		else{
			if(status[int(Face::U)][5]==colorOfFace[int(Face::U)]) ROTATE(Face::Ui);
			ROTATE(Face::F);ROTATE(Face::U);ROTATE(Face::R);
			ROTATE(Face::Ui);ROTATE(Face::Ri);ROTATE(Face::Fi);
		}
	}
}

void SolveTopCorners(Cube &status, vector<Op> &OpStack){
	for(;;){
		int cnt=0;
		for(int i=0;i<8;i+=2) if(status[int(Face::U)][innerFaceOrder[i]]==colorOfFace[int(Face::U)]) cnt++;
		if(cnt==4) break;
		if(cnt==0){
			for(;status.CornerGetNeighbor(PFPos(Face::U,6)).first.color!=colorOfFace[int(Face::U)];ROTATE(Face::U));
		}
		else if(cnt==1){
			for(;status[int(Face::U)][6]!=colorOfFace[int(Face::U)];ROTATE(Face::U));
		}
		else{
			for(;status.CornerGetNeighbor(PFPos(Face::U,6)).second.color!=colorOfFace[int(Face::U)];ROTATE(Face::U));
		}
		ROTATE(Face::R);ROTATE(Face::U);ROTATE(Face::Ri);ROTATE(Face::U);
		ROTATE(Face::R);ROTATE(Face::U);ROTATE(Face::U);ROTATE(Face::Ri);
	}
}

inline bool TCPCheck(Cube &status,int pos){
	pair<PFPosColor,PFPosColor> t=status.CornerGetNeighbor(PFPos(Face::U,pos));
	return colorOfFace[int(t.first.face)]==t.first.color && colorOfFace[int(t.second.face)]==t.second.color;
}

#define SWAP(c) {\
	ROTATE(inv(Right(c)));ROTATE(c);ROTATE(inv(Right(c)));\
	ROTATE(Counter(c));ROTATE(Counter(c));\
	ROTATE(Right(c));ROTATE(inv(c));ROTATE(inv(Right(c)));\
	ROTATE(Counter(c));ROTATE(Counter(c));\
	ROTATE(Right(c));ROTATE(Right(c));\
	ROTATE(Face::Ui);\
}

void FixTopCorners(Cube &status, vector<Op> &OpStack){
	int cnt=0;
	for(;;){
		cnt=0;
		for(int i=0;i<8;i+=2) if(TCPCheck(status,innerFaceOrder[i])) cnt++;
		if(cnt>=2) break;
		ROTATE(Face::U);
	}
	if(cnt==2){
		if(TCPCheck(status,0) && TCPCheck(status,8)){
			SWAP(Face::F);SWAP(Face::R);
		}
		else if(TCPCheck(status,2) && TCPCheck(status,6)){
			SWAP(Face::F);SWAP(Face::L);
		}
		for(int i=0;i<8;i+=2) if(TCPCheck(status,innerFaceOrder[i]) && TCPCheck(status,innerFaceOrder[(i+2)%8])){
			Face cface=Face(((i>>1)^2)+1);
			SWAP(Face(cface));break;
		}
	}
}

#define __CYC(c,__u){\
	ROTATE(c);ROTATE(c);ROTATE(__u);ROTATE(Left(c));ROTATE(inv(Right(c)));\
	ROTATE(c);ROTATE(c);ROTATE(inv(Left(c)));ROTATE(Right(c));ROTATE(__u);\
	ROTATE(c);ROTATE(c);\
}
#define CYC(c)  __CYC(c,Face::U)
#define CCYC(c) __CYC(c,Face::Ui)

inline bool TEPCheck(Cube &status,int pos){
	PFPosColor t=status.EdgeGetNeighbor(PFPos(Face::U,pos));
	return t.color==colorOfFace[int(t.face)];
}

void FixTopCross(Cube &status, vector<Op> &OpStack){
	int cnt=0;
	for(int i=1;i<8;i+=2) if(!TEPCheck(status,innerFaceOrder[i])) cnt++;
	if(!cnt) return;
	if(cnt==4) CYC(Face::F)
	int cb;cnt=0;
	for(int i=1;i<8;i+=2)
		if(!TEPCheck(status,innerFaceOrder[i])) cnt++;
		else cb=(i>>1)+1;
	if(!cnt) return;
	Face front=Counter(Face(cb));
	if(status[int(front)][1]==colorOfFace[int(Right(front))]) CCYC(front)
	else CYC(front)
}
