/* func_ov003_02212158 @ 0x02212158, 0x60 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *, int);
extern int func_0200f290(void *, int);
extern void func_ov003_022241a4(void *);
extern void func_0200f268(void *, int);
extern void *data_020ccf94;

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02212158;

void func_ov003_02212158(UnkStruct_02212158 *self)
{
    unsigned char *p;
    int loc[2];
    int a, b;
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        if (func_0200f290(self, 0x1c) != 0) {
            p = (unsigned char *) self + 0x7d4;
            if (p[2] != 0) {
                a = p[0];
                b = p[1];
                loc[0] = a;
                loc[1] = b;
                func_ov003_022241a4(loc);
                func_0200f268(self, 0x12);
                func_0200f268(self, 0x1c);
            }
        }
    }
}
