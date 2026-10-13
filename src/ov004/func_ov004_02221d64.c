/* func_ov004_02221d64 @ 0x02221d64, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02019c90(void *p, int a, int b, unsigned short c);
extern unsigned short data_020c80f8;
extern int func_020644cc(int a);
extern int func_ov004_02222178(void *self, int a);

void func_ov004_02221d64(char *self)
{
    unsigned char *p;
    unsigned int v;

    switch (*(unsigned char *) (self + 0xa90)) {
        case 0x45:
            func_02019c90(self + 0x564, 1, 7, data_020c80f8);
            break;
        case 1:
            func_02019c90(self + 0x564, 1, 0, data_020c80f8);
            *(short *) (self + 0xa76) = (short) (func_020644cc(0x14) + 0x14);
            break;
        case 0:
            if (func_ov004_02222178(self, 0) != 0) {
                return;
            }
            break;
    }
    if (*(unsigned char *) (self + 0xa90) != 0) {
        *(unsigned char *) (self + 0xa90) -= 1;
    }
}
