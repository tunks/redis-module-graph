#ifndef GROUP_CACHE_H_
#define GROUP_CACHE_H_

#include "../util/khash.h"
#include "group.h"
#include "../rmutil/vector.h"

// Shorthand way to get the key from hashtable or defVal if not found
#define kh_get_val(kname, hash, key, defVal) ({khiter_t k=kh_get(kname, hash, key);(k!=kh_end(hash)?kh_val(hash, k):defVal);})

// shorthand way to set value in hash with single line command.  Returns value
// returns 0=replaced existing item, 1=bucket empty (new key), 2-adding element previously deleted
#define kh_set(kname, hash, key, val) ({int ret; khiter_t k = kh_put(kname, hash, key, &ret); kh_value(hash, k) = val; ret;})

static const char* khID = "group_cache";

// Returns an iterator to scan hashtable
khiter_t CacheGroupIter();

// Advance iterator and returns key & value in current position.
int CacheGroupIterNext(khiter_t* iter, char** key, Group** group);

KHASH_MAP_INIT_STR(khID, Group*) // setup khash to handle string key with Group* payload

int CacheGroupAdd(const char* key, const Group* group);

void CacheGroupRemove(const char* key);

// Retrives a group,
// Sets group to NULL if key is missing.
void CacheGroupGet(const char* key, Group** group);

void CacheGroupClear();

#endif