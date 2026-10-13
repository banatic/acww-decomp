/* func_020b3ed4 @ 0x020b3ed4, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    signed char c;
    unsigned char pad_01[3];
} Entry;

extern int func_020b3f2c(Entry *);
extern int func_020b3f08(Entry *);

int func_020b3ed4(Entry *arg)
{
    int i, j, count, offset;
    Entry *p;

    i = func_020b3f2c(arg);
    j = func_020b3f08(arg);
    p = arg + i;
    p += j;
    count = 0;
    offset = count;
    while (p[offset].c == 'S') {
        p++;
        count++;
    }
    return count;
}
