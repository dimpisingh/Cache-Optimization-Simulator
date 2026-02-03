/*****************************************
 * Proj: Cache Simulator
 * File: header.hpp 
 * Auth: Dimpi Singh */

#pragma once
#include<bits/stdc++.h>

using namespace std;

/****************************************/
enum RESULT { MISS, HIT, EVICTION, DIRTYEVICTION };

/****************************************
 * Node struct used in LRU_Cache
 ****************************************/
struct Node {
    Node* next;
    Node* prev;
    int tag;
    bool dirty;
    Node(Node* n, Node* p, int t, bool d) : next(n), prev(p), tag(t), dirty(d) {};
};

/****************************************
 * Poly_Cache Class
 ****************************************/
class Poly_Cache {
    public:
        virtual enum RESULT get(long long, bool = false, bool = false) = 0;
        virtual enum RESULT put(long long, bool = false, bool = false) = 0;
        Poly_Cache() {};
        Poly_Cache(int c) {};
};

/****************************************
 * LRU_Cache Class
 ****************************************/
class LRU_Cache : public Poly_Cache {
    private:
        Node* head;
        Node* tail;
        int capacity;
        int size;
        unordered_map<long long, Node*> where;

    public:
        LRU_Cache(int); 
        enum RESULT get(long long, bool = false, bool = false);
        enum RESULT put(long long, bool = false, bool = false);
};

/****************************************
 * Random_Cache Class
 ****************************************/
class Random_Cache : public Poly_Cache {
    private:
        unordered_map<long long,int> where;
        vector<pair<long long, int>> nums;
        int capacity;
        int size;

    public:
        Random_Cache(int);
        enum RESULT get(long long, bool = false, bool = false);
        enum RESULT put(long long, bool = false, bool = false);
};


/****************************************
 * Cache Class
 ****************************************/
class Cache {
    private:
        // Config vars
        int num_sets;
        int block_size;
        int associativity;
        bool replacement_policy;
        bool write_policy;
        int access_cycles;
        long long main_mem;

        // Summary vars
        long long hits, misses, evictions;
        long long cycles, reads, writes;

        // O(1) caches by index
        vector<Poly_Cache*> index;

    public:
        bool setup(fstream&, long long);
        string load(long long);
        string modify(long long, string const& command);
        string store(long long);

        // Getters
        long long get_hits();
        long long get_misses();
        long long get_evictions();
        long long get_cycles();
        long long get_total_cycles();
        long long get_total_reads();
        long long get_total_writes();
};


/****************************************
 * Simulator Class
 ****************************************/
class Simulator {
    private:
        int num_caches;
        long long main_mem_access_cycles;
        Cache cache;
        fstream output;
        int total_writes, total_cycles, total_reads;

    public:
        Simulator(fstream&);
        bool execute(string const&, char const&, string const&);
        bool create_output(string const&);
        void complete();
};



