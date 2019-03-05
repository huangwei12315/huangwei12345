/*************************************************************************
    > File Name: add_bookmark.c
    > Author: amoscykl
    > Mail: amoscykl@163.com
    > Created Time: 2019年02月18日 星期一 16时03分27秒
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
void AddBookmarkForColumn(int tbl_number,int row_number_Start,int column_number,vector<string> &bookname, vector<string> &book_content);
void TraversalxmlForAddColumnBook(int tbl_number,int row_number_Start,int column_number,vector<string> &bookname, vector<string> &book_content,xmlDocPtr doc,xmlNodePtr cur,xmlNsPtr *NameSpace);
void AddColumnBook(int column_number,int tbl_number_temp,unsigned int counter,vector<string> &bookname, vector<string> &book_content, xmlDocPtr doc, xmlNodePtr cur2,xmlNsPtr *NameSpace);
int main(){
    //ChangeBookmark("asdad","123");
    vector<string> m;
    vector<string> n;
    m.push_back(string("a"));
    m.push_back(string("b"));
    m.push_back(string("c"));
    m.push_back(string("d"));
    m.push_back(string("e"));
    m.push_back(string("f"));
    m.push_back(string("g"));
    m.push_back(string("h"));
    m.push_back(string("i"));
    n.push_back(string("1"));
    n.push_back(string("2"));
    n.push_back(string("3"));
    n.push_back(string("4"));
    n.push_back(string("5"));
    n.push_back(string("6"));
    n.push_back(string("7"));
    n.push_back(string("8"));
    n.push_back(string("9"));

    AddBookmarkForColumn(2,3,1,m, n);
    return 0;
}
void AddBookmarkForColumn(int tbl_number,int row_number_Start,int column_number,vector<string> &bookname, vector<string> &book_content){

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
    TraversalxmlForAddColumnBook(tbl_number,row_number_Start,column_number,bookname,book_content,doc,cur,NameSpace);
    xmlSaveFormatFile("document.xml", doc, 0);
}



void TraversalxmlForAddColumnBook(int tbl_number,int row_number_Start,int column_number,vector<string> &bookname, vector<string> &book_content,xmlDocPtr doc,xmlNodePtr cur,xmlNsPtr *NameSpace){
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
                    int column_number_temp = column_number;
                    if(!xmlStrcmp(cur1 -> name,(const xmlChar *)"tr")){
                        row_number_Start --;
                        if(row_number_Start <=0){
                            if(counter < bookname.size())
                                counter ++;
                            else if(counter >= bookname.size())
                                break;
                            printf("%d\n",counter);
                            xmlNodePtr cur2 = NULL;
                            cur2 = cur1 ->xmlChildrenNode;
                            while(cur2 != NULL){
                                if(!xmlStrcmp(cur2 -> name,(const xmlChar*)"tc")){
                                    column_number_temp --;
                                    if(!column_number_temp){
                                        //printf("%s\n",cur2->name);
                                        AddColumnBook(column_number,tbl_number_temp,counter,bookname,book_content,doc,cur2,NameSpace);
                                    }
                                }
                                cur2 = cur2 -> next;
                            }
                        }
                    }
                    cur1 = cur1 -> next;
                }
            }
        }
        TraversalxmlForAddColumnBook(tbl_number,row_number_Start,column_number,bookname,book_content,doc,cur,NameSpace);
        cur = cur->next; /* 下一个子节点 */
    }
}

void AddColumnBook(int column_number,int tbl_number_temp,unsigned int counter,vector<string> &bookname, vector<string> &book_content, xmlDocPtr doc, xmlNodePtr cur2,xmlNsPtr *NameSpace){
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
            switch (column_number) {
            case 1:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 2:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 3:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 4:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 5:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 6:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 7:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 8:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 9:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            case 10:
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"name",(const xmlChar*)buf_bookName);
                xmlSetNsProp(cur_bookstart,NameSpace[10],(const xmlChar *)"id",(const xmlChar *)buf_bookName);
                break;
            default:
                printf("this line don't permit to add bookmark\n");
                break;
            }
            content = xmlGetProp(cur_bookstart,(const xmlChar*)"id");
            cur_r = xmlNewNode(NameSpace[10],(const xmlChar *)"r");
            xmlAddNextSibling(cur_bookstart,cur_r);
            xmlAddChild(cur_r,cur_copy);
            cur_t = xmlNewNode(NameSpace[10],(const xmlChar *)"t");
            xmlAddNextSibling(cur_copy,cur_t);
            switch (column_number) {
            case 1:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 2:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 3:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 4:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 5:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 6:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 7:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 8:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 9:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            case 10:
                xmlNodeSetContent(cur_t,(const xmlChar *)buf_bookContent);
                break;
            default:
                break;
            }
            cur_bookend = xmlNewNode(NameSpace[10],(const xmlChar *)"bookmarkEnd");
            xmlAddNextSibling(cur_r,cur_bookend);
            xmlSetNsProp(cur_bookend,NameSpace[10],(const xmlChar*)"id",(const xmlChar*)buf_bookName);
             }

        }
        AddColumnBook(column_number, tbl_number_temp,counter, bookname,book_content,  doc, cur2, NameSpace);
        cur2= cur2 -> next;
    }
}

