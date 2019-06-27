#include <cstdio>
#include <cstring>

#define COUNT 602333
#define UNIT_SIZE 41

int n = 0;
unsigned code = 0;
unsigned tmp = 0;
char str[UNIT_SIZE];
char dupmap[COUNT / 8 + 1];
char usemap[COUNT / 8 + 1];
char names[COUNT * UNIT_SIZE];

void strcpy(char *dest, char *src, unsigned len)
{
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}

int strcmp(char *dest, char *src, unsigned len)
{
    for (int i = 0; i < len; i++)
    {
        if (dest[i] != src[i])
        {
            return 0;
        }
    }
    return 1;
}

/*
 * return : 1 - mapbit is 1.
 *          0 - mapbit is 0. set it to 1.
 */
bool mapGetAndSet(char *map, unsigned rank)
{
    char offset = rank % 8;
    char *block = map + rank / 8;
    bool val = (((1 << offset) & (*block)) != 0);
    if (!val)
        (*block) |= (1 << offset);
    return val;
}

unsigned hash(char *str)
{
    unsigned h = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        h = (h << 5) | (h >> 27);
        h += str[i];
    }
    return h % COUNT;
}

/*
 * return : 1 - find a empty position.
 *          0 - find a same name.
 *          Parameter "result" save the position in hashtable;
 */
int probe(char *items, char *item, unsigned hashcode, unsigned size, unsigned unit, unsigned *result)
{
    unsigned offset;
    for (unsigned i = 1;; i++) {
        offset = i * i;
        *result = (hashcode + offset) % size;
        if (mapGetAndSet(usemap, *result)) {
            if (strcmp(items+((*result) * unit), item, unit)) {
                return 0;
            }
        } else {
            return 1;
        }

        *result = ((hashcode - offset) % size + size) % size;
        if (mapGetAndSet(usemap, *result)) {
            if (strcmp(items+((*result) * unit), item, unit)) {
                return 0;
            }
        } else {
            return 1;
        }
    }
}

int main(void)
{
    setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
    setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);

    scanf("%d", &n);
    int msize = COUNT / 8 + 1;
    memset(dupmap, 0x00, msize);
    memset(usemap, 0x00, msize);

    for (int i = 0; i < n; i++)
    {
        memset(str, 0x00, UNIT_SIZE);
        scanf("%s", str);
        code = hash(str);
        char *item = names + code * UNIT_SIZE;
        if (mapGetAndSet(usemap, code))
        {
            if (strcmp(item, str, UNIT_SIZE))
            {
                if (!mapGetAndSet(dupmap, code))
                {
                    printf("%s\n", str);
                }
            }
            else
            {
                int unexist = probe(names, item, code, COUNT, UNIT_SIZE, &tmp);
                if (unexist)
                {
                    strcpy(item, str, UNIT_SIZE);
                }
                else
                {
                    if (!mapGetAndSet(dupmap, tmp))
                    {
                        printf("%s\n", str);
                    }
                }
            }
        }
        else
        {
            strcpy(item, str, UNIT_SIZE);
        }
    }
    return 0;
}