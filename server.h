//
// Created by KuPuK on 22.03.2023.
//

#ifndef LLP3_ABTSERVER_H
#define LLP3_ABTSERVER_H
#include <jsonrpccpp/server.h>
class AbstractStubServer : public jsonrpc::AbstractServer<AbstractStubServer> {
public:
    AbstractStubServer(jsonrpc::AbstractServerConnector &conn,jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2): jsonrpc::AbstractServer<AbstractStubServer>(conn, type) {
        this->bindAndAddMethod(jsonrpc::Procedure("create__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "paramsList",jsonrpc::JSON_ARRAY,"tableName",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::create__I);
        this->bindAndAddMethod(jsonrpc::Procedure("insert__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "paramsList",jsonrpc::JSON_ARRAY,"tableName",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::insert__I);

        this->bindAndAddMethod(jsonrpc::Procedure("update__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "paramsList",jsonrpc::JSON_ARRAY,"tableName",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::update__I);

        this->bindAndAddMethod(jsonrpc::Procedure("select__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "columnName",jsonrpc::JSON_STRING,"columnType",jsonrpc::JSON_STRING,"tableName",jsonrpc::JSON_STRING,"value",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::select__I);
        this->bindAndAddMethod(jsonrpc::Procedure("join__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "firstCName",jsonrpc::JSON_STRING,"firstTName",jsonrpc::JSON_STRING,"secondCName",jsonrpc::JSON_STRING,"secondTName",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::join__I);
        this->bindAndAddMethod(jsonrpc::Procedure("delete__", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "columnName",jsonrpc::JSON_STRING,"columnType",jsonrpc::JSON_STRING,"tableName",jsonrpc::JSON_STRING,"value",jsonrpc::JSON_STRING, NULL), &AbstractStubServer::delete__I);
    }
    inline virtual void create__I(const Json::Value &request, Json::Value &response)
    {
        response = this->create__(request["paramsList"], request["tableName"].asString());
    }

    inline virtual void delete__I(const Json::Value &request, Json::Value &response)
    {
        response = this->delete__(request["columnName"].asString(), request["columnType"].asString(), request["tableName"].asString(), request["value"].asString());
    }


    inline virtual void insert__I(const Json::Value &request, Json::Value &response)
    {
        response = this->insert__(request["paramsList"], request["tableName"].asString());
    }
    inline virtual void update__I(const Json::Value &request, Json::Value &response)
    {
        response = this->update__(request["paramsList"], request["tableName"].asString());
    }

    inline virtual void select__I(const Json::Value &request, Json::Value &response)
    {
        response = this->select__(request["columnName"].asString(), request["columnType"].asString(), request["tableName"].asString(), request["value"].asString());
    }
    inline virtual void join__I(const Json::Value &request, Json::Value &response)
    {
        response = this->join__(request["firstCName"].asString(), request["firstTName"].asString(), request["secondCName"].asString(), request["secondTName"].asString());
    }


    virtual std::string create__(const Json::Value& paramsList, const std::string& tableName) = 0;
    virtual std::string insert__(const Json::Value& paramsList, const std::string& tableName) = 0;

    virtual std::string update__(const Json::Value& paramsList, const std::string& tableName) = 0;
    virtual std::string select__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value) = 0;

    virtual std::string join__(const std::string& firstCName, const std::string& firstTName, const std::string& secondCName, const std::string& secondTName) = 0;
    virtual std::string delete__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value) = 0;
};
#endif //LLP3_ABTSERVER_H
