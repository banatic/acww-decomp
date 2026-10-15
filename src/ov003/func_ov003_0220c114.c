/* func_ov003_0220c114 @ 0x0220c114, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203edd0(void *a);
extern int func_020ea990(void *a, void *b);
extern int func_020e8b4c(int a, int b);

int func_ov003_0220c114(void *a, void *b)
{
    func_0203edd0(a);
    if (b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x2333 &&
        func_020e8b4c(0xffff8000, *(short *) ((char *) b + 0x8e)) <= 0x1100) {
        return 1;
    } else {
        return 0;
    }
}
