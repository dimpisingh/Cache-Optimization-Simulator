##########################################################
# Proj: Cache Simulator
# File: Makefile
# Auth: Dimpi Singh
##########################################################
COMPILER = g++ --std=c++11

cache_sim: driver.o simulator.o cache.o lru_cache.o random_cache.o
	$(COMPILER) driver.o simulator.o cache.o lru_cache.o random_cache.o -o cache_sim
	rm -f *.o 

driver.o: driver.cpp
	$(COMPILER) -c driver.cpp

simulator.o: simulator.cpp
	$(COMPILER) -c simulator.cpp

cache.o: cache.cpp
	$(COMPILER) -c cache.cpp

lru_cache.o: lru_cache.cpp
	$(COMPILER) -c lru_cache.cpp

random_cache.o: random_cache.cpp
	$(COMPILER) -c random_cache.cpp

clean:
	rm -f *.o cache_simulator 
