/* func_ov049_02261a6c @ 0x02261a6c, 0xc8 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_ov049_0226332c[];
extern unsigned char data_ov049_02263334[];
extern unsigned char data_ov049_0226333c[];
extern struct {
    unsigned char pad0[4];
    unsigned char byte0;
    unsigned char pad1[7];
    unsigned char byte1;
    unsigned char pad2[7];
    unsigned char byte2;
    unsigned char pad3[7];
    unsigned char byte3;
} data_ov049_02263324;

extern void func_ov049_02260b20(unsigned int a, unsigned char *b, int c);

void func_ov049_02261a6c(unsigned int self)
{
    unsigned int cond;
    unsigned char *base;
    unsigned short h;

    base = *(unsigned char **) (self + 0xb0);
    cond = 0;
    h = *(unsigned short *) (base + 0x738);
    if ((unsigned int) h >= 0x11a8 && (unsigned int) h <= 0x12a7) {
        cond = 1;
    }
    if (cond != 0) {
        func_ov049_02260b20(self, (unsigned char *) &data_ov049_02263324, data_ov049_02263324.byte0 - 1);
    } else if (((unsigned int) h >= 0x13c8 && (unsigned int) h <= 0x1407) ||
               ((unsigned int) h >= 0x13a8 && (unsigned int) h <= 0x13c7)) {
        func_ov049_02260b20(self, data_ov049_0226332c, data_ov049_02263324.byte1 - 1);
    } else if ((unsigned int) h >= 0x1431 && (unsigned int) h <= 0x1470) {
        func_ov049_02260b20(self, data_ov049_02263334, data_ov049_02263324.byte2 - 1);
    } else if ((unsigned int) h >= 0x1380 && (unsigned int) h <= 0x139f) {
        func_ov049_02260b20(self, data_ov049_0226333c, data_ov049_02263324.byte3 - 1);
    }
}
