/*****************************************
 * Proj: Cache Simulator
 * File: lru_cache.hpp 
 * Auth: Dimpi Singh */

#include "./header.hpp"


/*****************************************
 * Func: Constructor
 * Desc: Sets up LRU_Cache size and capacity
 */
LRU_Cache::LRU_Cache(int c) {
    this->capacity = c;
    size = 0;
    head = tail = NULL;
}


/*****************************************
 * Func: get()
 * Desc: Returns HIT if in cache, MISS if not
 */
enum RESULT LRU_Cache::get(long long tag, bool write_back, bool store_bit) {
    if (this->where.find(tag) != this->where.end()) {
        this->put(tag, write_back, store_bit);
        return HIT;
    } else return MISS;
}

/*****************************************
 * Func: put()
 * Desc: Organizes item at tag inside Cache
 *       If already in Cache: HIT
 *       If not in Cache and cache is full: EVICT
 *       If not in Cache: MISS
 */
enum RESULT LRU_Cache::put(long long tag, bool write_back, bool store_bit) {
    bool evict = false, hit = false, dirty = false;
    if (this->where.find(tag) != this->where.end()) {
        Node* removed = where[tag];
        if (removed->prev)
            removed->prev->next = removed->next;
        else
            head = removed->next;
        if (removed->next)
            removed->next->prev = removed->prev;
        else
            tail = removed->prev;
        where.erase(tag);
        delete removed;
        size--;
        hit = true;
    } else if (size == capacity) {
        Node* new_head = head->next;
        if (new_head) new_head->prev = NULL;
        if (head == tail) tail = NULL;
        where.erase(head->tag);
        dirty = head->dirty;
        delete head;
        head = new_head;
        size--;
        evict = true;
    }
    Node* add = new Node(NULL, NULL, tag, write_back && (hit || store_bit));
    where[tag] = add;
    if (tail) {
        tail->next = add;
        add->prev = tail;
        tail = add;
    } else {
        tail = add;
        head = add;
    }
    this->size++;
    if (hit) return HIT;
    if (evict && dirty) return DIRTYEVICTION;
    if (evict) return EVICTION;
    return MISS;
}
