/* func_020b2e54 @ 0x020b2e54, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020b2e54 {
    unsigned short id;
} UnkStruct_020b2e54;

extern int func_02037d64(void *, int);
extern UnkStruct_020b2e54 *func_02037e0c(void *, unsigned int, unsigned int, int);

int func_020b2e54(void *p)
{
    int count;
    unsigned int y;
    unsigned int start;
    int zero;
    unsigned int x;
    UnkStruct_020b2e54 *e;
    count = 0;
    if (p != 0) {
        if (func_02037d64(p, 0xe0) != 0 || func_02037d64(p, 0x10) != 0) {
            return 0;
        }
        y = 0;
        zero = 0;
        start = 0;
        for (; y < 0x10; y++) {
            for (x = start; x < 0x10; x++) {
                e = func_02037e0c(p, x, y, zero);
                if (e != 0 && e->id == 0x500a) {
                    count++;
                }
            }
        }
    }
    return count;
}
