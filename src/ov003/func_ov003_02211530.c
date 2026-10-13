/* func_ov003_02211530 @ 0x02211530, 0x74 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *, int);
extern int func_0200f290(void *, int);
extern void func_ov003_02221294(int, int *, unsigned char);
extern void func_0200f268(void *, int);
extern void *data_020ccf94;

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02211530;

void func_ov003_02211530(UnkStruct_02211530 *self, int k)
{
    int loc[3];
    int *p;
    if (func_02073908(data_020ccf94, self->unk_800) == 0) {
        if (func_0200f290(self, 0x1c) != 0) {
            p = (int *) ((char *) self + 0x7d4);
            loc[0] = p[0];
            loc[1] = p[1];
            loc[2] = p[2];
            func_ov003_02221294(self->unk_800, loc, ((unsigned char *) p)[0xd]);
            func_0200f268(self, 0x1c);
            func_0200f268(self, 9);
        }
        if (k != 0x60 && k != 0x61) {
            func_0200f268(self, 0xd);
        }
    }
}
