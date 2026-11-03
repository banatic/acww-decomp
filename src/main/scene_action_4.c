/* scene_action_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020141e8 @ 0x020141e8, 0x5c bytes, Thumb
 * func_020141c4 @ 0x020141c4, 0x24 bytes, Thumb
 */

extern int func_02019e00(void *p);
extern int func_02019de8(void *p);
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, unsigned short i, int j);
extern void func_02019b78(void *p);
extern unsigned short data_020c80f8;
extern void func_02019b70(void *ptr);

void func_020141e8(unsigned char *out, unsigned char *base)
{
    if (func_02019e00((void *) (base + 0x564)) != 3) {
        return;
    }
    if (func_02019de8((void *) (base + 0x564)) == 0) {
        return;
    }

    func_02019d0c((void *) (base + 0x564), 0, 2, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02019b78((void *) (base + 0x564));

    out[0xa] = 1;
}

void func_020141c4(void *param1, void *param2)
{
    unsigned char b;
    void *ptr;

    b = *(unsigned char *) ((char *) param1 + 0xe);
    if (b != 0) {
        ptr = (char *) param2 + 0x564;
        func_02019b70(ptr);
        *(unsigned char *) ((char *) param1 + 0xa) = 2;
        *(unsigned char *) ((char *) param1 + 8) = 5;
    }
}
