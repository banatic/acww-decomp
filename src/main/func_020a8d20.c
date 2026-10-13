/* func_020a8d20 @ 0x020a8d20, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a8d20 {
    void *vtable;
    char pad_04[0x28];
    int unk_2C;
    int unk_30;
    int unk_34;
    unsigned char unk_38;
} UnkStruct_020a8d20;

extern void func_020a9218(void *);
extern void func_020a9210(void *);
extern void func_020a9354(void *, int);

void func_020a8d20(UnkStruct_020a8d20 *self, int p1, int p2, int p3, unsigned char p4)
{
    self->unk_2C = p1;
    self->unk_30 = p2;
    self->unk_34 = p3;
    self->unk_38 = 0;
    if (p4) {
        func_020a9218(self);
    } else {
        func_020a9210(self);
    }
    func_020a9354(self, p2);
}
