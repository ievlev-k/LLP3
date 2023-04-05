//
// Created by KuPuK on 22.03.2023.
//

#ifndef LLP3_SUBCLIENT_H
#define LLP3_SUBCLIENT_H
#include <jsonrpccpp/client.h>
class StubClient : public jsonrpc::Client {
    public:
        StubClient(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}


        std::string create__(const Json::Value& paramsList, const std::string& tableName) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["paramsList"] = paramsList;
            p["tableName"] = tableName;

            Json::Value result = this->CallMethod("create__",p);

            if (result.isString()) {
                std::cout << result.asString() << std::endl;
                return result.asString();
            }
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        std::string delete__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["columnName"] = columnName;
            p["columnType"] = columnType;
            p["tableName"] = tableName;
            p["value"] = value;
            Json::Value result = this->CallMethod("delete__",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }

        std::string update__(const Json::Value& paramsList, const std::string& tableName) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["paramsList"] = paramsList;
            p["tableName"] = tableName;
            Json::Value result = this->CallMethod("update__",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }

        std::string join__(const std::string& firstCName, const std::string& firstTName, const std::string& secondCName, const std::string& secondTName) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["firstCName"] = firstCName;
            p["firstTName"] = firstTName;
            p["secondCName"] = secondCName;
            p["secondTName"] = secondTName;
            Json::Value result = this->CallMethod("join__",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }

        std::string insert__(const Json::Value& paramsList, const std::string& tableName) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["paramsList"] = paramsList;
            p["tableName"] = tableName;
            Json::Value result = this->CallMethod("insert__",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }

        std::string select__(const std::string& columnName, const std::string& columnType, const std::string& tableName, const std::string& value) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["columnName"] = columnName;
            p["columnType"] = columnType;
            p["tableName"] = tableName;
            p["value"] = value;
            Json::Value result = this->CallMethod("select__",p);
            if (result.isString())
                return result.asString();
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }


};
#endif //LLP3_SUBCLIENT_H
