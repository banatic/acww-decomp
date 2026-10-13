/* func_ov111_0229fff4 @ 0x0229fff4, 0x28 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229bf48(void *);
extern int func_ov002_0220b8ac(void *, int);
extern void func_ov111_022a01bc(void *);

void func_ov111_0229fff4(void *obj)
{
    func_ov095_0229bf48((char *) obj + 0xac);
    if (func_ov002_0220b8ac((char *) obj + 0x3d9c, 1) != 0) {
        func_ov111_022a01bc(obj);
    }
}
