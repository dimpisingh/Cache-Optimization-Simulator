/*****************************************
 * Proj: Cache Simulator
 * File: simulator.cpp 
 * Auth: Dimpi Singh */

#include "header.hpp"

/*****************************************
 * Func: Simulator()
 * Desc: Populates simulator class with
 *       input from file. Then, sets up
 *       simulator instance. */
Simulator::Simulator(fstream& config) {
    config >> num_caches;
    config >> main_mem_access_cycles;
    total_writes = total_reads = total_cycles = 0;
    if (!cache.setup(config, main_mem_access_cycles)) {
        cerr << "simulator: constructor: Bad config file input" << endl;
        exit(0);
    }
    return;
}


/***************************************
 * Func: create_output()
 * Desc: Creates output fstream object for
 *       output. */
bool Simulator::create_output(string const& filename) {
    output.open(filename, fstream::out);
    return output.is_open();
}


/***************************************
 * Func: execute()
 * Desc: Executes instruction that is
 *       inputted. Returns true if success. */
bool Simulator::execute(string const& line, char const& instr, string const& addr) {
    long long size, address, comma_pos = addr.find(',');
    if (comma_pos != string::npos) {
        string just_addr = addr.substr(0, comma_pos);
        address = stoull(just_addr, nullptr, 16);
    } else return false;

    output << line << " ";
    string out;
    if (instr == 'S') out = cache.store(address);
    else if (instr == 'L') out = cache.load(address);
    else if (instr == 'M') out = cache.modify(address, line);
    output << out << endl;
    return true;
}

/***************************************
 * Func: complete()
 * Desc: Completes the program by printing 
 *       simulation summary. */
void Simulator::complete() {
    output << "L1"  << " Cache: ";
    output << "Hits:" << cache.get_hits() << " ";
    output << "Misses:" << cache.get_misses() << " ";
    output << "Evictions:" << cache.get_evictions() << " ";
    output << endl;
    output << "Cycles:" << cache.get_total_cycles() << " ";
    output << "Reads:" << cache.get_total_reads() << " " ;
    output << "Writes:" << cache.get_total_writes() << " ";
    output << endl;
}

   
