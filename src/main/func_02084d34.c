/* func_02084d34 @ 0x02084d34, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short id;
    unsigned char pad_02[18];
} Entry;

Entry *func_02084d34(Entry *key, Entry *list, int count)
{
    Entry *p;
    int i;

    p = list;
    i = 0;
    while (i < count) {
        if (key->id == p->id) {
            return p;
        }
        p++;
        i++;
    }
    return 0;
}
