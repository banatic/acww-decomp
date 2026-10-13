/* func_ov004_022269a8 @ 0x022269a8, 0xd8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_022269a8 {
    int unk_00, unk_04, unk_08, unk_0C, unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
} UnkStruct_022269a8;

typedef struct UnkStruct_022269a8_2 UnkStruct_022269a8_2;

extern void *data_020ccf94;
extern char data_ov004_02254af0;
extern char data_ov004_02254ae4;

extern int func_02073908(void *g, int k);
extern void func_020b220c(void);
extern void func_0200f328(UnkStruct_022269a8_2 *self, int k);
extern void func_0201107c(UnkStruct_022269a8_2 *self, char *p);
extern void func_ov004_02225de0(UnkStruct_022269a8_2 *self, Vec3 *v, int *q, int *a);

void func_ov004_022269a8(UnkStruct_022269a8_2 *self)
{
    int a;
    Vec3 v;
    UnkStruct_022269a8 *s;
    unsigned char *p;

    s = (UnkStruct_022269a8 *) ((char *) self + 0x7d4);
    p = &s->unk_14;
    if (*p != 0) {
        *p = (unsigned char) (*p - 1);
        if (s->unk_15 == 2) {
            if (*p != 0) {
                return;
            }
            if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) == 0) {
                func_020b220c();
                func_0200f328(self, 0x4cb);
            }
            *(int *) ((char *) self + 0x7f8) = 1;
            func_0201107c(self, &data_ov004_02254af0);
            s->unk_0C = 0x400;
        } else {
            if (*p > 0xa) {
                return;
            }
            if (*p == 0xa) {
                *(int *) ((char *) self + 0x7f8) = 1;
                func_0201107c(self, &data_ov004_02254ae4);
                s->unk_0C = 0x400;
            } else if (*p == 0) {
                if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) == 0) {
                    func_0200f328(self, 0x4d3);
                }
            }
        }
    }
    a = s->unk_10;
    v.x = s->unk_00;
    v.y = s->unk_04;
    v.z = s->unk_08;
    func_ov004_02225de0(self, &v, &s->unk_0C, &a);
}
