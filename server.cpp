#include <iostream>

#include "server.h"
#include "server/include/database_include.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>


using namespace jsonrpc;
using namespace std;

class MyStubServer : public AbstractStubServer {
public:
    MyStubServer(AbstractServerConnector &connector, serverVersion_t type) : AbstractStubServer(connector, type) {};
    virtual std::string open__();
//    virtual std::string delete__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value);
    virtual std::string create__(const Json::Value& paramsList, const std::string& tableName);
    virtual std::string insert__(const Json::Value& paramsList, const std::string& tableName);
    virtual std::string update__(const Json::Value& paramsList, const std::string& tableName);
    virtual std::string select__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value);
    virtual std::string join__(const std::string& firstCName, const std::string& firstTName, const std::string& secondCName, const std::string& secondTName);
    virtual std::string delete__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value);
    virtual void close__() {
        db_close(this->db);
        this->db = NULL;
    }

private:

    database* db = NULL;
};

string MyStubServer::open__(){

        db  = db_get("db.db", SAVED_IN_FILE);

    return "table is open";
}

std::string MyStubServer::select__(const std::string &columnName, const std::string &columnType, const std::string &tableName,const std::string &value){
    if (tableName.empty()) throw JsonRpcException(-1, "Table name was empty");
    if (columnName.empty()) throw JsonRpcException(-1, "Column name was empty");
    if (columnType.empty()) throw JsonRpcException(-1, "Column type was empty");
    if (value.empty()) throw JsonRpcException(-1, "Value was empty");

    table* table = table_get(tableName.c_str(), this ->db);

    int int_val;
    double double_val;
    bool bool_val;
    string string_val;
    void* val;
    if (columnType == "STR") {
        string_val =value.c_str();
        val = (void*)(&string_val);

    } else if (columnType == "INT") {
        int_val = atoi(value.c_str());
        cout << "vfd"<<endl;
        val = (void *) (&int_val);

    } else if (columnType == "DOUBLE") {
        double_val = atof(value.c_str());
        val = (void*) (&double_val);

    } else if (columnType== "BOOL") {
        bool_val  = value == "true";
        val = (void*) (&bool_val);
    } else {
            cout << "error" << endl;
        return "Error!";
    }

    const void* value1[1] = {val};
    const char* col_name[1] = {columnName.c_str()};


    query* select_query = query_make(SELECT, table,col_name,value1, -1);



    char* res1 = "";
    res1 = query_execute(select_query, true, res1);
    if (res1) {
        std::string res(res1);
        return !res.empty() ? res : "empty";
    } else return "Something went very wrong";
}


std::string MyStubServer::insert__(const Json::Value &paramsList, const std::string &tableName){
    if (!paramsList.isArray()) throw JsonRpcException(-1, "No list of arguments provided");
    if (tableName.empty()) throw JsonRpcException(-1, "Table name was empty");

    struct table* table = table_get(tableName.c_str(), this -> db);

    row* row_one = row_create(table);
    int int_val;
    double double_val;
    bool bool_val;
    string string_val;
    for (int i = 0; i <  paramsList.size() / 3; i++){
        if (paramsList[i*3].asString() == "STR") {
//            cout << "упал здесь 1" <<endl;
            string_val = paramsList[i*3 + 2].asCString();
            attribute_add(row_one,paramsList[i*3 + 1].asCString(),VARCHAR ,&string_val);

        } else if (paramsList[i*3].asString() == "INT") {

            int_val = paramsList[i*3 + 2].asInt();
            attribute_add(row_one,paramsList[i*3 + 1].asCString(),INTEGER ,&int_val);
        } else if (paramsList[i*3].asString() == "DOUBLE") {

            double_val = paramsList[i*3 + 2].asDouble();
            attribute_add(row_one,paramsList[i*3 + 1].asCString(),DOUBLE ,&double_val);
        } else if (paramsList[i*3].asString() == "BOOL") {

            bool_val = paramsList[i*3 + 2].asBool();
            attribute_add(row_one,paramsList[i*3 + 1].asCString(),BOOLEAN ,&bool_val);
        } else {

            cout << paramsList[i*2].asString()<<endl;
            return "Error!";
        }

    }
    row_insert(row_one);
    row_close(row_one);

    return std::string ("inserted into ") + std::string (tableName.c_str());
}

std::string MyStubServer::create__(const Json::Value& paramsList, const std::string& tableName) {
    std::cout << "vfd" << std::endl;
    if (!paramsList.isArray()) throw JsonRpcException(-1, "No list of arguments provided");
    if (tableName.empty()) throw JsonRpcException(-1, "Table name was empty");

    struct schema* schema_one = schema_create();
    for (int i = 0; i < paramsList.size() / 2; i++){
        if (paramsList[i*2].asString() == "STR") {
            schema_one = schema_add_column_varchar(schema_one,paramsList[i*2 + 1].asCString(), VARCHAR, 40);

        } else if (paramsList[i*2].asString() == "INT") {
            schema_one = schema_add_column(schema_one, paramsList[i*2 + 1].asCString(), INTEGER);
        } else if (paramsList[i*2].asString() == "DOUBLE") {
            schema_one = schema_add_column(schema_one, paramsList[i*2 + 1].asCString(), DOUBLE);
        } else if (paramsList[i*2].asString() == "BOOL") {
            schema_one = schema_add_column(schema_one, paramsList[i*2 + 1].asCString(), BOOLEAN);
        } else {
            cout << paramsList[i*2].asString()<<endl;
            return "Error!";
        }

    }

    table* table = table_create(schema_one, tableName.c_str(), db);
    return std::string("created ") + std::string(tableName.c_str());
}

std::string
MyStubServer::join__(const std::string &firstCName, const std::string &firstTName, const std::string &secondCName, const std::string &secondTName) {
    if (firstCName.empty()) throw JsonRpcException(-1, "First column name was empty");
    if (firstTName.empty()) throw JsonRpcException(-1, "Firts table name was empty");
    if (secondCName.empty()) throw JsonRpcException(-1, "Second column name was empty");
    if (secondTName.empty()) throw JsonRpcException(-1, "Second table name was empty");

    table* table = table_get(firstCName.c_str(), db);
    struct table* table2 = table_get(secondCName.c_str(), db);
    struct query_join* select_query_join = query_join_make(table, table2, firstTName.c_str(), secondCName.c_str());
    char* res = "";
    res = query_join_execute(select_query_join, res);
    if (res){
        return res;
    }else return "Something went very wrong";

}

std::string MyStubServer::update__(const Json::Value &paramsList, const std::string &tableName) {
    if (!paramsList.isArray()) throw JsonRpcException(-1, "No list of arguments provided");
    if (tableName.empty()) throw JsonRpcException(-1, "Table name was empty");

    table* table = table_get(tableName.c_str(), this ->db);




    const char* first_column_name = paramsList[1].asCString();

    const void* first_column_val;

    if (paramsList[0].asString() == "STR"){
        first_column_val = (void*) paramsList[2].asCString();
    } else if (paramsList[0].asString() == "INT") {
        int32_t val = paramsList[2].asInt();
        first_column_val = (void*) (&val);
    } else if (paramsList[0].asString() == "DOUBLE") {
        double val = paramsList[2].asDouble();
        first_column_val = (void*) (&val);
    } else if (paramsList[0].asString() == "BOOL") {
        bool val = paramsList[2].asBool();
        first_column_val = (void*) (&val);
    }   else {
        return "Error!";
    }

    const char* second_column_name = paramsList[4].asCString();
    const void* second_column_val;

    if (paramsList[3].asString() == "STR"){
        second_column_val = (void*) paramsList[5].asCString();
    } else if (paramsList[3].asString() == "INT") {
        int32_t val = paramsList[5].asInt();
        second_column_val = (void*) (&val);
    } else if (paramsList[3].asString() == "DOUBLE"){
        double  val = paramsList[5].asDouble();
        second_column_val = (void*) (&val);
    } else if (paramsList[3].asString() == "BOOL") {
        bool val = paramsList[5].asBool();
        second_column_val = (void*) (&val);
    } else {
        return "Error!";
    }


    const char* column_name[2] = {first_column_name,second_column_name};


    const void* query_vals[2] = {first_column_val,second_column_val};

    query* query = query_make(UPDATE, table, column_name, query_vals, -1);

    char* res1 = "";
    res1 = query_execute(query, true, res1);

    if (res1) {
        std::string res(res1);
        return !res.empty() ? res : "empty";
    } else return "Something went very wrong";
}


std::string MyStubServer::delete__(const std::string &columnName, const std::string &columnType, const std::string &tableName, const std::string &value) {
    if (tableName.empty()) throw JsonRpcException(-1, "Table name was empty");
    if (columnName.empty()) throw JsonRpcException(-1, "Column name was empty");
    if (columnType.empty()) throw JsonRpcException(-1, "Column type was empty");
    if (value.empty()) throw JsonRpcException(-1, "Value was empty");


    int int_val;
    double double_val;
    bool bool_val;
    string string_val;
    void* val;
    if (columnType == "STR") {
        string_val =value.c_str();
        val = (void*)(&string_val);

    } else if (columnType == "INT") {
        int_val = atoi(value.c_str());
        cout << "vfd"<<endl;
        val = (void *) (&int_val);

    } else if (columnType == "DOUBLE") {
        double_val = atof(value.c_str());
        val = (void*) (&double_val);

    } else if (columnType== "BOOL") {
        bool_val  = value == "true";
        val = (void*) (&bool_val);
    } else {
        cout << "error" << endl;
        return "Error!";
    }

    const void* value1[1] = {val};
    const char* col_name[1] = {columnName.c_str()};

    table* table = table_get(tableName.c_str(), this ->db);
    query* query = query_make(DELETE, table, col_name, value1, -1);



    char* res1 = "";
    res1 = query_execute(query, true, res1);
    if (res1) {
        std::string res(res1);
        return !res.empty() ? res : "empty";
    } else return "Something went very wrong";

}
int main() {

    int port = 9898;

    HttpServer httpserver(port);
    MyStubServer s(httpserver,
                   JSONRPC_SERVER_V2);
    s.StartListening();

    s.open__();



    cout << "Hit enter to stop the server" << endl;
    getchar();
    s.close__();
    s.StopListening();
}