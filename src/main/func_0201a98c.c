/* func_0201a98c @ 0x0201a98c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int pad_00;
    int unk_04;
    char pad_08[0x54];
    int unk_5C;
    unsigned char unk_60;
} UnkStruct_0201a98c_2;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0201a98c;

extern int func_0201ad8c(void *ptr, UnkStruct_0201a98c *out);
extern void func_0201aa94(UnkStruct_0201a98c_2 *self, void *param, int field4, UnkStruct_0201a98c *data, int val5c,
                          unsigned char val60);

void func_0201a98c(UnkStruct_0201a98c_2 *self, void *param)
{
    UnkStruct_0201a98c local;
    UnkStruct_0201a98c copy;

    if (self->unk_04 == 0) {
        return;
    }
    if (!func_0201ad8c((void *) (self->unk_04 + 0x3b0), &local)) {
        return;
    }
    copy.x = local.x;
    copy.y = local.y;
    copy.z = local.z;
    func_0201aa94(self, param, self->unk_04, &copy, self->unk_5C, self->unk_60);
}
