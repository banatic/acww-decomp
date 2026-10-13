/* func_ov003_022124c4 @ 0x022124c4, 0xb0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011398(void *, int);
extern void func_0201107c(void *, int *);
extern void func_02010f5c(void *);
extern int func_02073908(int, unsigned int);
extern void func_0201100c(void *);
extern void func_02010d64(void *);
extern void func_ov003_02212574(void *, int *, int _x);
extern int func_0200f554(void *);
extern unsigned int func_02008258(void *, unsigned int);
extern void func_ov003_02212728(void *);
extern void func_020912d4(int, void *, void *, int);
extern int data_020ccf94;

typedef struct UnkStruct_022124c4 {
    char pad_00[0x5c];
    char unk_5C[0x8e - 0x5c];
    char unk_8E[0x98 - 0x8e];
    void *unk_98;
    char pad_9C[0x7f0 - 0x9c];
    unsigned int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    unsigned int unk_7FC;
    unsigned int unk_800;
} UnkStruct_022124c4;

void func_ov003_022124c4(UnkStruct_022124c4 *self)
{
    void *obj;
    int tmp0;
    int arr[3];

    obj = self->unk_98;
    tmp0 = func_02011398(obj, 0);
    func_0201107c(self, &tmp0);
    func_02010f5c(self);

    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_0201100c(self);
        func_02010d64(self);
        arr[0] = 0;
        arr[1] = 0;
        arr[2] = 0;
        func_ov003_02212574(self, arr, 0);
    } else {
        if (func_0200f554(self)) {
            func_0201100c(self);
        }
        func_02010d64(self);
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }

    func_ov003_02212728(self);

    if (obj != 0 && self->unk_98 == 0) {
        func_020912d4(0x2a, (void *) ((char *) self + 0x5c), (void *) ((char *) self + 0x8e), 0);
    }
}