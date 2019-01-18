/* soapClient.cpp
   Generated by gSOAP 2.8.4 from mm7.h

Copyright(C) 2000-2011, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
1) GPL or 2) Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#if defined(__BORLANDC__)
#pragma option push -w-8060
#pragma option push -w-8004
#endif
#include "soapH.h"

SOAP_SOURCE_STAMP("@(#) soapClient.cpp ver 2.8.4 2019-01-04 08:55:29 GMT")


SOAP_FMAC5 int SOAP_FMAC6 soap_call_mm7__DeliverReq(struct soap *soap, const char *soap_endpoint, const char *soap_action, char *MM7Version, char *MMSRelayServerID, char *Sender, char *Recipients, char *TimeStamp, char *Subject, char *Content, struct mm7__DeliverRsp *DeliverRsp)
{	struct mm7__DeliverReq soap_tmp_mm7__DeliverReq;
	soap->encodingStyle = NULL;
	soap_tmp_mm7__DeliverReq.MM7Version = MM7Version;
	soap_tmp_mm7__DeliverReq.MMSRelayServerID = MMSRelayServerID;
	soap_tmp_mm7__DeliverReq.Sender = Sender;
	soap_tmp_mm7__DeliverReq.Recipients = Recipients;
	soap_tmp_mm7__DeliverReq.TimeStamp = TimeStamp;
	soap_tmp_mm7__DeliverReq.Subject = Subject;
	soap_tmp_mm7__DeliverReq.Content = Content;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize_mm7__DeliverReq(soap, &soap_tmp_mm7__DeliverReq);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put_mm7__DeliverReq(soap, &soap_tmp_mm7__DeliverReq, "mm7:DeliverReq", NULL)
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put_mm7__DeliverReq(soap, &soap_tmp_mm7__DeliverReq, "mm7:DeliverReq", NULL)
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!DeliverRsp)
		return soap_closesock(soap);
	soap_default_mm7__DeliverRsp(soap, DeliverRsp);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	soap_get_mm7__DeliverRsp(soap, DeliverRsp, "mm7:DeliverRsp", "");
	if (soap->error)
		return soap_recv_fault(soap, 0);
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

#if defined(__BORLANDC__)
#pragma option pop
#pragma option pop
#endif

/* End of soapClient.cpp */
