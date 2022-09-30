#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


// reads a packages contents and prints them out.

void cleanPkg(char *pkgName) {
	remove(pkgName);
}

int checkStoredPkg(char *packageName) 
{
	FILE *fp;
	int c;
	fp = fopen("./tpmdata.tpm", "r");
	while(1) {
		c = fgetc(fp);
		if( feof(fp) ) {
			printf("%c", c);
			break;
		}
	}
	return 0;
}



void storePkg(char *packageName) 
{
	FILE *fp;
	if (!fopen("./tpmdata.tpm", "r")) {
		fp = fopen("./tpmdata.tpm", "w");	
		fclose(fp);
	} else {
		fp = fopen("./tpmdata.tpm", "a+");
		fprintf(fp, "%s\n", packageName);
	}
}


// FULL PATH for the option. i.e /deps instead of deps.
char *fetchFromGithub(char *pkgName, char *option) {
	// this needs to be on the heap
	char gitlink[512] = "https://raw.githubusercontent.com/tarot-linux/tarot-pkgs/main/"; 
	strcat(gitlink, pkgName);
	strcat(gitlink, option);
	return gitlink;
}

int downloadPkgInfo(char *pkgName, char *option) 
{
	FILE *fp;
	// fetch the link from github
	char *packageUrl = fetchFromGithub(pkgName, option);
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
		if(curl) {
			fp = fopen(pkgName, "wb");
			// set url to fetched link
			curl_easy_setopt(curl, CURLOPT_URL, packageUrl);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK) {
				printf("Could not fetch requested file: %s", pkgName);
			}

			curl_easy_cleanup(curl);
			fclose(fp);
		} else 
		  printf("Could not fetch requested file.");
		
	// maybe cut this function up?
	return 0;
}


void matchDependencies() {
	FILE *fp;
	int c;
	char line[512];
	
	fp = fopen("./deps.txt", "r");
	if (fp) {
		// Read line by line and match deps
		while(fgets(line, 512, fp)) {
			printf("%s", line);
			downloadPkgInfo(line, "/build");
		}
	}
	fclose(fp);
}

void buildPkg(char *pkgName) {
	chmod(pkgName, S_IRWXG);
	char strbuff[512];
	strcat(strbuff, "./");
	strcat(strbuff, pkgName);
	system(strbuff);
}

int main(int argc, char *argv[])
{
	cleanPkg("vim");
	downloadPkgInfo("vim", "/build");
	buildPkg("vim");
	cleanPkg("vim");
	return 0;
	// Implement a command system.
}
