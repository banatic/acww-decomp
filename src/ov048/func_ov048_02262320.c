/* func_ov048_02262320 @ 0x02262320, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02262320 {
    char pad_00[0xb8];
    void *unk_B8;
};

extern void func_ov048_02262390(void *self, int a);
extern void func_ov048_02262618(void *self, int a, int b);
extern void func_ov048_022616b8(void *self, int a);

void func_ov048_02262320(struct UnkStruct_02262320 *self)
{
    func_ov048_02262390(self, 1);
    func_ov048_02262618(self, 4, 2);
    *(unsigned short *) ((char *) self->unk_B8 + 0xe6e) = 0x960;
    func_ov048_022616b8(self, 10);
}
