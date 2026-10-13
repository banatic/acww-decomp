/* func_ov111_022a0940 @ 0x022a0940, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov111_022a09d8(void *);
extern void func_ov095_0229b324(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov111_0229efd8(void *, int);
extern void func_ov111_022a0910(void *);

void func_ov111_022a0940(void *arg0)
{
    void *r4 = arg0;
    func_ov111_022a09d8(r4);
    func_ov095_0229b324((char *) r4 + 0xac);
    func_ov002_02208090(r4, 1);
    if (func_ov111_0229efd8(r4, 0x20) == 0) {
        func_ov111_022a0910(r4);
    }
}
