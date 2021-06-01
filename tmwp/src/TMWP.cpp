#include<tmwp>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace tmwp;
int extensionEquals(const char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}
char * getMIMETYPE(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len<4) return mimeType;
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.') lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"javascript"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
}
if(extensionEquals(resource+lastIndexOfDot+1,"bmp"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/bmp");
}
return mimeType;
}
char isClientSideResource(char *resource)
{
int i;
for(i=0;resource[i]!='\0' && resource[i]!='.';i++);
if(resource[i]=='\0') return 'N' ;
return 'Y'; //this will have to be changed later on
}
REQUEST * parseRequest(char *bytes)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
char **data=NULL;
int dataCount=0;
if(strcmp(method,"GET")==0)
{
// whatever?sdfsdf=xcvxvxvx&wrwerwr=sdfsf&xcvxvxv=sdfsdfs
for(j=0;bytes[i]!=' ';j++,i++)
{
if(bytes[i]=='?') break;
resource[j]=bytes[i];
}
resource[j]='\0';
if(bytes[i]=='?')
{
i++;
int si=i;
dataCount=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='&') dataCount++;
i++;
}
dataCount++;
data=(char **)malloc(sizeof(char *)*dataCount);
int *pc=(int *)malloc(sizeof(int)*dataCount);
i=si;
int j=0;
while(bytes[i]!=' ')
{
if(bytes[i]=='&')
{
pc[j]=i;
j++;
}
i++;
}
pc[j]=i;
i=si;
j=0;
int howManyToPick;
while(j<dataCount)
{
howManyToPick=pc[j]-i;
data[j]=(char *)malloc(sizeof(char)*(howManyToPick+1));
strncpy(data[j],bytes+i,howManyToPick);
data[j][howManyToPick]='\0';
i=pc[j]+1;
j++;
}
}
} // method is of GET type
printf("Request arrived for %s\n",resource);
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->dataCount=dataCount;
request->data=data;
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0')
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char)+strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMETYPE(resource);
}
return request;
}


int urlComparator(void *left,void *right)
{
URL_MAP_NODE *n1,*n2;
char *p,*q;
n1=(URL_MAP_NODE *)left;
n2=(URL_MAP_NODE *)right;
p=n1->url;
q=n2->url;
while(*p && *q && *p==*q)
{
p++;
q++;
}
return (*p)-(*q);
}

TMWebProjector::TMWebProjector(int portNumber)
{
this->portNumber=portNumber;
//this->url=NULL;
//this->ptrOnRequest=NULL;
initBinarySearchTree(&(this->urlBinarySearchTree),sizeof(URL_MAP_NODE),urlComparator);
}
TMWebProjector::~TMWebProjector()
{
//if(this->url) delete [] this->url;
}
void TMWebProjector::onRequest(const char *url,void (*ptrOnRequest)(Request &request,Response &response))
{
//this->urlMap.add(url,ptrOnRequest);
URL_MAP_NODE urlMapNode;
urlMapNode.url=(char *)malloc((sizeof(char)*strlen(url))+1);
strcpy(urlMapNode.url,url);
urlMapNode.ptrOnRequest=ptrOnRequest;
insertNode(&this->urlBinarySearchTree,(void *)&urlMapNode);
/*
if(this->url) delete [] this->url;
this->url=NULL;
this->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
this->url=new char[strlen(url)+1];
strcpy(this->url,url);
this->ptrOnRequest=ptrOnRequest;
*/
}
// I replaced all return 0; with return; in the following method
void TMWebProjector::start()
{
FILE *f;
int length;
int i,rc;
char g;
char responseBuffer[1024]; // A Chunk of 1024
char requestBuffer[8192]; // 8192 = 1024 x 8 
int bytesExtracted;
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int len;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData); // socket library initialized
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
WSACleanup();
return;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(this->portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
char message[101];
if(successCode<0)
{
sprintf(message,"Unable to bind socket to port %d",this->portNumber);
printf("%s\n",message);
WSACleanup();
return;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1)
{
sprintf(message,"TMServer is ready to accept request on port %d",this->portNumber);
printf("%s\n",message);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer),0);
if(bytesExtracted<0)
{
// what to do is yet to be decided
}else
if(bytesExtracted==0)
{
//  what to do is yet to be decided
}
else
{
requestBuffer[bytesExtracted]='\0';
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource=='Y')
{
if(request->resource==NULL)
{
f=fopen("index.html","rb");
if(f!=NULL) printf("Sending index.html\n");
if(f==NULL)
{
f=fopen("index.htm","rb");
if(f!=NULL) printf("Sending index.htm\n");
}
if(f==NULL)
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:163\nConnection: close\n\n<DOCTYPE HTML><html lang='en'><head><meta charset='utf=8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
printf("Sending 404 page\n");
}
else
{
fseek(f,0,2); // move the internal pointer to the end of file
length=ftell(f);
fseek(f,0,0); // move the internal pointer to the start of file
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
else
{
f=fopen(request->resource,"rb");
if(f!=NULL) printf("Sending %s\n",request->resource);
if(f==NULL)
{
// something needs to be done over here
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf=8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2); // move the internal pointer to the end of file
length=ftell(f);
fseek(f,0,0); // move the internal pointer to the start of file
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length:%d\nConnection: close\n\n",request->mimeType,length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
fread(&responseBuffer,rc,1,f);
send(clientSocketDescriptor,responseBuffer,rc,0);
i+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
}
else
{
// more changes required in context to server side resource

//if(this->url==NULL || this->ptrOnRequest==NULL)
//if(this->urlMap.getSize()==0)
if(isEmptyBinarySearchTree(&(this->urlBinarySearchTree)))
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf=8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
//int ii=0;
//if(this->url[0]=='/') ii=1;
char tmp[50001];
if(request->resource[0]!='/') sprintf(tmp,"/%s",request->resource);
else strcpy(tmp,request->resource);
//void (*ptrOnRequest)(Request &,Response &)=this->urlMap.getValue(tmp);
URL_MAP_NODE urlMapNode1,urlMapNode2;
urlMapNode1.url=tmp;
getNodeValue(&(this->urlBinarySearchTree),(void *)&urlMapNode1,(void *)&urlMapNode2);
void (*ptrOnRequest)(Request &,Response &)=urlMapNode2.ptrOnRequest;
//if(strcmp(this->url+ii,request->resource)==0)
if(ptrOnRequest!=NULL)
{
Request rq(request,this,clientSocketDescriptor);
Response rs(clientSocketDescriptor);
//this->ptrOnRequest(rq,rs);
ptrOnRequest(rq,rs);
if(request->data!=NULL)
{
for(int k=0;k<request->dataCount;k++) free(request->data[k]);
free(request->data);
}
/*
printf("Sending processed page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf=8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s processed</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
*/
}
else
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf=8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nConnection: close\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
}


}
}


} // the infinite loop related to accept method ends here

/*if(successCode>0)
{
printf("Response sent\n");
}
else
{
printf("Unable to send response\n");
}*/
closesocket(serverSocketDescriptor);
WSACleanup();
return;
}
void URLEncoder::encode(char *url,char *encodedUrl)
{
char *p;
int x,y,i;
char c1,c2;
for(p=url,i=0;*p!='\0';p++,i++)
{
if((*p>=65 && *p<=90) || (*p>=97 && *p<=122) || (*p>=48 && *p<=57) || (*p=='-') || (*p=='_') || (*p=='.') || (*p=='~'))
{
encodedUrl[i]=*p;
continue;
}
if(*p==' ') //space
{
encodedUrl[i]='+';
continue;
}
encodedUrl[i]='%';
i++;
x=*p;
y=(x%16)+48;
c2=y;
if(y>57) c2=y+7;
x=x/16;
y=(x%16)+48;
c1=y;
if(y>57) c1=y+7;
x=x/16;
encodedUrl[i]=c1;
i++;
encodedUrl[i]=c2;
}
encodedUrl[i]='\0';
}
void URLDecoder::decode(char *url,char *decodedUrl)
{
char *p;
int x,y,i;
char c;
for(p=url,i=0;*p!='\0';p++,i++)
{
if(*p=='%')
{
p++;
if(*p=='\0')
{
decodedUrl[0]='\0';
return;
}
y=*p;
y=y-48;
if(y>=17 && y<=22) y=y-7; 
x=(16*y);
p++;
if(*p=='\0')
{
decodedUrl[0]='\0';
return;
}
y=*p;
y=y-48;
if(y>=17 && y<=22) y=y-7;  
x=x+y;
c=x;
decodedUrl[i]=c;
continue;
}
if(*p=='+') //space
{
decodedUrl[i]=' ';
continue;
}
decodedUrl[i]=*p;
}
decodedUrl[i]='\0';
}

int pairComparator(void *left,void *right)
{
PAIR *p1,*p2;
char *p,*q;
p1=(PAIR *)left;
p2=(PAIR *)right;
p=p1->name;
q=p2->name;
while(*p && *q && *p==*q)
{
p++;
q++;
}
return (*p)-(*q);
}
Request::Request(REQUEST *request)
{
PAIR pair;
int i,j,length;
char *p,*q,*name,*value,*decodedValue;
this->forward=0;
this->request=request;
//this->data=(char ***)malloc(sizeof(char **)*(this->request->dataCount));
initBinarySearchTree(&(this->requestDataBinarySearchTree),sizeof(PAIR),pairComparator);
for(i=0;i<(this->request->dataCount);i++)
{
//this->data[i]=(char **)malloc(sizeof(char *)*2);
p=this->request->data[i];
for(q=p;*q!='\0' && *q!='=';q++);
length=(q-p);
name=(char *)malloc(sizeof(char)*(length+1));
strncpy(name,p,length);
name[length]='\0';
//this->data[i][0]=name;
pair.name=name;
for(length=0,p=q+1;*p!='\0';length++,p++)
{
if(*p=='%') length-=2;
}
value=(char *)malloc(sizeof(char)*(length+1));
URLDecoder::decode(q+1,value);
//this->data[i][1]=value;
pair.value=value;
insertNode(&(this->requestDataBinarySearchTree),(void *)&pair);
}
}
Request::~Request()
{
// not yet implemented
}
/*
char * Request::get(const char *name)
{
int size,i;
size=this->request->dataCount;
for(i=0;i<size && strcmp(this->data[i][0],name)!=0;i++);
if(i==size) return NULL;
return this->data[i][1];
}
*/
char *Request::get(const char *name)
{
PAIR pair1,pair2;
int s;
pair1.name=(char *)malloc(sizeof(char)*(strlen(name)+1));
strcpy(pair1.name,name);
s=getNodeValue(&(this->requestDataBinarySearchTree),(void *)&pair1,(void *)&pair2);
free(pair1.name);
if(s==0) return NULL;
return pair2.value;
}

void Request::forward(const char *resource)
{
this->isForward=1;
}
Response::Response(int clientSocketDescriptor)
{
this->clientSocketDescriptor=clientSocketDescriptor;
this->headerStatus=0;
this->isConnectionOpen=1;
}
void Response::sendHeader()
{
char responseBuffer[1024];
if(this->isConnectionOpen==0 || this->headerStatus==1) return;
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nConnection: close\n\n");
send(this->clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
this->headerStatus=1;
}
void Response::write(const char *byteStream)
{
int length,i,rc;
if(this->isConnectionOpen==0) return;
if(this->headerStatus==0) this->sendHeader();
length=strlen(byteStream);
i=0;
while(i<length)
{
rc=length-i;
if(rc>1024) rc=1024;
send(this->clientSocketDescriptor,byteStream+i,rc,0);
i+=rc;
}
}
void Response::close()
{
if(this->isConnectionOpen==0) return;
closesocket(this->clientSocketDescriptor);
this->isConnectionOpen=0;
}

/*
URLMap::URLMap()
{
this->size=0;
this->top=NULL;
}
int URLMap::getSize()
{
return this->size;
}
void URLMap::add(const char *url,void (*ptrOnRequest)(Request &request,Response &response))
{
URL_MAP_NODE *node;
node=(URL_MAP_NODE *)malloc(sizeof(URL_MAP_NODE));
node->url=NULL;
node->ptrOnRequest=NULL;
if(url==NULL || ptrOnRequest==NULL) return;
node->url=new char[strlen(url)+1];
strcpy(node->url,url);
node->ptrOnRequest=ptrOnRequest;
node->next=this->top;
this->top=node;
this->size++;
}
void URLMap::remove(const char *url)
{
URL_MAP_NODE *p1,*p2;
p1=this->top;
p2=NULL;
while(p1!=NULL)
{
if(strcmp(p1->url,url)==0) break;
p2=p1;
p1=p1->next;
}
if(p1==NULL) return;
if(p2==NULL) this->top=p1->next;
else p2->next=p1->next;
this->size--;
delete [] p1->url;
free(p1);
}
URLMap::~URLMap()
{
this->removeAll();
}
void URLMap::removeAll()
{
URL_MAP_NODE *p;
p=this->top;
while(p!=NULL)
{
delete [] p->url;
free(p);
p=p->next;
}
this->size=0;
this->top=NULL;
}
void (*URLMap::getValue(const char *url))(Request &request,Response &response)
{
URL_MAP_NODE *p;
p=this->top;
while(p!=NULL)
{
if(strcmp(p->url,url)==0) break;
p=p->next;
}
if(p==NULL) return NULL;
return p->ptrOnRequest;
}
*/