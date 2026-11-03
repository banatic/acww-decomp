/* actor_table_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020829b8 @ 0x020829b8, 0x34 bytes, Thumb
 * func_0208298c @ 0x0208298c, 0x2c bytes, Thumb
 */

extern int func_02082afc(void *base, unsigned short *tag);
extern int func_0207cf74(int);
extern int func_02082b60(int, int);

void *func_020829b8(void *base, unsigned short *tag)
{
    unsigned short val;
    int idx;
    void *result = 0;

    val = *tag;
    if (((val & 0xF000) >> 12) == 0xE) {
        idx = func_02082afc(base, tag);
        if (idx >= 0 && idx < 8) {
            result = *(void **) ((char *) base + (idx << 3));
        }
    }
    return result;
}

int func_0208298c(int r0, int r1)
{
    int r4 = r1;
    int r5 = r0;
    int r6 = 0;

    if (func_0207cf74(r4) != 0) {
        r4 = r5 + (r4 << 3);
        if (func_02082b60(r5, r4) != 0) {
            r6 = *(int *) r4;
        }
    }
    return r6;
}
