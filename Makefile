
.PHONY:
all:
	g++ -o ptp main.cpp msock.cpp

.PHONY:
test:
	g++ -o ptp_test main_test.cpp msock.cpp    
