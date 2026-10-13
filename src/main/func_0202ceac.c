/* func_0202ceac @ 0x0202ceac, 0x46 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a478(int value);

struct Work {
    unsigned char *entries;
    unsigned char count;
};

int func_0202ceac(int key, struct Work *p)
{
    unsigned char *e = p->entries;
    int count = 0;
    int i;

    if (e != 0 && p->count != 0) {
        for (i = 0; i < p->count; i++) {
            if (e[0] < 0x38 && e[2] != 0) {
                if (func_0209a478(e[2]) == key) {
                    count++;
                }
            }
            e += 3;
        }
    }

    return count;
}
