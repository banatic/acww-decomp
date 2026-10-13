/* func_ov144_02299ed4 @ 0x02299ed4, 0x70 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov144_02299680(void *ptr, int arg);
extern void func_ov144_02299d3c(void *ptr);
extern int func_020b9bbc(void *dst, void *src, int a, int b, int c);
extern void func_ov144_02299660(void *ptr, int arg);
extern void func_ov144_02299f44(void *ptr);

void func_ov144_02299ed4(void *ptr)
{
    if (func_ov144_02299680(ptr, 8) != 0) {
        func_ov144_02299d3c(ptr);
    }
    if (func_ov144_02299680(ptr, 2) != 0) {
        if (func_020b9bbc((char *) ptr + 0x72C, (char *) ptr + 0x190A, 6, 0x800, 0) != 0) {
            func_ov144_02299660(ptr, 2);
        }
    }
    if (func_ov144_02299680(ptr, 4) != 0) {
        func_ov144_02299660(ptr, 4);
        func_ov144_02299f44(ptr);
    }
}
