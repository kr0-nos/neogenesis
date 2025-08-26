#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <rpc.h>

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

	Sleep(10000);
	// Seed for jitter
	// srand((unsigned int)time(NULL));




	return 0;
}
