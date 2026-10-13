/* func_ov004_02242078 @ 0x02242078, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02242078 {
    short ang;
    short pad_02;
    Vec3 v;
    char unk_10[0x18 - 0x10];
    unsigned char flag;
} UnkStruct_02242078;

typedef struct UnkStruct_02242078_2 {
    char unk_00[0x98];
    short unk_98;
    char unk_9A[0x192 - 0x9a];
    short unk_192;
    char unk_194[2];
    signed char unk_196;
    char unk_197[0x2c8 - 0x197];
    Vec3 pos;
} UnkStruct_02242078_2;

extern int func_ov004_02244658(UnkStruct_02242078_2 *self, Vec3 *v);
extern int func_0200322c(Vec3 *a, Vec3 *b);
extern void func_020e8870(short *cur, int target, int step);
extern void func_02056fcc(char *p, int a, int b, int c, int d);
extern void func_020550e4(char *p, int a);

int func_ov004_02242078(UnkStruct_02242078_2 *self)
{
    UnkStruct_02242078 info;
    int rc, ang, v;
    Vec3 *p;
    short *t;
    char *b;

    rc = func_ov004_02244658(self, &info.v);
    p = &self->pos;
    t = &self->unk_98;
    if (info.flag != 0) {
        if (rc == 3 || *t != 0) {
            ang = func_0200322c(p, &info.v);
            info.ang = self->unk_192;
            b = (char *) self + 0xb0;
            func_020e8870(&info.ang, ang, 0x38e);
            self->unk_192 = info.ang;
            if (self->unk_196 == 0x37) {
                v = *(int *) (b + 0xa0) >> 12;
                if ((unsigned short) v < 0xb && (unsigned short) (*(int *) (b + 0xa4) >> 12) <= 2) {
                    func_02056fcc(b + 0x9c, 0xb, 1, 0x1000, 3);
                } else if ((unsigned short) v < 0xe && (unsigned short) (*(int *) (b + 0xa4) >> 12) < 0xa) {
                    func_02056fcc(b + 0x9c, 0xe, 0, 0x1000, 0xa);
                } else if ((unsigned short) (*(int *) (b + 0xa4) >> 12) == 0xd && (unsigned short) v > 0xa) {
                    func_020550e4(b, 0xa);
                }
            }
            if (*t > 0) {
                *t = (short) (*t - 1);
            } else {
                *t = 0x3c;
            }
            return 1;
        }
    }
    return 0;
}
