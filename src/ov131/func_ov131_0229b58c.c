/* func_ov131_0229b58c @ 0x0229b58c, 0x28 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *, int kind);
extern unsigned char *func_ov002_022080a0(void *, unsigned char v);
extern void func_ov131_0229b0d0(int r0);
extern void func_ov131_0229b504(void *);

void func_ov131_0229b58c(int arg0)
{
    if (func_ov002_02207f48((void *) arg0, 0) != 0) {
        func_ov002_022080a0((void *) arg0, 2);
        func_ov131_0229b0d0(arg0);
    }
    func_ov131_0229b504((void *) arg0);
}
