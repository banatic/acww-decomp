/* func_ov004_02236464 @ 0x02236464, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_02236464 {
    char unk_00[0x1ac];
    int unk_1AC;
} UnkStruct_02236464;

extern unsigned char data_021f6c38;
extern unsigned char data_021f6c34;

extern int func_020b6590(void);
extern int func_020b755c(int h, Vec3 *v, int *id, unsigned char *kind);
extern long long func_020ea940(char *p, Vec3 *v);

int func_ov004_02236464(UnkStruct_02236464 *self, Vec3 *out)
{
    unsigned char kind;
    int id;
    Vec3 v;
    int ok;
    int t, d;

    ok = 0;
    if (func_020b755c(func_020b6590(), &v, &id, &kind) != 0) {
        t = (data_021f6c38 != 0 && data_021f6c34 != 0) ? 1 : 0;
        if (t == 0 && id == 0x13) {
            if (kind == 0) {
                if (func_020ea940((char *) self + 0x1a8, &v) <= 0x9000) {
                    d = self->unk_1AC - v.y;
                    if (d < 0) {
                        d = -d;
                    }
                    if (d <= 0x3000) {
                        out->x = v.x;
                        out->y = v.y;
                        out->z = v.z;
                        ok = 1;
                    }
                }
            } else if (kind == 1) {
                if (func_020ea940((char *) self + 0x1a8, &v) <= 0x9000) {
                    d = self->unk_1AC - v.y;
                    if (d < 0) {
                        d = -d;
                    }
                    if (d <= 0x3000) {
                        out->x = v.x;
                        out->y = v.y;
                        out->z = v.z;
                        ok = 1;
                    }
                }
            }
        }
    }
    return ok;
}
