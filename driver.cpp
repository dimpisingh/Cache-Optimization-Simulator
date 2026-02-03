/*****************************************
 * Proj: Cache Simulator
 * File: driver.cpp
 * Auth: Dimpi Singh */

#include "header.hpp"

/*****************************************
 * Func: main
 * In: Configuration file path, trace_file path
 * Out: Output file where name = "trace_file.out" */
int main(int argc, char** argv) {
    // Input check
    if (argc != 3) {
        cerr << "driver, main: Not the correct number of arguments" << endl;    
        return 0;
    }

    fstream config, trace;
    config.open(argv[1]);
    trace.open(argv[2]);

    if (config.is_open() && trace.is_open()) {
        // Files exist and are open!
        Simulator simulator(config);

        string output_file_name(argv[2]);
        output_file_name += ".out";
        if (!simulator.create_output(output_file_name)) {
            cerr << "driver, main: Simulator output creation failed" << endl;
            return 0;
        }

        char instruction;
        string address, line;
        while (true) {
            getline(trace, line);
            if (trace.fail()) break;
            for (int i = 0; i < line.length(); i++)
                if (line[i] != ' ') {
                    instruction = line[i];
                    address = line.substr(i+2); 
                    break;
                }
            // If comment or instruction load, no operation on cache
            if (instruction == '=' || instruction == 'I') continue;
            if (!simulator.execute(line, instruction, address)) {
                cerr << "driver, main: Instruction failed: " << instruction << ", " << address << endl;
                return 0;
            }
        }
        simulator.complete();
    } else {
        cerr << "driver, main: Could not open input file(s)" << endl;
    }
    return 0;
}
