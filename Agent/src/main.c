#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <rpcdce.h>
#include <curl/curl.h>
#include <time.h>


#define C2_SERVER_URL "https://localhost:5107"

RPC_CSTR generate_uuid(){
	UUID uuid;
	RPC_CSTR str = NULL;
	if(UuidCreate(&uuid) == RPC_S_OK && UuidToStringA(&uuid, &str) == RPC_S_OK){
		return str;
	}

	return NULL;
}
		
	
int main(){		

	RPC_CSTR agent_uuid = generate_uuid();
	// Debug get rid of
	if(agent_uuid){
		
	printf("Generated unique Agent UUID: %s\n", agent_uuid);	
	
	}
	else printf("Failed to generate UUID\n");

	// libcurl
	// serve as a handle
	CURL *curl = curl_easy_init();
	CURLcode status;
	if(curl){

		time_t current = time(NULL);
		char timestamp[20];
		strftime(timestamp, sizeof(timestamp), "%Y-%m-%d%H:%M:%SZ", gmtime(&current));
		char post_data[256];
		snprintf(post_data, sizeof(post_data), "{\"AgentId\": \"%s\", \"Timestamp\": \"%s\"}", agent_uuid, timestamp);
		
		// setting options for cul
		curl_easy_setopt(curl, CURLOPT_URL, C2_SERVER_URL);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		status = curl_easy_perform(curl);
		if(status != CURLE_OK){
			fprintf(stderr, "Request failed.\n");
		}

		else{
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			printf("POST request sent, response code: %s\n", response_code);
		
		}
	}
	else {
		fprintf(stderr, "Initialization failed\n");
		return EXIT_FAILURE;
	}
	
	Sleep(10000);

	return 0;
}
