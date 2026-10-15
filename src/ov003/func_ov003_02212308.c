/* func_ov003_02212308 @ 0x02212308, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern void *func_020113a4(void *, int, int);
extern void func_0201107c(void *, void **);
extern void func_ov003_02212348(void *);

struct UnkStruct_02212308 {
    char pad_00[0x98];
    void *unk_98;
};

void func_ov003_02212308(struct UnkStruct_02212308 *self)
{
    void *v;

    func_02010f5c(self);
    func_0201100c(self);
    func_02010d64(self);
    v = func_020113a4(self->unk_98, 0, 0x171);
    func_0201107c(self, &v);
    func_ov003_02212348(self);
}
