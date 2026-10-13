/* func_ov004_02234418 @ 0x02234418, 0x158 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    unsigned char category, pad_01[3], height, tail[12];
} Entry;
extern "C" unsigned char data_ov004_022593a4, data_ov004_02255c30;
extern "C" char *data_ov004_022594d4[];
extern "C" Entry data_ov004_02247924[];
extern "C" char data_021f38f8[];
extern "C" int func_02071298(void *, unsigned short *);
extern "C" int func_ov004_022394ac(int, int);
extern "C" int func_ov004_0223546c(void *, int);
static inline int height(int id)
{
    return data_ov004_02247924[id].height << 12;
}
extern "C" void func_ov004_02234418(void *self)
{
    int i;
    char **slot;
    unsigned short item;
    Vec *position, *previous;
    i = data_ov004_022593a4;
    slot = data_ov004_022594d4 + i;
    item = 0xfff1;
    for (; i < (int) data_ov004_02255c30; ++slot, ++i) {
        item = (unsigned int) i < 56 ? (unsigned short) (i + 0x12e8) : 0x12e8;
        if (func_02071298(data_021f38f8, &item)) {
            position = (Vec *) (*slot + 0x1a8);
            switch (i) {
                case 52:
                case 53:
                case 54:
                    position->z = 0x12000;
                    if ((unsigned int) (i - 53) <= 1) {
                        position->x = func_ov004_022394ac(5, 30);
                    } else if (i == 52) {
                        position->x = func_ov004_022394ac(5, 30);
                    }
                    break;
                case 38:
                    position->z = 0x14700;
                    position->x = 0x9e00;
                    break;
                case 35:
                    position->z = 0x14a00;
                    position->x = 0x6000;
                    break;
                case 37:
                    position->z = 0x14a00;
                    position->x = 0x7000;
                    break;
                default:
                    position->z = func_ov004_022394ac(18, 22);
                    position->x = func_ov004_022394ac(5, 30);
                    break;
            }
            position->y = (height(i) >> 6) - 0x1000;
            previous = (Vec *) (*slot + 0x1b4);
            previous->x = position->x;
            previous->y = position->y;
            previous->z = position->z;
            (*slot)[0x164] = data_ov004_02247924[i].category;
            func_ov004_0223546c(self, i);
        }
    }
}
