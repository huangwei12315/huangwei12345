/*************************************************************************
	> File Name: GetAllParaph.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年03月01日 星期五 15时02分21秒
 ************************************************************************/
#include <libxml/parser.h>
#include <libxml/tree.h>
#include<iostream>
using namespace std;
int GetAllParaphNumber(xmlDocPtr doc,xmlNodePtr cur);
void Analysis_xml(void);
int main(){
   //ChangeBookmark("asdad","123");
    Analysis_xml();
   return 0;
}
void Analysis_xml(void){
    xmlKeepBlanksDefault(0);
    /* 定义文档和节点指针 */
    xmlDocPtr doc;
    xmlNodePtr cur;
    int number;
    /* 进行解析，如果没成功，显示一个错误并停止 */
    doc = xmlParseFile("document.xml");
    if(doc == NULL){
        fprintf(stderr, "Document not parse successfully. \n");
        return;
    }
    /* 获取文档根节点，若无内容则释放文档树并返回 */
    cur = xmlDocGetRootElement(doc);
    if(cur == NULL){
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return;
    }
    /* 确定根节点名是否为story，不是则返回 */
     // printf("%s\n",cur->name);
    if(xmlStrcmp(cur->name, (const xmlChar *)"document")){
        fprintf(stderr, "document of the wrong type, root node != document");
        xmlFreeDoc(doc);
        return;
    }
    number = GetAllParaphNumber(doc,cur);
    cout << number <<endl;
    xmlSaveFormatFile("document.xml", doc, 0);
}

int GetAllParaphNumber(xmlDocPtr doc,xmlNodePtr cur){
    static int paraph_number = 0;
    cur = cur -> xmlChildrenNode;
    while(cur !=NULL){
        if(!xmlStrcmp(cur->name,(const xmlChar*)"p")){
            paraph_number++;
        }
        GetAllParaphNumber(doc,cur);
        cur = cur->next;
    }
    return paraph_number;
}

