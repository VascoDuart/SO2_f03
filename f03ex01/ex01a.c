#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <tchar.h>			
#include <io.h>	
#include <windows.h>
#include <fcntl.h>

#define _UNICODE
#define MAX 1000

typedef struct {
	DWORD soma;
}TDATA;


BOOL Primo(DWORD num) {
	if (num <= 1) {
		return FALSE; // 0 e 1 não são primos
	}

	for (DWORD d = 2; d * d <= num; d++) {
		if (num % d == 0) {
			return FALSE; // Não é primo
		}
	}
	return TRUE; // É primo
}




DWORD WINAPI somaPares(LPVOID data) {		//LPVOID data --> tdata
	TDATA * td = (TDATA*) data;
	int pares = 0;
	//td->soma = 0;
	for (int i = 0; i <= MAX; i++) {
		if (i % 2 == 0) {
			td->soma += i;
			pares++;
			//_tprintf_s(_T("\n%d"), pares);
			if(pares %200 ==0)
				Sleep(1000);
		}

			

	}
	return 0;
}

DWORD WINAPI somaPrimos(LPVOID data) {		//LPVOID data ==> tdata
	TDATA* td = (TDATA*)data;
	int primos = 0;
	for (int i = 0; i <= MAX; i++) {
		if (Primo(i)) {
			td->soma += i;
			primos++;
			if(primos %200 == 0)
				Sleep(1000);
		}
	}
	return 0;
}

int _tmain() {

#ifdef _UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	HANDLE hThread[2];
	TDATA tData[2];
	DWORD tId[2];
	DWORD i, res, num, pos;
	
	tData[0].soma = 0;
	tData[1].soma = 0;

	hThread[0] = CreateThread(NULL, 0, somaPares, &tData[0], 0, &tId[0]);
	hThread[1] = CreateThread(NULL, 0, somaPrimos, &tData[1], 0, &tId[1]);
	//res = WaitForSingleObject(hThread[0], INFINITE);
	res = WaitForSingleObject(hThread[1], INFINITE);
	//_tprintf_s(_T("Soma Pares = %d\n"), tData[0].soma);
	_tprintf_s(_T("Soma Primos = %d\n"), tData[1].soma);

	/*for (i = 0; i < 5; i++) {
		tData[i].soma = 0; 
	}*/

	num = 5;
	DWORD data[5] = {0,1,2,3,4};

	while (num > 0) {
		res = WaitForInputIdle(num, hThread, FALSE, 10000);	//10 segs espera
		if (res == WAIT_TIMEOUT) {
			_tprintf_s(_T("Ninguém terminou\n"));
		}
		else if (res >= WAIT_OBJECT_0 && res <= (WAIT_OBJECT_0 + num - 1)) {
			pos = res - WAIT_OBJECT_0;
			_tprintf_s(_T("Terminou a thread %d ... \n"), i);
		}
		for (i = pos; i < num - 1; i++) {
			hThread[i] = hThread[i + 1];
			data[i] = data[i + 1];
		}
			
		num--;
	}

	return 0;
}
