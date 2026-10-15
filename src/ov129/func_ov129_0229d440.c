/* func_ov129_0229d440 @ 0x0229d440, 0x50 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207eb4(void *, int, int);
extern int func_ov002_0220abbc(void *);
extern void func_ov002_0220a63c(void *, int);
extern void func_ov002_0220a658(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov129_0229b7dc(void *, int);

void func_ov129_0229d440(unsigned char *obj)
{
    func_ov002_02207eb4(obj, 0, 0);
    func_ov002_0220abbc(obj + 0x1d4);
    if (obj[0xb1] == 2) {
        func_ov002_0220a63c(obj + 0x1d4, 6);
    } else {
        func_ov002_0220a658(obj + 0x1d4, 6);
    }
    func_ov002_02208090(obj, 11);
    func_ov129_0229b7dc(obj, 1);
}
