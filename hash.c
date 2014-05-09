#include "hash.h"

struct hash
{
    unsigned int buckets;
    hashfunc_t hash_func;
    hash_node_t **nodes;
};

hash_node_t **hash_get_bucket(hash_t *hash, void *key)
{
    unsigned int buck = hash->hash_func(hash->buckets, key);
    if (buck >= hash->buckets)
	{
		fprintf(stderr, "bad bucket lookup\n");
		exit(EXIT_FAILURE);
	}
    return &(hash->nodes[buck]);
}

hash_t* hash_alloc(unsigned int buckets, hashfunc_t hash_func)
{
    hash_t *myhash = (hash_t*)malloc(sizeof(hash_t));
    //assert(myhash != NULL);
    myhash->buckets = buckets;
    myhash->hash_func = hash_func;
    myhash->nodes = (hash_node_t **)malloc(buckets*sizeof(hash_node_t *));
    memset(myhash->nodes, 0, buckets*sizeof(hash_node_t *));
    return myhash;
}

void hash_add_entry(hash_t *hash, void *key, unsigned int key_size,
    void *value, unsigned int value_size)
{
    if(hash_lookup_entry(hash, key, key_size))
    {
		fprintf(stderr, "duplicate hash key\n");
		return;
	}

    hash_node_t *node = (hash_node_t *)malloc(sizeof(hash_node_t));
    memset(node, 0, sizeof(hash_node_t));
    node->prev = NULL;
    node->next = NULL;
    node->key = (void *)malloc(key_size);
    node->value = (void *)malloc(value_size);
    memcpy(node->key, key, key_size);
    memcpy(node->value, value, value_size);
    hash_node_t **bucket = hash_get_bucket(hash, key);
    if(*bucket == NULL)
    {
        *bucket = node;
    }else
    {
        node->next = *bucket;
        (*bucket)->prev = node;
        *bucket = node;
    }
}
void hash_free_entry(hash_t *hash, void *key, unsigned int key_size)
{
    hash_node_t *node = hash_get_node_by_key(hash, key, key_size);
    if(node == NULL)
        return;

    free(node->key);
    free(node->value);
    if(node->prev)
        node->prev->next = node->next;
    else
    {
        hash_node_t **bucket = hash_get_bucket(hash, key);
        *bucket = node->next;
    }

    if(node->next)
        node->next->prev = node->prev;

    free(node);
}

hash_node_t* hash_get_node_by_key(hash_t *hash, void *key, unsigned int key_size)
{
   hash_node_t **bucket = hash_get_bucket(hash, key);
    if(*bucket == NULL)
        return NULL;

    hash_node_t* node = *bucket;
    while(node != NULL && memcmp(node->key, key, key_size) != 0)
        node = node->next;
    return node;
}
void *hash_lookup_entry(hash_t *hash, void *key, unsigned int key_size)
{
    hash_node_t *node = hash_get_node_by_key(hash, key, key_size);
    if(node == NULL)
        return NULL;

    return node->value;
}
