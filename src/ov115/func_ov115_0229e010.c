/* func_ov115_0229e010 @ 0x0229e010, 0x64 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov114_0229d244(void *);
extern void func_ov114_0229d220(void *);
extern void func_ov002_02208098(void *, int);
extern void func_ov114_0229d52c(void *, int);
extern int func_ov115_0229dedc(void *);
extern int func_ov115_0229ded0(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov115_0229e010(void *obj)
{
    int a, b;
    if (data_021fbe40 & 1) {
        func_ov114_0229d244((char *) obj + 0xf8);
    } else {
        func_ov114_0229d220((char *) obj + 0xf8);
        func_ov002_02208098(obj, 8);
    }
    func_ov114_0229d52c((char *) obj + 0xf8, *(int *) ((char *) obj + 0x1424));
    a = func_ov115_0229dedc(obj);
    b = func_ov115_0229ded0(obj);
    func_ov002_0220a0b4((char *) obj + 0x94, a, b);
}
