/*****************************************
 * Proj: Cache Simulator
 * File: random_cache.cpp 
 * Auth: Dimpi Singh */

#include "header.hpp"


/****************************************
 * Func: Constructor
 * Desc: Constructs random cache.  */
Random_Cache::Random_Cache(int c) {
    capacity = c;
    size = 0;
    srand(time(NULL));
}

/*****************************************
 * Func: put()
 * Desc: Organizes item at tag inside Cache
 *       If already in Cache: HIT
 *       If not in Cache and cache is full: EVICT
 *       If not in Cache: MISS
 *       Some tricky stuff to do it in O(1).
 */
enum RESULT Random_Cache::put(long long tag, bool write_back, bool store) {
    if (where.count(tag) == 1) {
        if (write_back && store) nums[where[tag]].second = true;
        return HIT;
    }
    bool evict = false, dirty = false;
    if (capacity == size) {
        int random_index = rand() % capacity;
        dirty = nums[random_index].second;
        swap(nums[capacity-1], nums[random_index]);
        where.erase(nums[capacity-1].first);
        nums.pop_back();
        if (random_index != capacity-1)
            where[nums[random_index].first] = random_index;
        size--;
        evict = true;
    }
    nums.push_back({tag, (write_back && store)});
    size++;
    where[tag] = size-1;
    return (evict ? (dirty ? DIRTYEVICTION : EVICTION) : MISS);
}



/*****************************************
 * Func: get()
 * Desc: Returns HIT if in cache, MISS if not
 */
enum RESULT Random_Cache::get(long long tag, bool write_back, bool store) {
    enum RESULT result = (this->where.count(tag) == 1) ? HIT : MISS;
    if (result == HIT && write_back == true)
        nums[where[tag]].second = store;
    return result;
}



