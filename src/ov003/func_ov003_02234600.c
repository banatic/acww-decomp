/* func_ov003_02234600 @ 0x02234600, 0x22c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_02234600;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234600_2;

extern int func_020644cc(int n);
extern void func_020550e4(unsigned char *p, int a);
extern int func_02073dd4(UnkStruct_02234600_2 *p, int a);
extern void func_ov003_02234cc4(unsigned char *self);
extern int func_ov003_02234d70(unsigned char *self);
extern void func_ov003_02235934(unsigned char *self, int a);
extern int func_ov003_02234030(unsigned char *self, int a);
extern void func_ov068_022717e0(unsigned char *self);
extern void func_ov003_022343a8(unsigned char *self);
extern void func_ov003_02234264(unsigned char *self);
extern void func_ov003_022344c8(unsigned char *self, short *p);
extern void func_ov003_022342f8(unsigned char *self, short *p);
extern int func_ov003_02234984(unsigned char *self);
extern int func_ov068_02271b30(unsigned char *self);
extern UnkStruct_02234600_2 *data_020ccf94;

void func_ov003_02234600(unsigned char *self)
{
    short *p242;
    int n;
    int flag;
    int r;
    UnkStruct_02234600 *src;
    UnkStruct_02234600 *dst;
    int x;

    p242 = (short *) (self + 0x242);
    n = (*(int *) (self + 0x21c) & 0xf0) >> 4;
    flag = 0;
    if (n > 0 && self[0x251] == 0x13) {
        if (self[0x24f] % 0x14 == 0) {
            r = func_020644cc(100);
            if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 == 0 && r > 0x5c) {
                func_020550e4(self + 0x50, 2);
            } else if (r > 0x32) {
                func_020550e4(self + 0x50, 0);
            }
        } else if ((unsigned) (*(int *) (self + 0xf4) << 4) >> 16 != 0) {
            func_ov003_02234cc4(self);
        }
    } else {
        func_ov003_02234cc4(self);
    }
    if (self[0x251] != 0xb && self[0x251] != 9) {
        func_ov003_02234d70(self);
    }
    func_ov003_02235934(self, 5);
    switch (self[0x251]) {
        case 15:
            flag = 1;
        case 3:
            if (func_ov003_02234030(self, 0) != 0 && flag != 0) {
                self[0x251] = 0x12;
            }
            break;
        case 4:
            if (n > 0) {
                func_ov068_022717e0(self);
            } else {
                func_ov003_022343a8(self);
            }
            func_ov003_02234264(self);
            *p242 = 0;
            break;
        case 12:
        case 13:
        case 14:
            if (*(signed char *) (self + 0x24d) == 0x17) {
                *p242 = 0x64;
            }
            func_ov003_022344c8(self, p242);
            break;
        case 7:
            self[0x251] = 3;
            src = (UnkStruct_02234600 *) (self + 0x204);
            dst = (UnkStruct_02234600 *) (self + 0x1d4);
            dst->x = src->x;
            dst->y = src->y;
            dst->z = src->z;
            *(int *) (self + 0x21c) = *(int *) (self + 0x21c) | 0xf00;
            break;
        case 9:
        case 11:
            func_ov003_022342f8(self, p242);
            break;
        default:
            if (n > 0) {
                *p242 = (short) (*p242 + 1);
                if ((*p242 > 0x28 && *p242 % 0xa == 0 && func_020644cc(100) > 0x50) || *p242 > 0xc8) {
                    *(int *) (self + 0x21c) = *(int *) (self + 0x21c) & 0xff0f;
                    *p242 = 0;
                    self[0x251] = 0xc;
                    *(short *) (self + 0x244) = 0x64;
                }
            } else {
                x = func_ov003_02234984(self);
                *p242 = 0;
                if (self[0x24a] == 0 && x != 0 && func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
                    func_ov068_02271b30(self);
                }
                if (self[0x251] == 0x12) {
                    self[0x251] = 4;
                } else {
                    self[0x24a] = 0;
                    self[0x251] = 0xc;
                    *(int *) (self + 0x21c) = *(int *) (self + 0x21c) & 0xfff0;
                }
            }
            break;
    }
}
