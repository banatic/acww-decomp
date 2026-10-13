/* func_ov116_0229e010 @ 0x0229e010, 0x64 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov114_0229d244(void *);
extern void func_ov114_0229d220(void *);
extern void func_ov002_02208098(void *, int);
extern void func_ov114_0229d52c(void *, int);
extern void func_ov002_0220a0b4(void *, void *, void *);
extern void *func_ov116_0229dedc(void *);
extern void *func_ov116_0229ded0(void *);

void func_ov116_0229e010(void *param)
{
    void *r5;
    void *r2;

    if (data_021fbe40 & 1) {
        func_ov114_0229d244((char *) param + 0xf8);
    } else {
        func_ov114_0229d220((char *) param + 0xf8);
        func_ov002_02208098(param, 8);
    }
    func_ov114_0229d52c((char *) param + 0xf8, *(int *) ((char *) param + 0x1424));
    r5 = func_ov116_0229dedc(param);
    r2 = func_ov116_0229ded0(param);
    param = (char *) param + 0x94;
    func_ov002_0220a0b4(param, r5, r2);
}
