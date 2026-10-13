/* func_ov122_022a1c24 @ 0x022a1c24, 0x44 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229efe8(void *arg0, int arg1);
extern void func_ov002_02207f04(void *arg0, int arg1, int arg2, int arg3, int arg4);
extern void func_ov002_02207e80(void *arg0, int arg1, int arg2, int arg3);
extern void func_ov122_0229f454(void *arg0, int arg1);

void func_ov122_022a1c24(void *arg0)
{
    if (func_ov122_0229efe8(arg0, 0x20) == 0) {
        func_ov002_02207f04(arg0, 8, 0, 0, 0x30);
        func_ov002_02207e80(arg0, 6, 0, 0);
        ((unsigned char *) arg0)[0x8c] = 5;
    } else {
        func_ov122_0229f454(arg0, 0);
    }
}
