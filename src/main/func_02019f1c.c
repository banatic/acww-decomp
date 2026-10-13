/* func_02019f1c @ 0x02019f1c, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02019f1c {
    char pad_00[0x1c];
    char sub1c[0x48 - 0x1c];
    char sub48[0x74 - 0x48];
    int unk_74;
    int unk_78;
} UnkStruct_02019f1c;

typedef struct Other {
    char pad_00[0x418];
    int unk_418;
} Other;

extern int func_0201a3e8(UnkStruct_02019f1c *self);
extern int func_02056f28(void *buf, int n);
extern int func_020645e0(UnkStruct_02019f1c *self);
extern void func_02056778(void *p);
extern int func_0201a7b4(int *p);
extern int func_0201a7bc(int *p);
extern int func_0201a2e8(UnkStruct_02019f1c *self, int val);
extern void func_0201a19c(UnkStruct_02019f1c *self, int val);
extern void func_0201a27c(UnkStruct_02019f1c *self);
extern int func_0201a234(UnkStruct_02019f1c *self);
extern void func_0201a174(UnkStruct_02019f1c *self);

void func_02019f1c(UnkStruct_02019f1c *self, Other *other)
{
    if (func_0201a3e8(self) == 0) {
        return;
    }

    if (self->unk_74 == 0) {
        if (func_02056f28(&self->sub1c, 0) == 0 || func_020645e0(self) != 0) {
            func_02056778(&self->sub1c);
        }
    } else {
        func_02056778(&self->sub1c);
    }

    if (func_0201a7b4(&other->unk_418) < 2) {
        if (func_0201a7bc(&other->unk_418) != 0) {
            if (func_0201a2e8(self, self->unk_78) == 0) {
                func_0201a19c(self, func_0201a7b4(&other->unk_418));
                func_0201a27c(self);
            } else {
                if (func_0201a234(self) != 0) {
                    func_0201a27c(self);
                }
            }
        } else {
            if (func_0201a2e8(self, self->unk_78) != 0 && func_0201a234(self) != 0) {
                func_0201a174(self);
            }
        }
    } else {
        if (func_0201a2e8(self, self->unk_78) != 0) {
            func_0201a174(self);
        }
    }

    self = (UnkStruct_02019f1c *) ((char *) self + 0x48);
    func_02056778(self);
}
