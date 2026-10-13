/* func_ov051_02260c1c @ 0x02260c1c, 0x28 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern char func_ov051_022605e8(void *self, int n);
extern void func_0206844c(int, char *, int);
extern int data_ov051_022615c0;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02260c1c;

void func_ov051_02260c1c(UnkStruct_02260c1c *self)
{
    char c;
    c = func_ov051_022605e8(self, 0x25);
    func_0206844c(self->unk_40, &c, data_ov051_022615c0);
}
