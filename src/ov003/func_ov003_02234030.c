/* func_ov003_02234030 @ 0x02234030, 0x15c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234030;

extern UnkStruct_02234030 *data_020ccf94;
extern int func_020a7278(void);
extern int func_02073dd4(UnkStruct_02234030 *g, int a);
extern int func_020644cc(int a);
extern int func_ov003_02235834(unsigned char *self, int ang, int k);
extern short func_0200322c(int *a, int *b);
extern int func_020e8870(short *p, int ang, int step);

int func_ov003_02234030(unsigned char *self, int b)
{
    int ret;
    short ang;
    int f;
    unsigned char k;

    ret = 0;
    ang = *(short *) (self + 0x23a);
    if (self[0x251] != 0xb) {
        if (func_020a7278() == 0 && func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
            if (*(int *) (self + 0x204) != *(int *) (self + 0x1d4) && *(int *) (self + 0x20c) != *(int *) (self + 0x1dc)) {
                self[0x251] = 4;
                self[0x24c] = (unsigned char) b;
            }
        } else {
            int *p = (int *) (self + 0x204);
            int *q = (int *) (self + 0x1d4);
            f = *(int *) (self + 0x21c);
            if ((p[0] == q[0] && p[2] == q[2]) || (f & 0xf00) != 0) {
                k = self[0x259];
                k = (unsigned char) (k + func_020644cc(3));
                if (self[0x24a] != 0) {
                    k = (unsigned char) (k + (unsigned char) (func_020644cc(2) + 2));
                }
                if (func_ov003_02235834(self, *(short *) (self + 0x240), k << 12) != 0) {
                    *(short *) (self + 0x240) = func_0200322c((int *) (self + 0x204), (int *) (self + 0x1d4));
                    f = f & 0xf0ff;
                    *(int *) (self + 0x21c) = f;
                } else {
                    f = f & 0xf0ff;
                    *(int *) (self + 0x21c) = f;
                }
            }
            if (func_020e8870(&ang, *(short *) (self + 0x240), 0xe38) != 0) {
                self[0x251] = 4;
                self[0x24c] = (unsigned char) b;
                ret = 1;
            }
            *(short *) (self + 0x23a) = ang;
        }
    } else {
        func_ov003_02235834(self, *(short *) (self + 0x23a), (unsigned char) (self[0x259] * 2) << 12);
        self[0x24c] = (unsigned char) b;
    }
    return ret;
}
