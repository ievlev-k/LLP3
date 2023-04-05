#include <iostream>
#include "client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include "client//include/ast.h"
#include "client/parser.tab.h"
using namespace jsonrpc;
using namespace std;



    int main(int argc, char *argv[]) {
        if (argc < 2) {
            cout << "Usage: ./sampleclient `port`" << endl;
            return 1;
        }

        string addr = "http://localhost:";
        addr += argv[1];
        HttpClient httpClient(addr);
        StubClient c(httpClient, JSONRPC_CLIENT_V2);

        ast_node *this_root = NULL;

        while (true) {
                printf("> ");
                this_root = yyparse();
                if (this_root == NULL) throw JsonRpcException(-1, "Unknown error");

                if (this_root->type== CREATE_NODE){
                    ast_node *curr = this_root->first;
                    string table_name = this_root->fields_one.string;
                    Json::Value paramsList(Json::arrayValue);
                    string value;
                    while (curr != NULL) {
                        switch (curr->first->second->fields_one.data_type) {
                            case NUMERIC_DATA:
                                paramsList.append("INT");
                                break;
                            case FLOAT_NUMERIC_DATA:
                                paramsList.append("DOUBLE");
                                break;
                            case BOOLEAN_DATA:
                                paramsList.append("BOOL");
                                break;
                            case STR_DATA:
                                paramsList.append("STR");
                                break;
                            default:
                                cout << "Unknown column type" << endl;
                        }
                        paramsList.append(curr->first->fields_one.string);

                        curr = curr->second;

                    }
                    cout << c.create__(paramsList, table_name) << endl;

                }else if (this_root->type == INSERT_NODE ){
                    ast_node *curr = this_root -> first;
                    string table_name = this_root -> fields_one.string;
                    Json::Value paramsList(Json::arrayValue);
                    string value;
                    while (curr != NULL){
                        switch (curr->first->second->type) {
                            case NUMBER_NODE:
//                                cout << curr->first->second->type << endl;
                                paramsList.append("INT");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.number);
                                break;
                            case FLOAT_NUMBER_NODE:
//                                cout << curr->first->second->type << endl;
                                paramsList.append("DOUBLE");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.float_number);
                                break;
                            case BOOLEAN_NODE:
                                paramsList.append("BOOL");
//                                cout << curr->first->second->type << endl;
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.boolean);
                                break;
                            case STRING_NODE:
                                paramsList.append("STR");
//                                cout << curr->first->second->type << endl;
                                paramsList.append(curr->first->fields_one.string);

                                paramsList.append(value);
                                break;
                            default:
//                                cout << curr->first->second->fields_one.data_type << endl;
                                cout << "Unknown column type" << endl;
                        }
                        curr = curr -> second;
                    }
                    cout << c.insert__(paramsList, table_name) << endl;
                }else if (this_root -> type == FOR_NODE) {
                    string table_name = this_root -> fields_one.string;
                    Json::Value paramsList(Json::arrayValue);
                    if (this_root -> first != NULL){
                        //selectWhere
                        ast_node * column;
                        ast_node * term;
                        if (this_root ->first ->first -> type == NAME_NODE){
                            column = this_root -> first -> first;
                            term = this_root ->first ->second;
                        }else{
                            column = this_root ->first ->second;
                            term = this_root -> first -> first;
                        }
                        if (column->fields_one.string != table_name) {
                            cout <<" error!" << endl;
                        }
                        string column_name = column->fields_two.string;
                        string column_type;
                        string value;

                        switch (term -> type) {
                            case NUMBER_NODE:
//                                cout << curr->first->second->type << endl;
                                column_type = "INT";
                                value = std::to_string(term->fields_one.number);
                                break;
                            case FLOAT_NUMBER_NODE:
//                                cout << curr->first->second->type << endl;
                                column_type ="DOUBLE";
                                value = std::to_string(term->fields_one.float_number);
                                break;
                            case BOOLEAN_NODE:
                                column_type ="BOOL";
                                value = std::to_string(term->fields_one.boolean);
                                break;
                            case STRING_NODE:
                                column_type = "STR";
                                value = term -> fields_one.string;

                                break;
                            default:
//                                cout << curr->first->second->fields_one.data_type << endl;
                                cout << "Unknown column type" << endl;
                        }
                        cout << c.select__(column_name, column_type, table_name, value) << endl;
                    } else{
                        ast_node * astNode = this_root -> second;
                        string firstTName = astNode -> fields_one.string;
                        string secondTName = astNode -> fields_two.string;
                        cout << c.join__(astNode ->first -> fields_two.string, astNode -> first -> fields_one.string, astNode -> second -> fields_two.string, astNode -> second -> fields_one.string) << endl;
                    }
                } else if (this_root -> type == UPDATE_NODE){
                    string table_name = this_root->fields_one.string;
                    ast_node * column = this_root -> first -> first ->type == NAME_NODE ? this_root -> first->first : this_root -> first ->second;
                    ast_node * term = this_root -> first -> first -> type == NAME_NODE ? this_root -> first -> second : this_root -> first -> first;

                    string value;

                    Json::Value paramsList(Json::arrayValue);
                    switch (term -> type) {
                        case NUMBER_NODE:
//

                            paramsList.append("INT");
                            paramsList.append(column->fields_two.string);
                            paramsList.append(term -> fields_one.number);

                            break;
                        case FLOAT_NUMBER_NODE:
                            paramsList.append("DOUBLE");
                            paramsList.append(column->fields_two.string);
                            paramsList.append(term -> fields_one.float_number);
                            break;
                        case BOOLEAN_NODE:
                            paramsList.append("BOOL");
                            paramsList.append(column->fields_two.string);
                            paramsList.append(term -> fields_one.boolean);
                            break;
                        case STRING_NODE:
                            paramsList.append("STR");
                            paramsList.append(column->fields_two.string);

                            paramsList.append(term -> fields_one.string);

                            break;
                        default:
//                                cout << curr->first->second->fields_one.data_type << endl;
                            cout << "Unknown column type" << endl;
                    }
                    ast_node* curr = this_root -> second;
                    while (curr != NULL){

                        switch (curr->first->second->type) {
                            case INSERT_NODE:
                                paramsList.append("INT");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.number);
                                break;
                            case FLOAT_NUMBER_NODE:
                                paramsList.append("DOUBLE");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.float_number);
                                break;
                            case BOOLEAN_NODE:
                                paramsList.append("BOOL");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.boolean);
                                break;
                            case STRING_NODE:
                                paramsList.append("STR");
                                paramsList.append(curr->first->fields_one.string);
                                paramsList.append(curr->first->second->fields_one.string);
                                break;
                            default:
                                cout << "Unknown column type" << endl;
                        }
                        curr = curr -> second;
                    }
                    cout << c.update__(paramsList, table_name);
                } else if (this_root -> type == REMOVE_NODE){
                    string table_name = this_root -> fields_one.string;

                    ast_node* column = this_root -> first -> first -> type == NAME_NODE ? this_root -> first -> first : this_root -> first -> second;
                    ast_node * term = this_root -> first -> first -> type == NAME_NODE ? this_root -> first -> second : this_root -> first -> first;
                    string column_name = column -> fields_two.string;
                    string column_type;
                    string value;

                    switch (term -> type) {
                        case INSERT_NODE:
                            column_type = "INT";
                            value = to_string(term-> fields_one.number);
                            break;
                        case FILTER_NODE:
                            column_type = "DOUBLE";
                            value = to_string(term-> fields_one.float_number);
                            break;
                        case BOOLEAN_NODE:
                            column_type = "BOOL";
                            value = term->fields_one.boolean ? "true" : "false";
                            break;
                        case STRING_NODE:
                            column_type = "STR";
                            value = term -> fields_one.string;
                            break;
                        default:
                            cout << "Unknown column type" << endl;
                    }
                    cout << c.delete__(column_name, column_type, table_name, value) << endl;
                }
                else{
                    cout << "there isn't this command" << endl;
                }
        }
    }

