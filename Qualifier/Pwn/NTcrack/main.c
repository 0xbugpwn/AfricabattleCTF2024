//gcc -pie -Wl,-z,relro,-z,now main.c -o ntc -lcurl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void __() {
  asm volatile ("pop %%rdi\n\t"
      "ret"
      :
      :
      : "rdi");
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, char *data) {
    strcat(data, (char *)ptr);
    return size * nmemb;
}

int curl_ntlm_pw(const char *hash) {
    CURL *curl;
    CURLcode res;
    char url[100];
    char result[1000] = "";

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Erreur lors de l'initialisation de Curl\n");
        return 1;
    }

    snprintf(url, sizeof(url), "https://ntlm.pw/%s", hash);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Erreur lors de la requête Curl: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        //return 1;
    }

    result[strcspn(result, "\n")] = '\0';
    printf(" : %s\n", result);

    curl_easy_cleanup(curl);
    return main();
}

int main() {
    char hash[512];

    printf("\nEntrez le hash NTLM : ");
    fgets(hash, sizeof(hash), stdin);
    hash[strcspn(hash, "\n")] = '\0';
	
	if (strlen(hash) == 0 ) {
    	printf("No hash was provided. Exiting the program.\n");
    	return 1;
	}
	printf(hash);
    return curl_ntlm_pw(hash);
}

__attribute__((constructor))
void myconstructor() {
    printf("\n=== NTLM Hash Cracker ===\n");
}

