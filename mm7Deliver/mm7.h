struct SOAP_ENV__Header
{
    mustUnderstand char* mm7__TransactionID;
};

struct StatusTree
{
    char *StatusCode;
    char *StatusText;
    char *Detail;
};

struct mm7__DeliverRsp
{
    char* MM7Version;
    char *ServiceCode;
    struct StatusTree *Status;
};

int mm7__DeliverReq(char *MM7Version, char *MMSRelayServerID, char *Sender, char *Recipients, char *TimeStamp, char *Subject, char *Content, struct mm7__DeliverRsp *DeliverRsp);
