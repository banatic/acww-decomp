/* func_ov003_02212884 @ 0x02212884, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020113a4(int, int, int);
extern void func_0201107c(void *, int *);
extern int func_02073908(void *, int);
extern void func_ov003_02212a54(void *);
extern void func_02010f5c(void *);
extern void func_0201100c(void *);
extern void func_02010d64(void *);
extern void func_ov003_02212968(void *);
extern void func_ov003_02212a14(void *);
extern int func_0200f554(void *);
extern void func_ov003_0221292c(void *);
extern void func_020912d4(int, void *, void *, int);
extern void *data_020ccf94;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C[0x32];
    unsigned char unk_8E[0x0a];
    int unk_98;
    unsigned char pad_9C[0x800 - 0x9c];
    int unk_800;
} SelfType;

void func_ov003_02212884(SelfType *self)
{
    int tmp;
    int orig;
    orig = self->unk_98;
    tmp = func_020113a4(orig, 0, 0x171);
    func_0201107c(self, &tmp);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_02212a54(self);
        func_02010f5c(self);
        func_0201100c(self);
        func_02010d64(self);
        func_ov003_02212968(self);
        func_ov003_02212a14(self);
    } else {
        func_02010f5c(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        func_ov003_0221292c(self);
    }
    if (orig != 0 && self->unk_98 == 0) {
        func_020912d4(0x2a, &self->unk_5C, &self->unk_8E, 0);
    }
}
