#include "client.h"

size_t RestClient::AckResPrint(void *ptr, size_t size, size_t count, void *stream) {
    ((string*) stream)->append((char*) ptr, 0, size * count);
    return size * count;
}

int RestClient::OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *) {
    if (itype == CURLINFO_TEXT) {
        printf("[TEXT]%s\n", pData);
    } else if (itype == CURLINFO_HEADER_IN) {
        cout << "[emay] sent in header[" << pData << "]" << endl;
    } else if (itype == CURLINFO_DATA_IN) {
        cout << "[emay] sent in data[" << pData << "]" << endl;
    } else if (itype == CURLINFO_HEADER_OUT) {
        cout << "[emay] sent out header[" << pData << "]" << endl;
    } else if (itype == CURLINFO_DATA_OUT) {
        cout << "[emay] sent out data[" << pData << "]" << endl;
    }
    return 0;
}

int RestClient::connectSocket()
{
	if (m_pCurl == NULL)
	{
		curl_global_init (CURL_GLOBAL_ALL);
		m_pCurl = curl_easy_init();
		if (m_pCurl == NULL)
		{
			printf("fail, initialize curl\n");
			return 1;
		}
	}
	return 0;
}

int RestClient::disconnectSocket()
{
	if (m_pCurl != NULL)
	{
		curl_easy_cleanup(m_pCurl);
		curl_global_cleanup();
	}
	return 0;
}

int RestClient::sendMessage(string msg)
{
	string strURL;
	string strBody;

	strURL = "http://"+m_sIp+":"+m_iPort;
	strBody = msg;

	struct curl_slist *Headers = NULL;
	Headers = curl_slist_append(Headers, "Content-Type: application/x-www-form-urlencoded");
	//Headers = curl_slist_append(Headers, "Content-Type: text/xml");

	if (Headers == NULL)
	{
		printf ("fail, NOT Working Header Appending\n");
	}

	string sRes;

	curl_easy_setopt(m_pCurl, CURLOPT_URL, strURL.c_str());
    curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, AckResPrint);
    curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, &sRes);
    curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, strBody.c_str());
    curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, strBody.length());
    curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);

	curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 1);
	curl_easy_setopt(m_pCurl, CURLOPT_DEBUGFUNCTION, OnDebug);

	const CURLcode rc = curl_easy_perform(m_pCurl);
    if (CURLE_OK != rc) {
        printf ("fail, Error from cURL: %d:%s", rc, curl_easy_strerror(rc));
        curl_slist_free_all(Headers);
        disconnectSocket();
        return 0;
    } else {
        // get some info about the xfer:
        long statLong = 0;
        // HTTP 응답코드를 얻어온다.
        if (CURLE_OK == curl_easy_getinfo(m_pCurl, CURLINFO_HTTP_CODE, &statLong)) {
            // 200 성공
            if (statLong != 200) {
                printf ("Return Header ERR CODE:%d", statLong);
                curl_slist_free_all(Headers);
                disconnectSocket();
                return 0;
            }
        }
    }

	return 0;
}

int main (int argc, char **argv)
{
	RestClient clnt;

	clnt.setIp("localhost");
	clnt.setPort("9191");

	clnt.connectSocket();
	string msg ="<?xml version=\"1.0\" encoding=\"UTF-8\"?> "
				"<env:Envelope "
				" xmlns:env=\"http://schemas.xmlsoap.org/soap/envelope/\" "
				" xmlns:SOAP-ENC=\"http://schemas.xmlsoap.org/soap/encoding/\" "
				" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" "
				" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" "
				" xmlns:mm7=\"http://www.3gpp.org/ftp/Specs/archive/23_series/23.140/schema/REL-5-MM7-1-0\"> "
				" <env:Header> "
				"        <mm7:TransactionID xmlns:mm7=\"http://www.3gpp.org/ftp/Specs/archive/23_series/23.140/schema/REL-5-MM7-1-0\" env:mustUnderstand=\"1\">AABBCCDDEE</mm7:TransactionID> "
				" </env:Header> "
				" <env:Body> "
				"  <mm7:DeliverReq> "
				"   <MM7Version>1</MM7Version> "
				"   <MMSRelayServerID>1</MMSRelayServerID> "
				"   <Sender>1</Sender> "
				"   <Recipients> "
				"                <To><ShortCode>#3030</ShortCode></To> "
				"        </Recipients> "
				"   <TimeStamp>1</TimeStamp> "
				"   <Subject>1</Subject> "
				"   <Content>1</Content> "
				"  </mm7:DeliverReq> "
				" </env:Body> "
				"</env:Envelope> ";

	clnt.sendMessage(msg);

	return 0;
}
