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
*	Input: an array of BYTE to consider as a sequence of bit;
*		   a WORD (total number of bits).
*
*	Output: an array of WORD in which memorize only the position of bits equals to 1. 
*			Insert -1 to show that the position are over (ending element)
*/


#include <stdio.h>

void main()
{
	//Input
	unsigned char vet[]={0x01};
	unsigned short int len=1;
	int i=0;
	//Output
	short posizioni[1024];
	
	__asm
	{
		Clean:	
		MOV posizioni[ECX*2],-2
		INC ECX
		CMP ECX,1024
		JB Clean
		XOR EAX,EAX
		XOR ECX,ECX
		XOR EDX,EDX
		SUB ECX,1
		PUSH ECX
		SUB DX,1
	Ciclo1:
		POP ECX
		INC ECX
		MOV AH,vet[ECX]
		PUSH ECX
		XOR ECX,ECX
	CicloShift:
		INC ECX
		CMP ECX,9
		JE Ciclo1
		XOR EBX,EBX
		SHR AH,1
		SETC BL
		INC DX
		CMP DX,len
		JE Fine
		CMP BL,1
		JE Salva
		JMP CicloShift
	Salva:
		PUSH ECX
		XOR ECX,ECX
		SUB ECX,1
	CercaVuoto:
		INC ECX
		CMP posizioni[ECX*2],-2
		JNE CercaVuoto
		MOV posizioni[ECX*2],DX
		POP ECX
		JMP CicloShift
	Fine:
		XOR ECX,ECX
		SUB ECX,1
	CercaVuoto2:
		INC ECX
		CMP posizioni[ECX*2],-2
		JNE CercaVuoto2
		MOV posizioni[ECX*2],-1
		POP ECX
	}
	while(i<=len&&posizioni[i]!=-1)
	{
		printf("%d\n",posizioni[i++]);
	}
}