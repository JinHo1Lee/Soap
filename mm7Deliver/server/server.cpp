#include "server.h"

void getXmlShortCode(char *xmlString, string & result)
{
    string dup = xmlString;
    if (dup.find("<ShortCode>") == string::npos )
    {
        result = (string)"";
        return ;
    }

    dup.erase(0, dup.find("<ShortCode>")+strlen("<ShortCode>"));
    dup.erase(dup.find("</ShortCode>"), dup.size());

    if( dup.find("#") != string::npos )
    {
        dup.erase(0, dup.find("#"));
    }
    else
    {
        if( dup.find("*") != string::npos )
        {
            dup.erase(0, dup.find("*"));
        }
    }

    result = dup;

    return ;
}


int mm7__DeliverReq(struct soap* soap, char* MM7Version, char* MMSRelayServerID, char* Sender, char* Recipients, char* TimeStamp, char* Subject, char* Content, struct mm7__DeliverRsp* DeliverRsp)
{
	string strRecipients;

	getXmlShortCode (Recipients, strRecipients);
	cout<<"TrancationID : "<<soap->header->mm7__TransactionID<<endl;
	cout<<"Version : "<<MM7Version<<endl;
	cout<<"Serder : "<<Sender<<endl;
	cout<<"Recipeints : "<<strRecipients<<endl;

	DeliverRsp->MM7Version = (char*) soap_malloc(soap, 128);
	strcpy(DeliverRsp->MM7Version, MM7Version);

	DeliverRsp->ServiceCode = (char*) soap_malloc(soap, 32);
	strcpy(DeliverRsp->ServiceCode, "0");

	DeliverRsp->Status = (struct StatusTree*) soap_malloc(soap, 228);
	DeliverRsp->Status->StatusCode = (char*) soap_malloc(soap, 28);
	DeliverRsp->Status->StatusText = (char*) soap_malloc(soap, 100);
	DeliverRsp->Status->Detail = (char*) soap_malloc(soap, 100);

	strcpy(DeliverRsp->Status->StatusCode, "0");
	strcpy(DeliverRsp->Status->StatusText, "Success");
	strcpy(DeliverRsp->Status->Detail, "");

	return 0;
}


int main (int argc, char **argv)
{
	SOAP_SOCKET server_sock, client_sock;
	struct soap soap;
	int iListenPort = 9191;

	soap_init(&soap);

	server_sock = soap_bind(&soap, NULL, iListenPort, 100);

	if (server_sock < 0)
	{
		soap_print_fault(&soap, stderr);
		sleep(1);
		exit(-1);
	}

	while (1)
	{
		client_sock = soap_accept(&soap);

		if (client_sock < 0)
		{
			string result = *soap_faultstring(&soap);
			if (result != "Timeout")
			{
				soap_print_fault(&soap, stderr);
			}
		}
		else
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				if (soap_serve(&soap) != SOAP_OK)
					soap_print_fault(&soap, stderr);

				soap_destroy(&soap);
				soap_end(&soap);
				soap_done(&soap);
				return 0;
			}
		}
	}

	soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap);
	soap_closesocket(server_sock);

	return 0;
}
