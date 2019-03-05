/*************************************************************************
	> File Name: add_row.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年02月15日 星期五 11时18分02秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
void Analysis_xml(void);
void AddRow(int tbl_number,xmlDocPtr doc,xmlNodePtr cur);
void Add(xmlDocPtr doc, xmlNodePtr cur);
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
    //xmlAttrPtr attr;
    /* 进行解析，如果没成功，显示一个错误并停止 */
    doc = xmlParseFile("document.xml");
    if(doc == NULL){
        fprintf(stderr, "Document not parse successfully. \n");
        return;
    }
    /* 获取文档根节点，若无内容则释放文档树并返回 */
    cur = xmlDocGetRootElement(doc);
    //attr = cur ->properties;
    //xmlFreeProp(attr);
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
    AddRow(2,doc,cur);
    xmlSaveFormatFile("document.xml", doc, 0);
}



void AddRow(int tbl_number, xmlDocPtr doc,xmlNodePtr cur){
    /* 遍历文档树 */
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
       /* if(cur -> properties!=NULL){
            xmlAttrPtr attr = cur -> properties;
            if(!xmlStrncmp(attr ->name,(const xmlChar *)"rsid",4)){
                printf("%s\n",attr->name);
                xmlRemoveProp(attr);
            }
        }*/
        if(!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
            tbl_number--;
            printf("%d\n",tbl_number);
            if(!tbl_number){
                xmlNodePtr cur_last=NULL;
                xmlNodePtr cur_copy=NULL;
                cur_last = xmlGetLastChild(cur);
                cur_copy = xmlCopyNode(cur_last,1);
                xmlAddNextSibling(cur_last,cur_copy);

            }
        }
            AddRow(tbl_number,doc,cur);
            cur = cur->next; /* 下一个子节点 */
    }

}
