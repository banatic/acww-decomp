/* func_ov120_0229aa30 @ 0x0229aa30, 0x50 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov120_0229b14c(void *p);
extern void func_ov120_0229abec(void *p, int val);

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
    upper = func_ov120_0229b14c(p);
    if (field < 0) {
        field = 0;
    } else if (field > upper) {
        field = upper;
    }
    func_ov120_0229abec(p, field);
}
