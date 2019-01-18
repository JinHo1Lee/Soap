
CXX=c++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CXX) $(OPT) -c $<

all: main 

OPT=-g -I./

main: stdsoap2.o soapC.o soapServer.o server

stdsoap2.o: stdsoap2.cpp stdsoap2.h
	$(CXX) $(OPT) -DWITH_XMLNS -c stdsoap2.cpp

soapC.o: soapC.cpp soapH.h
	$(CXX) $(OPT) -c soapC.cpp

soapServer.o: soapServer.cpp soapH.h soapStub.h
	$(CXX) $(OPT) -c soapServer.cpp

server : server.o
	$(CXX) server.o soapC.o soapServer.o stdsoap2.o -o server

clean :
	rm -f server *.o
