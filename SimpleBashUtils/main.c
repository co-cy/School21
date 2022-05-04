#include <stdio.h>
#include <string.h>
#include <regex.h>

char* getsubstr(char *s, regmatch_t *pmatch)
{
    static char buf[100] = {0};
    memset(buf, 0, sizeof(buf));
    memcpy(buf, s+pmatch->rm_so, pmatch->rm_eo - pmatch->rm_so);

    return buf;
}

int main(void)
{
    regmatch_t pmatch;
    regex_t reg;
    const char *pattern = "[a-z]+";		// regular expression
    char buf[] = "HELLOsaiYear2012@gmail.com";	// the string to be searched

    regcomp(&reg, pattern, REG_EXTENDED);	// Compile the regular expression
    int offset = 0;
    while(offset < strlen(buf))
    {
        int status = regexec(&reg, buf + offset, 1, &pmatch, 0);
        /* Matches regular expressions. Note that the regexec() function can only match one at a time, and cannot be consecutively matched. Many examples on the Internet do not explain this. */
        if(status == REG_NOMATCH)
            printf("No Match\n");
        else if(pmatch.rm_so != -1)
        {
            printf("Match:\n");
            char *p = getsubstr(buf + offset, &pmatch);
            printf("[%lld, %lld]: %s\n", offset + pmatch.rm_so + 1, offset + pmatch.rm_eo, p);
        }
        offset += pmatch.rm_eo;
    }
    regfree(&reg);		// Release the regular expression

    return 0;
}
