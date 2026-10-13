/* func_ov122_022a1738 @ 0x022a1738, 0x2c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229efe8(void *obj, int param);
extern void func_ov002_0220ac4c(void *ptr);
extern void func_ov002_0220ac7c(void *ptr);

void func_ov122_022a1738(void *obj)
{
    if (func_ov122_0229efe8(obj, 0x10)) {
        func_ov002_0220ac4c((char *) obj + 0x4698);
    } else {
        func_ov002_0220ac7c((char *) obj + 0x4698);
    }
}
