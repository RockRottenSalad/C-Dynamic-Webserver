
#include "utils/regex_handler.h"

regex_container_t regex_container;

void regex_init(void)
{
    assert(regcomp(&regex_container.parse_get, "GET [^ ]+ HTTP/1.1", REG_NEWLINE|REG_EXTENDED) == 0);
    assert(regcomp(&regex_container.parse_dynamic, "<dynamic func=[^\\(]+", REG_NEWLINE|REG_EXTENDED) == 0);
    assert(regcomp(&regex_container.parse_arg, "\\([^\\)]+", REG_NEWLINE|REG_EXTENDED) == 0);
}

void regex_delete(void)
{
    regfree(&regex_container.parse_get);
    regfree(&regex_container.parse_dynamic);
    regfree(&regex_container.parse_arg);
}

int regex_match(regex_t* reg, const char* str, char** dest)
{
    return regex_nmatch(reg, str, dest, REQ_MAX_LEN);
}

int regex_nmatch(regex_t* reg, const char* str, char** dest, int n)
{
    regmatch_t match[1];
    int ret, match_length;

    ret = regexec(reg, str, 1, match, 0);
    if(ret != 0)
        return ret;

    match_length = match[0].rm_eo - match[0].rm_so;
    if(match_length > n)
        return -1;

    snprintf(*dest, match_length+1, "%s", str + match[0].rm_so);

    return 0;
}

