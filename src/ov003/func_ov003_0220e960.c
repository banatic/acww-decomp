/* func_ov003_0220e960 @ 0x0220e960, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200faf0(void *p, int a);
extern int func_02056f94(void *ptr);
extern int func_02008258(void *p, int val);
extern int func_0200d4e8(void *p, int a, int b, int c);
extern int func_02073908(void *g, int val);
extern void *data_020ccf94;
extern int func_ov003_0220d268(void *p);

void func_ov003_0220e960(void *p)
{
    func_0200faf0(p, 0x59a);
    if (func_02056f94((char *) p + 0x2d0) != 0) {
        *(int *) ((char *) p + 0x7fc) = func_02008258(p, *(int *) ((char *) p + 0x7f0));
        func_0200d4e8(p, 3, 1, -1);
    }
    if (func_02073908(data_020ccf94, *(int *) ((char *) p + 0x800)) != 0) {
        if (((*(unsigned int *) ((char *) p + 0x2d8) << 4) >> 16) >= 0x1a) {
            func_ov003_0220d268(p);
        }
    }
}
