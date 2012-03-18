/*
*	Copyright 2012, Andrea Mazzotti <amm263@gmail.com>
*
*	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted,
*	provided that the above copyright notice and this permission notice appear in all copies.
*
*	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
*	INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
*	ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
* 	OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING 
*	OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*
*/

/*
*	Input: an array of WORD (signed) containing the coordinates of point p.
*		   an array of WORD (signed) containing the coordinates of n points belonging to the set I (ex. m=3, n=2, pointset[]={x1,y1,z1,x2,y2,z3}).
*		   two DWORD (unsigned) containing rispectively the number of dimension of each point (m) and the number of point (n) in the set I.	
*
*	Output: two WORD (unsigned) where memorize the indexes of the nearest and the furthest point from p.
*/

#include <stdio.h>

void main()
{
	// Input
	short pointP[]={99,91,-88,-12,100,-95,-4,63,-31,-71,-39,-22,-17}; //Point p
	short pointset[]={74,-38,49,-19,93,93,98,-35,34,73,50,-13,71,-17,21,92,-90,-75,-98,14,10,-33,47,29,-97,51,37,23,-31,-84,-83,79,10,-95,17,-67,43,-60,-8,-47,-66,-95,-35,-83,-37,-100,-71,22,76,72,-41,-96,-41,64,73,6,16,-80,-22,-58,-44,-25,97,17,56,71,78,65,67,-12,-52,70,33,50,-20,4,-99,29,-35,-97,21,-86,47,-2,58,-88,20,47,-67,-90,18,23,63,-50,97,60,-91,49,-39,-8,-77,-35,55,-12,23,-11,-28,9,-16,-32,4,87,55,-26,21,-59,28,-2,59,44,-49,-70,31,57,70,26,-93,-18,53,20,-5,-47,-33,74,81,-44,-41,-41,75,-31,41,-90,-38,65,7,31,68,-12,30,56,-68,11,90,18,-59,93,34,99,18,97,-19,90,56,64,73,-50,19,82,-6,-36,82,-32,23,-10,-97,-60,68,67,-50,-62,59,20,53,98,-12,85,-37,50,32,88,23,-39,42,78,88,51,-46,-1,92,-44,-88,87,94,-35,74,65,88,-1,15,-100,-76,67,49,-21,-62,61,-64,59,-24,89,88,70,-51,6,42,21,26,45,3,-48,87,-31,75,95,-74,72,26,-12,-76,24,97,65,-66,31,64,56,13,-38,40,-74,14,-4,-78,-97,-31,-58,37,-12,23,-47,-62,-58,97,-37,-86,55,93,55,-47,-33,-65,49,35,53,92,-77,36,18,43,87,-93,-37,-95,-24,38,-10,-53,72,25,85,-65,-62,66,71,-15,55,68,71,17,-92,63,59,-91,-27,92,66,62,-30,-89,-54,7,-82,45,36,-55,75,-64,21,26,25,8,-79,-71,-32,-69,98,84,64,-33,-63,-45,65,-99,35,-77,-51,-47,33,-15,72,29,78,60,-21,-23,-84,-7,-71,26,10,18,-54,-55,93,1,42,29,42,-59,95,83,98,-98,75,91,42,-83,-90,13,97,22,4,-65,54,96,30,-38,50,91,-85,4,54,-62,57,19,-92,19,-91,-67,-18,20,12,-8,-9,89,31,75,85,-11,36,100,-17,16,30,89,-86,-90,-8,97,71,-20,80,51,-75,-10,-72,60,-55,-45,82,-77,-93,77,-69,-24,-91,-89,45,65,-36,56,-23,-40,-45,-84,-80,-62,9,68,5,98,-73,-87,-37,-99,41,62,-34,-100,61,72,29,29,8,13,93,6,-15,-47,80,-98,-34,27,32,-85,-98,19,-5}; //Array contenente le coordinate degli n punti
	unsigned int m=13; // Number of dimension of each point.
	unsigned int n=sizeof(pointset)/(sizeof(pointset[0])*m); // Number of points.
	// Output
	unsigned short indiceMin; //Index of the nearest point from p
	unsigned short indiceMax; //Index of the furthest point from p

	__asm
	{
		XOR EDI,EDI
		XOR ESI,ESI
		XOR EDX,EDX
NextPoint:
		MOV EAX,m
		IMUL EAX,n
		CMP EDX,EAX
		JE Fine
		XOR ECX,ECX
		XOR EBX,EBX
SamePoint:
		XOR EAX,EAX
		MOV AX,pointP[ECX*2]
		INC ECX
		SUB AX,pointset[EDX*2]
		INC EDX
		IMUL AX,AX
		ADD EBX,EAX
		CMP ECX,m
		JB SamePoint
		CMP EDX,m
		JE WriteFirstMin
Write:
		CMP EBX,ESI
		JB WriteMin
		CMP EBX,EDI
		JA WriteMax
		JMP NextPoint
WriteMin:
		MOV ESI,EBX
		MOV indiceMin,DX
		SUB indiceMin,1
		JMP NextPoint
WriteMax:
		MOV EDI,EBX
		MOV indiceMax,DX
		SUB indiceMax,1
		JMP NextPoint
WriteFirstMin:
		MOV ESI,EBX
		MOV indiceMin,DX
		SUB indiceMax,1
		JMP Write
Fine:
		XOR EDX,EDX
        MOV EBX,m
        ADD EDX,m
        SUB EDX,1
        SUB indiceMin,DX
		MOV AX,indiceMin
        XOR EDX,EDX
        IDIV BX
        MOV indiceMin,AX
        XOR EDX,EDX
        ADD EDX,m
        SUB EDX,1
        SUB indiceMax,DX
		MOV AX,indiceMax
        XOR EDX,EDX
        IDIV BX
        MOV indiceMax,AX

	}
	//Print
	printf("Index of the nearest point from p: %d\n",indiceMin);
	printf("Index of the furthest point from p: %d\n",indiceMax);
}