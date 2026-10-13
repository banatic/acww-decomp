/* func_ov004_0224627c @ 0x0224627c, 0xb0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int *func_ov004_022468b0(void);
extern void func_020af854(void *a, int b, unsigned short *c);
extern int func_ov004_02246848(unsigned short *t);

extern unsigned char data_021f395c[];

int func_ov004_0224627c(int *oj, int *oi, int sel)
{
    unsigned short t[2];
    int *base;
    int key;
    int want;
    int seen;
    unsigned int k;
    int i;
    int j;
    int *row;

    base = func_ov004_022468b0();
    t[0] = 0xfff1;
    func_020af854((void *) data_021f395c, sel, &t[0]);
    key = func_ov004_02246848(&t[0]);
    want = 0;
    for (k = 0; k < 0x25; k++) {
        t[1] = 0xfff1;
        func_020af854((void *) data_021f395c, k, &t[1]);
        if (sel == k) {
            break;
        }
        if (key == func_ov004_02246848(&t[1])) {
            want++;
        }
    }
    seen = 0;
    for (i = 0; i < 0x10; i++) {
        for (j = 0, row = base + i * 0x10; j < 0x10; j++) {
            if (key == row[j]) {
                if (seen == want) {
                    *oj = j;
                    *oi = i;
                    return 1;
                }
                seen++;
            }
        }
    }
    *oi = -1;
    *oj = *oi;
    return 0;
}
