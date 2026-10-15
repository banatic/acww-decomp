/* func_ov004_022232b4 @ 0x022232b4, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02223388(void *self, int a);
extern int func_02016884(void *a, int b, void *c);
extern int func_ov004_0222fd70(void);
extern int func_ov004_0222fdb8(void);
extern void func_ov004_0222fd58(unsigned short v);

int func_ov004_022232b4(char *self)
{
    unsigned int m, sh;

    if (*(short *) (self + 0x70c) != *(short *) (self + 0x8e)) {
        func_ov004_02223388(self, 3);
        return 1;
    }
    if (func_02016884(self + 0x334, 0xe4, self + 0x2a0) != 0) {
        if (func_ov004_0222fd70() != 0) {
            func_ov004_0222fdb8();
            m = *(unsigned char *) (self + 0x712) * 0x38;
            sh = (unsigned int) (*(int *) (self + 0x190) << 4) >> 16;
            func_ov004_0222fd58((unsigned short) (m + sh));
        }
    }
    return 1;
}
