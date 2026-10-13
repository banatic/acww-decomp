/* func_ov004_022248b0 @ 0x022248b0, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201ad18(char *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_02073d90(void *p);
extern short *func_0209d358(int a, int b);
extern int func_020960f8(int a, int b);
extern void func_0203e070(char *self, int a);
extern void func_ov004_022249b4(char *self, int a);
extern void *data_020ccf94;
extern int data_020c814c;

extern unsigned char data_021fbee8[];

int func_ov004_022248b0(char *self)
{
    // DECLS
    // ENDDECLS

    if (*(int *) (self + 0x778) > 0) {
        *(int *) (self + 0x778) = *(int *) (self + 0x778) + 1;
        if (*(int *) (self + 0x778) > 0x14) {
            func_0201ad18(self + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
            *(int *) (self + 0x778) = -1;
        }
    } else if (*(int *) (self + 0x778) == 0) {
        if (*(short *) (self + 0x3d2) > 0x2000) {
            *(int *) (self + 0x778) = 1;
        }
    }
    if (func_02073d90(data_020ccf94) == 0) {
        if (*func_0209d358(0, 0x4a) == 0) {
            if (func_020960f8(0x27, 4) != 0) {
                func_0203e070(self, 0);
            }
        }
    }
    if (*(short *) (self + 0x714) != *(short *) (self + 0x8e)) {
        func_ov004_022249b4(self, 3);
        return 1;
    }
    return 1;
}
