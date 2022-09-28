#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


void checkdeps(char *pkg) {
};

// reads a packages contents and prints them out.
void readPkg(char *path)
{
	FILE *fp;
	int c;

	fp = fopen(path, "r");
	if (fp) {
		while(1) {
			c = fgetc(fp);
			if( feof(fp) ) { 
				break ;
			}
			printf("%c", c);
		}
		fclose(fp);
	} else {
		printf("Invalid file location.\n");
	}
}

void getPkg() 
{
	// There should be a build directory in /var/tmp.	
}

int fetchPkg()
{
	// Implent curl to read the raw git content of tarot/tarot-pkgs.
	
	return 0;
}

void upgradeSys()
{
	FILE *fp;
	int c;
	fp = fopen("./tpmdata.tpm", "r");
	while(1) {
		c = fgetc(fp);
		if( feof(fp) ) { 
			break;
		}
	printf("%c", c);
	}
}


// Return true if match, else return false.
int checkPkg(char *vsrc, char *vdst) 
{
	if(strcmp(vsrc, vdst) == 0) {
		return 1;
	} else {
		return 0;
	}
} // redudant??

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

int buildPkg(char *packageName) 
{
	// TO-DO
	// Make sure it actually appends to tarot-pkgs/
	if (checkStoredPkg(packageName) == 1) { return 0; }

	system("./test.sh");
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

char *fetchBuild(char *pkgName) 
{
	char gitlink[512] = "https://raw.githubusercontent.com/tarot-linux/tarot-pkgs/main/"; 
	strcat(gitlink, pkgName);
	strcat(gitlink, "/build");
	return gitlink;
}

char *fetchInfo(char *pkgName) 
{
	char gitlink[512] = "https://raw.githubusercontent.com/tarot-linux/tarot-pkgs/main/"; 
	strcat(gitlink, pkgName);
	strcat(gitlink, "/info");
	return gitlink;
}

char *fetchDeps(char *pkgName) 
{
	char gitlink[512] = "https://raw.githubusercontent.com/tarot-linux/tarot-pkgs/main/"; 
	strcat(gitlink, pkgName);
	strcat(gitlink, "/deps");
	return gitlink;
}


int downloadBuild(char *pkgName) 
{
	FILE *fp;
	char *packageUrl = fetchBuild(pkgName);
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

		if(curl) {
			fp = fopen("./test.sh", "wb");
			chmod("./test.sh", S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
			curl_easy_setopt(curl, CURLOPT_URL, packageUrl);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK)
				printf("oops");

			curl_easy_cleanup(curl);
			fclose(fp);
		}
		// maybe cut this function up?
	return 0;
}

int downloadDeps(char *pkgName) 
{
	FILE *fp;
	char *packageUrl = fetchDeps(pkgName);
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
		if(curl) {
			fp = fopen("deps.txt", "wb");
			curl_easy_setopt(curl, CURLOPT_URL, packageUrl);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			res = curl_easy_perform(curl);
			if(res != CURLE_OK)
				printf("oops");

			curl_easy_cleanup(curl);
			fclose(fp);
		}
	// maybe cut this function up?
	return 0;
}


void matchDependencies() {
	FILE *fp;
	int c;
	char line[512];
	
	fp = fopen("deps.txt", "r");
	if (fp) {
		while(fgets(line, 512, fp)) {
			printf("%s", line);
			downloadBuild(line);
			buildPkg(line);
		}
	}
	fclose(fp);
}

int main(int argc, char *argv[])
{
	downloadDeps("vim");
	matchDependencies();
	return 0;
	// Implement a command system.
}
