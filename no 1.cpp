#include <Stdio.h>
#include <string.h>
#include <ctype.h> 

int main(){
	
	char strA[105];
	char strB[105];
	
	scanf("%s %s", strA, strB);
	
	int lenA = strlen(strA);
	int lenB = strlen(strB);
	
	int karakterAwal = 0;
	
	while(karakterAwal < lenA && karakterAwal < lenB){
		if(strA[karakterAwal] == strB[karakterAwal]){
			karakterAwal++;
		}
		else{
			break;
		}
	}
	
	int KarakterAkhir = 0;
	
	int i = lenA - 1;
	int j = lenB - 1;
	
	while(i >= 0 && j >= 0){
		if(strA[i] == strB[j]){
			KarakterAkhir++;
			i--;
			j--;
		}
		else{
			break;
			
		}
	}
	
	if(karakterAwal == 0 && KarakterAkhir == 0){
		printf("No Output\n");
	}else{
		
		for(int k = 0; k < karakterAwal; k++){
			char c = strA[k];
			
			if(isupper(c)){
				printf("%c", tolower(c));
			}
			else if(islower(c)){
				printf("%c", toupper(c));
			}
			else{
				printf("%c", c);
			}
		}
		
		int startIdxAwal = lenA - karakterAwal;
		for(int k = startIdxAwal; k < lenA; k++){
			char c = strA[k];
			
			if(isupper(c)){
				printf("%c", tolower(c));
			}
			else if(islower(c)){
				printf("%c", toupper(c));
			}
			else{
				printf("%c", c);
			}
			
		}
		
		printf("\n");
	}
	
	return 0;
}
