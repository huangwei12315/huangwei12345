/*************************************************************************
	> File Name: DeleteCloumn.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年02月14日 星期四 15时27分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
void Analysis_xml(void);
void DeleteColumn(int tbl_number,int column_number,xmlDocPtr doc,xmlNodePtr cur);
void Delete(int column_number, xmlDocPtr doc, xmlNodePtr cur);
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
    DeleteColumn(2,3,doc,cur);
    xmlSaveFormatFile("document.xml", doc, 0);
}



void DeleteColumn(int tbl_number,int column_number,xmlDocPtr doc,xmlNodePtr cur){
    /* 遍历文档树 */
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
	   //printf("%s\n",cur->name);
        if(!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
            tbl_number--;
			printf("%d\n",tbl_number);
            if(!tbl_number){
                Delete(column_number,doc,cur);
            }
        }
            DeleteColumn(tbl_number,column_number,doc,cur);
            cur = cur->next; /* 下一个子节点 */
    }

}

void Delete(int column_number, xmlDocPtr doc, xmlNodePtr cur){
    cur = cur -> children;
    while(cur != NULL){
	//	printf("%s\n",cur->name);
                 if(cur != NULL&&! xmlStrcmp(cur -> name,(const xmlChar *)"tr")){
                     int column_number_temporary;
                     column_number_temporary = column_number;
					   xmlNodePtr cur1;
					   cur1 = cur;
                       cur1 = cur1 -> children;
                    while(cur1 != NULL){
						printf("%s\n",cur1->name);
                        if(!xmlStrcmp(cur1 -> name,(const xmlChar *)"tc")){
                            column_number_temporary--;
                            printf("%d\n",column_number_temporary);
                          if(!column_number_temporary){
                             xmlNodePtr cur2;
                             cur2 = cur1;
                             cur1 = cur1 -> next;
                             xmlUnlinkNode(cur2);
                             xmlFreeNode(cur2);
                          }
                    }
                         cur1 = cur1->next;
                    }
	}
         Delete(column_number,doc,cur);
        cur = cur -> next;
		}
}
