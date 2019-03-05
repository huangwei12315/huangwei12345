/*************************************************************************
	> File Name: add_bookmark_row.cpp
	> Author: amoscykl
	> Mail: amoscykl@163.com 
	> Created Time: 2019年02月22日 星期五 14时45分17秒
 ************************************************************************/


#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
#define URL "http://schemas.openxmlformats.org/wordprocessingml/2006/main"
void AddBookmarkForRow(int tbl_number,int row_number,int column_number_Start,vector<string> &bookname, vector<string> &book_content);
void TraversalxmlForAddRowBook(int tbl_number,int row_number,int column_number_Start,vector<string> &bookname, vector<string> &book_content,xmlDocPtr doc,xmlNodePtr cur,xmlNsPtr *NameSpace);
void AddRowBook(int column_number_Start,int tbl_number_temp,unsigned int counter,vector<string> &bookname, vector<string> &book_content, xmlDocPtr doc, xmlNodePtr cur2,xmlNsPtr *NameSpace);
int main(){
    vector<string> m;
    vector<string> n;
    m.push_back(string("a"));
    m.push_back(string("b"));
    n.push_back(string("1"));
    n.push_back(string("2"));


    AddBookmarkForRow(2,3,2,m,n);
    return 0;
}
void AddBookmarkForRow(int tbl_number,int row_number,int column_number_Start,vector<string> &bookname, vector<string> &book_content){

    xmlKeepBlanksDefault(0);
    /* 定义文档和节点指针 */
    xmlNsPtr *NameSpace;
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
    NameSpace = xmlGetNsList(doc,cur);
    TraversalxmlForAddRowBook(tbl_number,row_number,column_number_Start,bookname,book_content,doc,cur,NameSpace);
    xmlSaveFormatFile("document.xml", doc, 0);
}



void TraversalxmlForAddRowBook(int tbl_number,int row_number,int column_number_Start,vector<string> &bookname, vector<string> &book_content,xmlDocPtr doc,xmlNodePtr cur,xmlNsPtr *NameSpace){
    /* 遍历文档树 */
    int tbl_number_temp = tbl_number;
    unsigned int counter = 0;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
       if(!xmlStrcmp(cur -> name,(const xmlChar *)"tbl")){
            tbl_number--;
            //printf("%d\n",tbl_number);
            if(!tbl_number){
                xmlNodePtr cur1 = NULL;
                cur1 = cur ->xmlChildrenNode;
                while(cur1 != NULL){
                    if(!xmlStrcmp(cur1 -> name,(const xmlChar *)"tr")){
                        row_number --;
                        if(!row_number){
                            xmlNodePtr cur2;
                             cur2 = cur1 -> xmlChildrenNode;
                              while(cur2 != NULL){
                                if(!xmlStrcmp(cur2 -> name,(const xmlChar *)"tc")){
                                    column_number_Start --;
                                    if(column_number_Start <= 0){
                                        if(counter < bookname.size())
                                            counter ++;
                                        else
                                            break;
                                        AddRowBook(column_number_Start,tbl_number_temp,counter,bookname,book_content,doc,cur2,NameSpace);
                                    }
                                }
                                cur2 = cur2 ->next;
                           }
                        }
                    }
                    cur1 = cur1 -> next;
                }
            }
        }
        TraversalxmlForAddRowBook(tbl_number,row_number,column_number_Start,bookname,book_content,doc,cur,NameSpace);
        cur = cur->next; /* 下一个子节点 */
    }
}

void AddRowBook(int column_number_Start,int tbl_number_temp,unsigned int counter,vector<string> &bookname, vector<string> &book_content, xmlDocPtr doc, xmlNodePtr cur2,xmlNsPtr *NameSpace){
    string buf_temp_name = bookname[counter-1];
    const char *buf_bookName = buf_temp_name.c_str();
    //printf("%s\n",buf_bookName);
    string buf_temp_cotent = book_content[counter-1];
    const char *buf_bookContent = buf_temp_cotent.c_str();
    //printf("%s\n",buf_bookContent);
    cur2 = cur2 -> children;
    while(cur2 != NULL){
        if(!xmlStrcmp(cur2 -> name,(const xmlChar *)"pPr")){
            printf("%s\n",cur2 ->name);
            xmlNodePtr cur_bookstart = NULL;
            xmlNodePtr cur_bookend =NULL;
            xmlNodePtr cur_rpr = NULL;
            xmlNodePtr cur_copy = NULL;
            xmlNodePtr cur_r = NULL;
            xmlNodePtr cur_t = NULL;
            xmlChar* content = NULL;
            cur_rpr = cur2 -> children;
            while(cur_rpr != NULL){
                if(!xmlStrcmp(cur_rpr -> name,(const xmlChar *)"rPr"))
                    cur_copy = xmlCopyNode(cur_rpr,1);
                cur_rpr = cur_rpr->next;
            }
            if(cur2 -> next == NULL){
                cur_bookstart = xmlNewNode(NameSpace[10],(const xmlChar *)"bookmarkStart");
                xmlAddNextSibling(cur2,cur_bookstart);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                content = xmlGetProp(cur_bookstart,(const xmlChar*)"id");
                cur_r = xmlNewNode(NameSpace[10],(const xmlChar *)"r");
                xmlAddNextSibling(cur_bookstart,cur_r);
                xmlAddChild(cur_r,cur_copy);
                cur_t = xmlNewNode(NameSpace[10],(const xmlChar *)"t");
                xmlAddNextSibling(cur_copy,cur_t);
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                cur_bookend = xmlNewNode(NameSpace[10],(const xmlChar *)"bookmarkEnd");
                xmlAddNextSibling(cur_r,cur_bookend);
                xmlSetNsProp(cur_bookend,NameSpace[10],(const xmlChar*)"id",(const xmlChar*)buf_bookName);
            }

        }
        AddRowBook(column_number_Start, tbl_number_temp,counter, bookname,book_content,  doc, cur2, NameSpace);
        cur2= cur2 -> next;
    }
}


