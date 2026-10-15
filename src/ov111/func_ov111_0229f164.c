/* func_ov111_0229f164 @ 0x0229f164, 0x74 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229efd8(void *ptr, int a);
extern void func_ov002_0220a05c(void *addr, int a, int b, int c, int d);
extern int func_ov095_02299b7c(void *ptr);
extern int func_ov095_02299b38(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov111_0229f164(void *p)
{
    if (func_ov111_0229efd8(p, 2)) {
        func_ov002_0220a05c((char *) p + 0x3d38, *(unsigned char *) ((char *) p + 0xa1) + 0x18, 0x28, 3, 1);
        *(unsigned char *) ((char *) p + 0x98) = 9;
    } else {
        int res1 = func_ov095_02299b7c((char *) p + 0xac);
        int res2 = func_ov095_02299b38((char *) p + 0xac);
        func_ov002_0220a05c((char *) p + 0x3d38, res1, res2, 2, 1);
        *(unsigned char *) ((char *) p + 0x98) = 3;
    }
    func_ov002_02208098((void *) (p), 4);
}
