/* func_ov112_022a00ac @ 0x022a00ac, 0x98 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229fe70(void *p, int flag);
extern int func_ov112_0229f900(void *p);
extern void func_ov112_0229f89c(void *p);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov095_0229b394(void *p);
extern int func_02051c8c_unk(void *p, int len);
extern int func_ov112_022a029c(void *p, unsigned short val, int j);
extern void func_ov112_0229ff50(void *receiver);
extern void func_ov095_022999e8(void *receiver);
extern void func_ov112_0229fd20(void *p);
extern void func_ov112_0229f668(void *p);
extern void func_ov095_0229b388(void *p);

void func_ov112_022a00ac(void *p)
{
    int count;
    int i, j;

    if (func_ov112_0229fe70(p, 0x200) == 0) {
        return;
    }

    if (func_ov112_0229f900(p) != 0) {
        func_ov112_0229f89c(p);
    }

    func_ov095_0229b3ec((char *) p + 0x384);
    func_ov095_0229b394((char *) p + 0x384);

    count = func_02051c8c_unk((char *) p + 0x184, 0x60);

    for (i = 0, j = i; i < count; i++) {
        if (func_ov112_022a029c(p, *(unsigned short *) ((char *) p + i * 2 + 0x184), j) == 0) {
            if (i == 0) {
                func_ov112_0229ff50((void *) p);
            }
            i = count;
        }
    }

    func_ov095_022999e8((char *) p + 0x384);
    func_ov112_0229fd20(p);
    func_ov112_0229f668(p);
    func_ov095_0229b388((char *) p + 0x384);
}
