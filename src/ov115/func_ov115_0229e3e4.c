/* func_ov115_0229e3e4 @ 0x0229e3e4, 0x36 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(int, int);
extern void func_020027f0(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov115_0229e3a8(int);

void func_ov115_0229e3e4(int arg)
{
    if (func_ov002_02207f3c(arg, 0) != 0) {
        func_020027f0(3);
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov115_0229e3a8(arg);
    }
}
