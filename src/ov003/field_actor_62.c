/* field_actor_62: 2 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022121b8 @ 0x022121b8, 0x54 bytes, Thumb
 * func_ov003_02212158 @ 0x02212158, 0x60 bytes, Thumb
 */

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02212158;

extern void func_ov003_02212270(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *);
extern int func_ov003_022122ac(unsigned char *, int, int *, int, int);
extern int func_02073908(void *, int);
extern int func_0200f290(void *, int);
extern void func_ov003_022241a4(void *);
extern void func_0200f268(void *, int);
extern void *data_020ccf94;

void func_ov003_022121b8(unsigned char *obj, int param2)
{
    unsigned char buf[4];

    func_ov003_02212270(obj + 0x8f0, buf, buf + 1, buf + 2, buf + 3);
    obj[0x16c] = buf[3];

    if (buf[0] == 0) {
        int arr[2];

        arr[0] = buf[1];
        arr[1] = buf[2];
        func_ov003_022122ac(obj, 0, arr, 6, param2);
    }
}

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
