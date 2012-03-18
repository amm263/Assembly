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
*	Input: a string (containing the phrase), as an array of BYTE ending with 0
*	
*	Output: an array of 26 WORD (unsigned) containing the number of occurrences
*	of each letter of the alphabet (English), inside the input phrase.
*/


#include <stdio.h>

void main()
{
	//Input
	char frase[]="ThIS Is An ExampLe PhraSE FoR The SCripT 1";//Phrase to evaluate
	//Output
	unsigned short occorrenze[26]; //Occurrences of the 26 letters of the alphabet
	//Utility
	int i=0;
	__asm
	{
		XOR ECX,ECX
	Clean:	
		MOV occorrenze[ECX*2],0
		INC ECX
		CMP ECX,26
		JB Clean
 		XOR ECX,ECX 
		SUB ECX,1
	Analisi:
		INC ECX
		MOV AH,59
		MOV AL,frase[ECX]
		CMP AL,0
		JE Fine
	Minuscole:
		ADD AH,5
		XOR EDX,EDX
		SUB EDX,1
	Find:
		INC EDX
		INC AH
		CMP AH,123
		JE Analisi
		CMP AH,91
		JE Minuscole
		CMP AL,AH
		JNE Find
		INC occorrenze[EDX*2]
		JMP Analisi
	Fine:
	}
	//Print
	for (i=0;i<26;i++)
	{
		printf("%c: %d\n",65+i,occorrenze[i]);
	}
}