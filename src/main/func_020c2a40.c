/* func_020c2a40 @ 0x020c2a40, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *arg);
extern void func_0201c280(void *a, void *b);
extern void func_020c1b30(void *a, void *b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern int func_020b65c4(void);

int func_020c2a40(unsigned char *arg)
{
    if (func_0202edc8(arg) == 0) {
        return 0;
    }
    func_0201c280(arg, arg + 0x658);
    func_020c1b30(arg + 0x658, arg);
    func_0201af28(arg + 0x350, 2, 0x333, 0xcc, 0x133);
    func_0201af28(arg + 0x350, 1, 0x1b3, 0xcc, 0x133);
    if (func_020b65c4() == 0xb) {
        *(short *) (arg + 0x8e) = -32768;
        *(short *) (arg + 0x94) = -32768;
    }
    if (func_020b65c4() == 0xc) {
        *(short *) (arg + 0x8e) = -32768;
        *(short *) (arg + 0x94) = -32768;
    }
    if (func_020b65c4() == 0x2f) {
        *(short *) (arg + 0x8e) = 0;
        *(short *) (arg + 0x94) = 0;
        *(int *) (arg + 0x5c) = 0xe000;
        *(int *) (arg + 0x64) = 0x4000;
        func_0201af28(arg + 0x350, 1, 0x280, 0xcc, 0x133);
    }
    *(unsigned char *) (arg + 0x563) = 1;
    return 1;
}
