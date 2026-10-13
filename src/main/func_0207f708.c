/* func_0207f708 @ 0x0207f708, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);

int func_0207f708(unsigned char *base, unsigned short *other)
{
    unsigned short *p;
    int flag1, flag2, count, i;
    int tmp, result;

    p = (unsigned short *) (base + 0x78c);
    count = 0;
    i = count;
    flag1 = count;
    flag2 = count;
    while (i < 10) {
        if (func_0204bcdc(p)) {
            tmp = func_0204bc64(p);
            result = (tmp == func_0204bc64(other)) ? 1 : flag1;
        } else {
            result = (*p == *other) ? 1 : flag2;
        }
        if (result != 0) {
            count++;
        }
        p++;
        i++;
    }
    return count;
}
