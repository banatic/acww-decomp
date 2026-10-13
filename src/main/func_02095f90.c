/* func_02095f90 @ 0x02095f90, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);

int func_02095f90(void)
{
    void *p;
    int v;

    p = func_02096718(4);
    if (p != 0) {
        v = *(int *) ((char *) p + 0x7f0);
        if (v != 0) {
            return v;
        }
        return (*(unsigned int *) ((char *) p + 8) >> 22) & 0xff;
    } else {
        return 0x93;
    }
}
