/*************************************************************************
	> File Name: DeleteBookmarkInParaph.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年03月01日 星期五 15时36分52秒
 ************************************************************************/

#include<iostream>
using namespace std;

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
void Analysis_xml(void);
void DeleteBookmarkInParaph(const string &bookmark_name,xmlDocPtr doc,xmlNodePtr cur);
xmlNodePtr DeleteParaph(const string &bookmark_name,xmlDocPtr doc,xmlNodePtr cur);
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
    ChangeBookmark("m另选区",doc,cur);
    xmlSaveFormatFile("document.xml", doc, 0);
}
xmlChar* attr_id_hide = NULL;
xmlChar* attr_id_value = NULL;
void DeleteBookmarkInParaph(const string &bookmark_name,xmlDocPtr doc,xmlNodePtr cur){
    /* 遍历文档树 */
    xmlNodePtr cur_start = NULL;
    xmlNodePtr cur_end = NULL;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if(!xmlStrcmp(cur -> name,(const xmlChar*)"p")){
            cur_start = cur;
            cur_end = cur;
            DeleteParaph(bookmark_name,doc,cur,cur_start,cur_end)
        }
        DeleteBookmarkInParaph(bookmark_name,doc,cur);
        cur = cur -> next;
    }

}
xmlNodePtr DeleteParaph(const string &bookmark_name,xmlDocPtr doc,xmlNodePtr cur,xmlNodePtr cur_start,xmlNodePtr cur_end){
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if(!xmlStrcmp(cur ->name,(const xmlChar*)"BookmarkStart"&&!xmlStrcmp((const xmlChar*)bookmark_name.data(),(const xmlChar*)xmlGetProp(cur,(const xmlChar*)"name")))){
            return
        }
        DeleteParaph(bookmark_name,doc,cur,cur_start,cur_end);
        cur = cur->next;
    }
}
