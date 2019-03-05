/*************************************************************************
	> File Name: ChangeBookmark.c
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年02月13日 星期三 16时22分05秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
using namespace std;
void Analysis_xml(void);
void ChangeBookmark(const string &bookmark_name,const string &change_name,bool delete_bookmark,xmlDocPtr doc,xmlNodePtr cur);
void ChangeContent(const string &change_name,xmlDocPtr doc,xmlNodePtr cur);
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
    ChangeBookmark("m另选区","黄为",0,doc,cur);
    xmlSaveFormatFile("document.xml", doc, 0);
}
xmlChar* attr_id_hide = NULL;
xmlChar* attr_id_value = NULL;
void ChangeBookmark(const string &bookmark_name,const string &change_name,bool delete_bookmark,xmlDocPtr doc,xmlNodePtr cur){
    /* 遍历文档树 */
    xmlChar* attr_name_value = NULL;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        ChangeBookmark(bookmark_name,change_name,delete_bookmark,doc,cur);
        //printf("%s\n",cur->name);
        if(!xmlStrcmp(cur->name, (const xmlChar *)"bookmarkStart")){
            attr_name_value = xmlGetProp(cur,(const xmlChar *)"name");
          //  printf("%s\n",attr_value);
            if(!xmlStrcmp(attr_name_value,(const xmlChar *)"_GoBack")){
                xmlNodePtr cur_hide_start;
                attr_id_hide = xmlGetProp(cur,(const xmlChar *)"id");
                cur_hide_start = cur;
                cur = cur -> next;
                xmlUnlinkNode(cur_hide_start);
                 xmlFreeNode(cur_hide_start);
            }
        else if(!xmlStrcmp((const xmlChar *)attr_name_value,(const xmlChar *)bookmark_name.data())){
                if(!delete_bookmark){
                    cur = cur->next;
                   ChangeContent(change_name,doc,cur);
                }
                else{
                xmlNodePtr cur_value_start;
                attr_id_value = xmlGetProp(cur,(const xmlChar *)"id");
                cur_value_start = cur;
                cur = cur -> next;
                xmlUnlinkNode(cur_value_start);
                xmlFreeNode(cur_value_start);
                ChangeContent(change_name,doc,cur);
                }
			}
        }
        /*if(attr_id_hide!=NULL)
        printf("%s:hide\n",attr_id_hide);
        if(attr_id_value!=NULL)
            printf("%s:value\n",attr_id_value);*/
              if(!xmlStrcmp(cur->name, (const xmlChar *)"bookmarkEnd")){
                if(attr_id_hide!=NULL&&!xmlStrcmp(attr_id_hide,xmlGetProp(cur,(const xmlChar *)"id"))){
                    printf("%s\n",attr_id_hide);
                   xmlNodePtr cur_hide_end;
                   cur_hide_end = cur;
                   if(cur -> next != NULL)
                   cur = cur -> next;
                  xmlUnlinkNode(cur_hide_end);
                  xmlFreeNode(cur_hide_end);
               }
                  else if(attr_id_value!=NULL&&!xmlStrcmp(attr_id_value,xmlGetProp(cur,(const xmlChar *)"id"))){
                    if(!delete_bookmark){
                        cur = cur->next;
                        continue;
                    }
                    else{
                    printf("%s\n",attr_id_value);
                   xmlNodePtr cur_value_end;
                   cur_value_end = cur;
                   if(cur -> next != NULL)
                   cur = cur -> next;
                   xmlUnlinkNode(cur_value_end);
                   xmlFreeNode(cur_value_end);
                    }
               }
         }

            cur = cur->next; /* 下一个子节点 */
    }

}

void ChangeContent(const string &change_name, xmlDocPtr doc, xmlNodePtr cur){
    cur = cur -> children;
    while(cur != NULL){
                if(!xmlStrcmp(cur -> name,(const xmlChar *)"bookmarkEnd")&&!xmlStrcmp(cur -> name,(const xmlChar *)"bookmarkStart"))
                    cur = cur -> next;
                else if(!xmlStrcmp(cur -> name,(const xmlChar *)"text")){
                    printf("%s\n",cur->name);
                    xmlNodeSetContent(cur,(const xmlChar *)change_name.data());
                }
        ChangeContent(change_name,doc,cur);
        cur = cur -> next;
    }

}
