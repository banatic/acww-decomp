/* func_ov004_02234570 @ 0x02234570, 0x130 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
struct Entry {
    unsigned char type, pad_01[3], height, rest[12];
};
extern unsigned char data_ov004_022593a4, data_ov004_02255c30;
extern unsigned char *data_ov004_022594d4[];
extern unsigned char data_021f38f8[], data_ov004_02247924[];
extern int func_02071298(void *, unsigned short *);
extern int func_ov004_022394ac(int, int);
extern int func_ov004_0223546c(void *, int);
void func_ov004_02234570(void *self)
{
    int i = data_ov004_022593a4;
    unsigned char **slot = &data_ov004_022594d4[i];
    unsigned short item = 0xfff1;
    for (; i < (int) data_ov004_02255c30; ++slot, ++i) {
        item = (unsigned) i < 56 ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_02071298(data_021f38f8, &item)) {
            Vec *position = (Vec *) (*slot + 0x1a8);
            int offset;
            Vec *saved;
            if (i >= 17) {
                if (i != 25) {
                    position->x = func_ov004_022394ac(9, 26);
                    position->z = func_ov004_022394ac(5, 10);
                } else {
                    position->x = func_ov004_022394ac(9, 26);
                    position->z = func_ov004_022394ac(19, 24);
                }
            } else {
                switch (i) {
                    case 10:
                        position->z = 0x14a00;
                        position->x = 0xc800;
                        break;
                    case 12:
                        position->z = 0x13900;
                        position->x = 0x15900;
                        break;
                    default:
                        position->x = func_ov004_022394ac(9, 26);
                        position->z = func_ov004_022394ac(19, 24);
                        break;
                }
            }
            offset = i * 17;
            position->y = ((((struct Entry *) (data_ov004_02247924 + offset))->height << 12) >> 6) - 0x1000;
            saved = (Vec *) (*slot + 0x1b4);
            saved->x = position->x;
            saved->y = position->y;
            saved->z = position->z;
            (*slot)[0x164] = data_ov004_02247924[offset];
            func_ov004_0223546c(self, i);
        }
    }
}
