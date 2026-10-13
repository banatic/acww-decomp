/* func_020656ac @ 0x020656ac, 0x1ac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short r : 5;
    unsigned short g : 5;
    unsigned short b : 5;
    unsigned short a : 1;
} Col;

typedef struct {
    char pad_00[0xf4];
    unsigned char unk_F4;
    char pad_F5[0x168 - 0xf5];
    Col col;
} UnkStruct_020656ac;

extern Col func_020bbf00(int);
extern int func_020b67d4(void);
extern int func_020b65c4(void);
extern unsigned char data_020e54a8;

void func_020656ac(UnkStruct_020656ac *self)
{
    Col y, z, x;
    int r, g, b;
    unsigned int ok;
    int k;

    x = func_020bbf00(3);
    y = x;
    z = y;
    if (func_020b67d4() != 0) {
        if (self->unk_F4 != 0) {
            r = z.r + 0xa;
            g = z.g + 0xa;
            b = z.b + 7;
            if (r > 0x1f) {
                z.r = 0x1f;
            } else {
                z.r = r;
            }
            if (g > 0x1f) {
                z.g = 0x1f;
            } else {
                z.g = g;
            }
            if (b > 0x1f) {
                z.b = 0x1f;
            } else {
                z.b = b;
            }
        }
    } else {
        ok = (data_020e54a8 == 1) ? 1 : 0;
        if (ok != 0) {
            k = func_020b65c4();
            switch (k) {
                case 0xb:
                    r = z.r + 0xa;
                    g = z.g + 0xa;
                    b = z.b + 7;
                    if (r > 0x1f) {
                        z.r = 0x1f;
                    } else {
                        z.r = r;
                    }
                    if (g > 0x1f) {
                        z.g = 0x1f;
                    } else {
                        z.g = g;
                    }
                    if (b > 0x1f) {
                        z.b = 0x1f;
                    } else {
                        z.b = b;
                    }
                    break;
                case 0x27:
                case 0x28:
                    break;
                default:
                    z.r = 0x1f;
                    z.g = 0x1f;
                    z.b = 0x1f;
                    break;
            }
        }
    }
    self->col = z;
}
