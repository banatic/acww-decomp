/* func_020b3db8 @ 0x020b3db8, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020b3f2c(char *);
extern unsigned int func_020b3ed4(char *);
extern unsigned int func_020b3f08(char *);

int func_020b3db8(char *a, int *b, int *c, int *d, unsigned int e)
{
    char *base = a + func_020b3f2c(a) * 4;
    char *entry;
    unsigned int index;

    if (e < func_020b3ed4(a)) {
        index = func_020b3f08(a);
        index += e;
        entry = base + index * 4;
        *b = entry[1];
        *c = entry[2];
        *d = entry[3];
        return 1;
    }
    return 0;
}
