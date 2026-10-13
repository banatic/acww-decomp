/* func_ov003_02232b68 @ 0x02232b68, 0x108 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02232b68;

extern UnkStruct_02232b68 *data_020ccf94;
extern int func_02073dd4(UnkStruct_02232b68 *g, int a);
extern int func_020a7278(void);
extern int func_ov003_02232210(unsigned char *self);
extern int func_ov003_02232414(unsigned char *self);
extern int func_ov003_02233e4c(unsigned char *self, Vec3 *v);
extern void func_020550e4(unsigned char *p, int a);
extern int func_ov003_022353e0(unsigned char *self, Vec3 *p);
extern int func_ov003_02232598(unsigned char *self, int a);
extern void func_ov003_02230f60(unsigned char *self);

void func_ov003_02232b68(unsigned char *self)
{
    Vec3 *p;
    short w;
    Vec3 v;

    p = (Vec3 *) (self + 0x204);
    w = *(short *) (self + 0x232);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        if (func_ov003_02232210(self) != 0) {
            return;
        }
    } else {
        if (func_ov003_02232414(self) == 0) {
            return;
        }
    }
    func_ov003_02233e4c(self, &v);
    if (self[0x254] >= self[0x255] &&
        (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 || func_020a7278() != 0 ||
         (*(int *) (self + 0x1d4) == *(int *) (self + 0x204) && *(int *) (self + 0x1dc) == *(int *) (self + 0x20c)))) {
        self[0x251] = 7;
        func_020550e4(self + 0x50, 0);
        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() != 0) {
            Vec3 *s = (Vec3 *) (self + 0x204);
            Vec3 *d = (Vec3 *) (self + 0x1d4);
            d->x = s->x;
            d->y = s->y;
            d->z = s->z;
        }
    } else if (w <= 0) {
        if (func_ov003_02232598(self, 1) != 0) {
            func_ov003_02230f60(self);
        }
    } else {
        if (func_ov003_022353e0(self, p) != 0) {
            w = 1;
        }
        *(short *) (self + 0x232) = (short) (w - 1);
    }
}
