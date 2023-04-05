all:
	g++ -std=c++14 server.cpp -ljsoncpp server/*.c -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -o sampleserver
	g++ -std=c++14 client.cpp  client/*.c    -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client -o sampleclient




