/* func_ov122_022a1a04 @ 0x022a1a04, 0x52 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229f444(void *ptr);
extern void func_ov002_02207f04(void *ptr, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *ptr, int a, int b, int c);
extern void func_ov002_02208090(void *ptr, int a);

void func_ov122_022a1a04(void *ptr)
{
    if (func_ov122_0229f444(ptr) == 0) {
        func_ov002_02207f04(ptr, 11, 0, 0, 0x30);
        func_ov002_02207e80(ptr, 6, 0, 0);
        func_ov002_02207e80(ptr, 4, 0, 0);
        func_ov002_02207e80(ptr, 3, 0, 0);
        func_ov002_02208090(ptr, 14);
    }
}
