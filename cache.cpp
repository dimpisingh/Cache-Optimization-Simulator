/*****************************************
 * Proj: Cache Simulator
 * File: cache.cpp 
 * Auth: Dimpi Singh */

#include "header.hpp"

/*****************************************
 * Func: setup()
 * Desc: Sets up cache object by populating
 *       variables and then setting up
 *       cache. Returns true if set up successfully. 
 *       */
bool Cache::setup(fstream& config, long long main_mem) {
    this->main_mem = main_mem;
    config >> num_sets;
    config >> block_size;
    config >> associativity;
    config >> replacement_policy;
    config >> write_policy;
    config >> access_cycles;
    if (cin.fail()) return false;
    cycles = hits = writes = reads = misses = evictions = 0;
    // Make minicaches
    if (replacement_policy == 1)
        for (int j = 0; j < num_sets; j++)
            index.push_back(new LRU_Cache(associativity));
    else
        for (int j = 0; j < num_sets; j++)
            index.push_back(new Random_Cache(associativity));

    return true;
}

/**************************************
 * Func: store()
 * Desc: Performs store operation at the
 *       given address. */
string Cache::store(long long address) {
    long long i = (address / block_size) % num_sets;     
    long long tag = (address / num_sets) / block_size; 
    long long prev = cycles;
    string impact = "";
    
    cycles += access_cycles;
    int result = index[i]->get(tag, (bool) this->write_policy, true);   
    if (result == MISS) {
        impact += "miss ";
        misses++;
        cycles += main_mem;
        cycles += access_cycles;
        result = index[i]->put(tag, (bool) this->write_policy, true);
        if (result == EVICTION || result == DIRTYEVICTION) {
            impact += "eviction ";
            evictions++;
            if (result == DIRTYEVICTION) {
                cycles += main_mem;
                cycles += access_cycles;
            }
        }       
    } else {
        impact = "hit";
        hits++;
    }
    if (write_policy == 0) {
        cycles += main_mem;
    }
    writes++;
    return to_string(cycles - prev) + " L1 " + impact;
}
 
/**************************************
 * Func: load()
 * Desc: Performs load operation at the
 *       given address. */
string Cache::load(long long address) {
    long long i = (address / block_size) % num_sets;
    long long tag = (address / num_sets) / block_size;
    long long prev = cycles;
    string impact = "";
    
    cycles += access_cycles; 
    int result = index[i]->get(tag, false);
    if (result == MISS) {
        impact += "miss ";
        misses++;
        cycles += main_mem;
        result = index[i]->put(tag, false);
        if (result == EVICTION || result == DIRTYEVICTION) {
            impact += "eviction ";
            evictions++;
            if (result == DIRTYEVICTION) {
                cycles += main_mem;
                cycles += access_cycles;
            }
        } 
    } else {
        impact = "hit";
        hits++;
    }
    reads++;
    return to_string(cycles - prev) + " L1 " + impact;
}
 
/**************************************
 * Func: modify()
 * Desc: Performs modify operation at the
 *       given address. */
string Cache::modify(long long address, string const& command) {
    string f = load(address) + "\n";
    string s = command + " " + store(address); 
    return f + s;
}
 
/**************************************
 * GETTERS AND SETTERS */
long long Cache::get_hits() {
    return this->hits;
}

long long Cache::get_misses() {
    return this->misses;
}

long long Cache::get_evictions() {
    return this->evictions;
}

long long Cache::get_total_cycles() {
    return this->cycles;
}

long long Cache::get_total_writes() {
    return this->writes;
}

long long Cache::get_total_reads() {
    return this->reads;
}
