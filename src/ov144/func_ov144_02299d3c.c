/* func_ov144_02299d3c @ 0x02299d3c, 0x78 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov144_02299db4(void *, int, int);
extern int func_020b9bbc(void *, void *, int, int, int);
extern void func_ov144_02299660(void *, int);

void func_ov144_02299d3c(char *ptr)
{
    func_0206fdd4(ptr + 0x110a, 0, 0, 0x1f, 0x1f, 4);
    if (*(short *) (ptr + 0xbc) == *(short *) (ptr + 0xba)) {
        func_ov144_02299db4(ptr, *(short *) (ptr + 0xbc), 10);
    } else {
        func_ov144_02299db4(ptr, *(short *) (ptr + 0xbc), 9);
        func_ov144_02299db4(ptr, *(short *) (ptr + 0xba), 5);
    }
    if (func_020b9bbc(ptr + 0x708, ptr + 0x110a, 4, 0x800, 0) != 0) {
        func_ov144_02299660(ptr, 8);
    }
}
