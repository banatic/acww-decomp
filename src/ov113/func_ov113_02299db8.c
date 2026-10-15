/* func_ov113_02299db8 @ 0x02299db8, 0x38 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070a98(void *receiver, int p2, int p3, int p4, unsigned char p5, unsigned char p6, int flag);
extern void func_02070a04(void *, int, int);

void func_ov113_02299db8(void *p, int index, void *a2, void *a3, int arg5, int arg6)
{
    void *obj = (void *) ((char *) p + 0x26e8 + index * 0x6c);
    func_02070a98(obj, 2, (int) a2, (int) a3, 15, 10, arg6);
    func_02070a04(obj, arg5, 0);
}
