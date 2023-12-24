
#include "config/config_loader.h"

page_t* pages_hashmap[HASHMAP_SIZE];

void page_hashmap_init(void)
{
    for(int i = 0; i < HASHMAP_SIZE; i++)
        pages_hashmap[i] = NULL;

    int pages_len = sizeof(pages) / sizeof(pages[0]);
    int urls = 0, index = 0;

    for(int i = 0; i < pages_len; i++)
    {
        urls = page_count_urls(&pages[i]);
        pages[i].dyn_wrap = NULL;

        for(int n = 0; n < urls; n++)
        {
            index = hash_page(pages[i].URL[n]);
            assert(pages_hashmap[index] == NULL);
            pages_hashmap[index] = &pages[i];
        }

        if(pages[i].HTML)
        {
            assert(file_exists(pages[i].HTML) == true);
            if(pages[i].DYNAMIC)
                pages[i].dyn_wrap = dynamic_parse(pages[i].HTML);
        }
         if(pages[i].CSS)
             assert(file_exists(pages[i].CSS) == true);

    }
}

int page_count_urls(page_t* restrict page)
{
    int urls_max_len = 0, urls_len = 0;

    urls_max_len = sizeof(page->URL) / sizeof(page->URL[0]);

    for(int i = 0; i < urls_max_len; i++)
        if(page->URL[i][0])
            urls_len++;

    return urls_len;
}

int hash_page(const char* URL)
{
    int index = 0, len = strlen(URL);
    for(int i = 0; i < len; i++)
    {
        index += URL[i];
        index *= URL[i];
    }

    index *= index;

    return index % HASHMAP_SIZE;
}

void config_cleanup(void)
{
    for(int i = 0; i < HASHMAP_SIZE; i++)
        if(pages_hashmap[i] != NULL)
        {
            /*
            for(int n = 0; n < MAX_DYNAMIC_FUNCTIONS; n++)
            {
                if(&pages_hashmap[i]->dyn_wrap[n] != NULL && pages_hashmap[i]->dyn_wrap[n].arg != NULL)
                {
                    free(pages_hashmap[i]->dyn_wrap[n].arg);
                }

            }
            */
            free(pages_hashmap[i]->dyn_wrap);
        }
}
