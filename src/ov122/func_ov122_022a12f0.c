/* func_ov122_022a12f0 @ 0x022a12f0, 0x3c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov122_0229fc2c(void *);
extern void func_ov002_0220a568(void *);
extern void func_ov122_022a0054(void *);
extern void func_ov122_0229f4e0(void *);

void func_ov122_022a12f0(void *s)
{
    *((char *) s + 0xab) = 0;
    if (data_021fbdd8 == 0) {
        func_ov122_0229fc2c(s);
        func_ov002_0220a568((char *) s + 0x4010);
        func_ov122_022a0054(s);
    } else {
        func_ov122_0229f4e0(s);
    }
}
