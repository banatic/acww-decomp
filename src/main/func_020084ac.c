/* func_020084ac @ 0x020084ac, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200faf0(void *p, int x);
extern int func_02056f94(void *p);
extern void func_020109a0(void *self, int a, int b, unsigned short c);
extern int func_0200f328(void *p, int a);
extern int func_02008458(void *a0, int a1, int a2);
extern void func_0200f268(void *p, int a);

void func_020084ac(void *a0)
{
    if (func_0200faf0(a0, 0x800) == 0) {
        return;
    }
    if (func_02056f94((char *) a0 + 0x2d0) == 0) {
        return;
    }
    if (*(int *) ((char *) a0 + 0x704) == 0x7e) {
        func_020109a0(a0, 0x7f, 0, 0);
        func_0200f328(a0, 0x6e);
    } else {
        func_02008458(a0, 6, -1);
        func_0200f268(a0, 0xd);
    }
}
