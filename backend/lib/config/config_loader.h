#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include "config/config.h"
#include "utils/file_handler.h"

#include <string.h>
#include <assert.h>

#define HASHMAP_SIZE 150

extern page_t* pages_hashmap[HASHMAP_SIZE];

void page_hashmap_init(void);

int page_count_urls(page_t* page);

int hash_page(const char* URL);

void config_cleanup(void);


#endif
