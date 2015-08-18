#include<stdio.h>
#include<stdlib.h>
#include<openssl/md5.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
bool compare(char *str, char digest[16]);
void trim(char *str);
int main (int argc, char **argv)
{
	FILE *fh;
	char hash[32] ;
	char *word ; 
	size_t len = 0;
	ssize_t  read;

	strcpy(hash, argv[2]);
	fh = fopen(argv[1], "r");

	if (fh == NULL)
		exit(EXIT_FAILURE);
	
	while ((read = getline(&word, &len, fh)) != EOF){
		trim(word);
		if (compare(word, hash)){
			printf("The word is %s\n", word);
			break;
		}
	}
	printf("%s\n", "Done");
	fclose(fh);

	if (word)
		free(word);

	exit(EXIT_SUCCESS);
	return 0;
}


bool compare(char *word, char hash[16]) {
	unsigned char digest[16];
    int length = strlen(word);
    int i=0;
    MD5_CTX md5;    
    MD5_Init(&md5);

	while (length > 0) {
        if (length > 512) {
            MD5_Update(&md5, word, 512);
        } else {
            MD5_Update(&md5, word, length);
        }
        length -= 512;
        word += 512;
    }

    MD5_Final(digest, &md5);
	char result[64] = "";
    for(i = 0; i < 16; i++) {
		sprintf(result + strlen(result)  ,"%02x", digest[i]);
    }
	if ( strcmp(hash, result) == 0)
		return true;
	return false;
}

void trim(char * s) {
    char * p = s;
    int l = strlen(p);

    while(isspace(p[l - 1])) p[--l] = 0;
    while(* p && isspace(* p)) ++p, --l;

    memmove(s, p, l + 1);
}

