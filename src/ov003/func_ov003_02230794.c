/* func_ov003_02230794 @ 0x02230794, 0x224 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022309c0(unsigned char *self, int a, int b, int c, int d);
extern void func_02056fcc(unsigned char *p, int a, int b, int c, int d);

void func_ov003_02230794(unsigned char *self)
{
    switch (*(signed char *) (self + 0x24d)) {
        case 0x2f:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x2e:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x2d:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x2c:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x28:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x29:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x2a:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x26:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x21:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x27:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x2b:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x22:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x24:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        case 0x1f:
            func_ov003_022309c0(self, 0xfa, 0x50, 0x16, 500);
            self[0x257] = 1;
            break;
        case 9:
            func_ov003_022309c0(self, 0x96, 0x46, 0x18, 1000);
            self[0x257] = 0xa;
            func_02056fcc(self + 0xec, (unsigned) (*(int *) (self + 0xf0) << 4) >> 16, 1, 0x1000, 0);
            break;
        case 0x10:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            break;
        case 0x11:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            break;
        case 0x12:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            break;
        case 0x13:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            break;
        case 0x14:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            self[0x252] = 0;
            break;
        case 0x34:
            func_ov003_022309c0(self, 0x82, 0x3c, 0x16, 1000);
            break;
        default:
            func_ov003_022309c0(self, 0x64, 0x50, 0x19, 1000);
            break;
    }
}
