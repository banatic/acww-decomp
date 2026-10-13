/* func_02082a44 @ 0x02082a44, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082afc(const void *table, const unsigned short *key);

unsigned int func_02082a44(const void *table, unsigned short id)
{
    unsigned short key = 0xfff1;
    unsigned int result;
    int idx;

    result = 0;
    key = (unsigned short) ((id & 0x0fff) | 0xe000);
    idx = func_02082afc(table, &key);
    if (idx >= 0 && idx < 8) {
        result = ((unsigned int *) ((const char *) table + idx * 8))[0];
    }
    return result;
}
