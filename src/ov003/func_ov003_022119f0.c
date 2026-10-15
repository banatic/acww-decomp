/* func_ov003_022119f0 @ 0x022119f0, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_ov003_02211ac0(void *self);
extern int func_02073908(unsigned int a, unsigned int b);
extern int func_0201100c(void *self);
extern int func_0200f434(void *self, unsigned int *arr);
extern void func_02010d64(void *self);
extern void func_ov003_02211a4c(void *self);

typedef struct UnkStruct_022119f0 {
    unsigned int pad_00;
    unsigned int v[3];
} UnkStruct_022119f0;

typedef struct UnkStruct_022119f0_2 {
    unsigned char pad_00[0x7d4];
    UnkStruct_022119f0 sub;
    unsigned char pad_7E4[0x800 - 0x7e4];
    unsigned int unk_800;
} UnkStruct_022119f0_2;

void func_ov003_022119f0(UnkStruct_022119f0_2 *self)
{
    func_ov003_02211ac0(self);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_0201100c(self);
    } else {
        UnkStruct_022119f0 *p = &self->sub;
        unsigned int arr[3];
        arr[0] = p->v[0];
        arr[1] = p->v[1];
        arr[2] = p->v[2];
        func_0200f434(self, arr);
    }

    func_02010d64(self);
    func_ov003_02211a4c(self);
}
