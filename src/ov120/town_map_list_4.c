/* town_map_list_4: 2 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229aa80 @ 0x0229aa80, 0x4c bytes, Thumb
 * func_ov120_0229aa30 @ 0x0229aa30, 0x50 bytes, Thumb
 */

extern unsigned char func_ov120_0229b14c(void *);
extern void func_ov120_0229abec(void *, int);
extern int _s32_div_f(int, int);
extern unsigned char data_021f6c54;
extern unsigned short data_021fbe40;

void func_ov120_0229aa80(void *r0)
{
    int r5;
    unsigned char r2;
    unsigned char r1;
    unsigned char r0b;
    int r0i;

    r2 = *(unsigned char *) ((char *) r0 + 0xa6);
    r1 = data_021f6c54;
    r0b = *(unsigned char *) ((char *) r0 + 0xa5);
    r5 = r2 + (r1 - r0b);
    if (r5 < 0) {
        r5 = 0;
    } else if (r5 > 0x58) {
        r5 = 0x58;
    }
    r0i = func_ov120_0229b14c(r0);
    r5 = r0i * r5;
    r0i = r5;
    r1 = 0x58;
    r0i = _s32_div_f(r0i, r1);
    func_ov120_0229abec(r0, r0i);
}

void func_ov120_0229aa30(void *p)
{
    int field;
    int upper;

    field = *(unsigned short *) ((char *) p + 0x9a);
    if (data_021fbe40 & 0x40) {
        field -= 4;
    } else if (data_021fbe40 & 0x80) {
        field += 4;
    }
    upper = (int) func_ov120_0229b14c(p);
    if (field < 0) {
        field = 0;
    } else if (field > upper) {
        field = upper;
    }
    func_ov120_0229abec(p, field);
}
