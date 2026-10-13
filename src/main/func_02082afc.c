/* func_02082afc @ 0x02082afc, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    int value;
    unsigned short extra;
};

extern int func_0204bcdc(void *a);
extern int func_0204bc64(void *a);

int func_02082afc(struct Entry *a, unsigned short *b)
{
    int i;
    int found = -1;
    for (i = 0; i < 8; i++) {
        struct Entry *e = &a[i];
        int match;
        if (func_0204bcdc(&e->extra) != 0) {
            match = (func_0204bc64(&e->extra) == func_0204bc64(b)) ? 1 : 0;
        } else {
            match = (e->extra == *b) ? 1 : 0;
        }
        if (match) {
            found = i;
            break;
        }
    }
    return found;
}
