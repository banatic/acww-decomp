/* func_ov145_02299e90 @ 0x02299e90, 0x40 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc2];
    unsigned char flag;
    char pad_C3[5];
    char unk_C8;
} UnkStruct_02299e90;

extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(void *ptr);
extern int func_ov145_02299f30(UnkStruct_02299e90 *self);
extern int func_ov145_02299eec(UnkStruct_02299e90 *self);
extern void func_ov145_02299e60(UnkStruct_02299e90 *self, int p1, int p2);

void func_ov145_02299e90(UnkStruct_02299e90 *self)
{
    int v1;
    int v2;
    if (self->flag == 4) {
        func_ov002_0220a314(&self->unk_C8);
    } else {
        func_ov002_0220a2b4(&self->unk_C8);
    }
    v1 = func_ov145_02299f30(self);
    v2 = func_ov145_02299eec(self);
    func_ov145_02299e60(self, v1, v2);
}
