/* func_ov051_02260d1c @ 0x02260d1c, 0x28 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern char func_ov051_022605e8(void *p, int n);
extern void func_0206844c(void *dst, char *src, void *param);
extern void *data_ov051_022615c0;

typedef struct {
    char pad_00[0x40];
    void *unk_40;
} UnkStruct_02260d1c;

void func_ov051_02260d1c(UnkStruct_02260d1c *self)
{
    char c = func_ov051_022605e8(self, 0xF);
    func_0206844c(self->unk_40, &c, data_ov051_022615c0);
}
