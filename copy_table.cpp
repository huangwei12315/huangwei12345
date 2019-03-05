/*************************************************************************
    > File Name: copy_table.c
    > Author: amoscykl
    > Mail: amoscykl@163.com
    > Created Time: 2019年02月20日 星期三 15时33分12秒
 ************************************************************************/

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
void CopyTable(int tbl_number);
int TraversalTable(xmlNodePtr cur);
void TraversalCopy(int tbl_number,int tbl_sum,xmlDocPtr doc,xmlNodePtr cur);
void Copy(xmlDocPtr doc, xmlNodePtr cur);
int main(){
    //ChangeBookmark("asdad","123");
    CopyTable(2);
    return 0;
}
void CopyTable(int tbl_number){
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
    tbl_number = tbl_number -1;
    int tbl_sum = TraversalTable(cur);
    printf("%d\n",tbl_sum);
    TraversalCopy(tbl_number,tbl_sum,doc,cur);
    xmlSaveFormatFile("document.xml", doc, 0);
}
int TraversalTable(xmlNodePtr cur){
    cur = cur->xmlChildrenNode->xmlChildrenNode;
    int table_number_cur = 0;
    while(cur !=NULL){
        if(!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
                table_number_cur ++;
    }
        cur = cur -> next;
}
    return table_number_cur;
}

void TraversalCopy(int tbl_number,int tbl_sum,xmlDocPtr doc,xmlNodePtr cur){
    /* 遍历文档树 */
    cur = cur->xmlChildrenNode;
    int copy_tag_number = 0;
    xmlNodePtr cur2[20];
    xmlNodePtr cur3[20];
    while(cur != NULL){
        if(!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
            tbl_sum --;
            tbl_number --;
            if(!tbl_number){
            xmlNodePtr cur_number;
            cur_number = cur->next;
            while(xmlStrcmp(cur_number->name,(const xmlChar*)"tbl")){
                copy_tag_number ++;
                printf("%s\n",cur_number->name);
                cur_number = cur_number -> next;
            }
            copy_tag_number = copy_tag_number+1;
            printf("%d\n",copy_tag_number);
                int MAX_cur;
                cur2[0] = cur->next;
                cur3[0]=xmlCopyNode(cur2[0],1);
                for(MAX_cur = 1;MAX_cur < copy_tag_number;MAX_cur++){
                    cur2[MAX_cur] = cur2[MAX_cur - 1]->next;
                    cur3[MAX_cur]=xmlCopyNode(cur2[MAX_cur],1);
                   // printf("%s\n",cur3[MAX_cur]->name);
               }
            }
        }
        if(tbl_sum ==0&&!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
            //printf("%s\n",cur->next->next->next->next->name);
            int MAX_copy_cur;
            xmlAddNextSibling(cur,cur3[0]);
            for(MAX_copy_cur = 1;MAX_copy_cur < copy_tag_number;MAX_copy_cur ++){
                   xmlAddNextSibling(cur3[MAX_copy_cur -1],cur3[MAX_copy_cur]);
                   printf("11111\n");
               }
            }
        TraversalCopy(tbl_number,tbl_sum,doc,cur);
        cur = cur->next; /* 下一个子节点 */
    }

}

