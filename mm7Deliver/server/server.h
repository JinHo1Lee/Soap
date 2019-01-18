#include <iostream>
#include <soapH.h>

using namespace std;

SOAP_NMAC struct Namespace namespaces[] =
{
	{"env", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"mm7", "http://www.3gpp.org/ftp/Specs/archive/23_series/23.140/schema/REL-5-MM7-1-0", "http://www.3gpp.org/ftp/Specs/aarchive/23_series/23.140/schema/REL-5-MM7-1-0", NULL},
	{"X-SKT", "http://vmms.nate.com:8282/soap/skt-schema-0226.xsd", "http://vmms.nate.com:8282/soap/skt-schema-*.xsd", NULL},
	{NULL, NULL, NULL, NULL}
};

