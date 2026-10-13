/* func_ov003_02215d1c @ 0x02215d1c, 0x9c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int, int);
extern void func_ov003_02215dfc(void *);
extern void func_ov003_02215e0c(void *);
extern void func_0201100c(void *);
extern void func_02010d64(void *);
extern int func_020113a4(void *, int, int);
extern void func_0201107c(void *, int *);
extern void func_ov003_02215db8(void *);
extern int func_0200f554(void *);

extern int data_020ccf94;

struct UnkStruct_02215d1c {
    char pad_00[0x98];
    void *unk_98;
    char pad_9C[0x800 - 0x98 - 4];
    int unk_800;
};

void func_ov003_02215d1c(struct UnkStruct_02215d1c *self)
{
    int v1, v2;
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02215dfc(self);
        func_ov003_02215e0c(self);
        func_0201100c(self);
        func_02010d64(self);
        v1 = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &v1);
        func_ov003_02215db8(self);
    } else {
        func_ov003_02215e0c(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        v2 = func_020113a4(self->unk_98, 0, 0x171);
        func_0201107c(self, &v2);
        func_ov003_02215db8(self);
    }
}
