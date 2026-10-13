/* func_020f6f88 @ 0x020f6f88, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    void *unk_00;
} UnkStruct_020f6f88;

extern void func_020f6f3c(UnkStruct_020f6f88 *, int);
extern void func_020eed18(int, int);
extern void func_020eedb8(int, int, int);

void func_020f6f88(UnkStruct_020f6f88 *self, int n)
{
    unsigned int ok;
    func_020f6f3c(self, n);
    if ((unsigned int) n > 0xd) {
        return;
    }
    ok = (self->unk_00 != 0);
    if (ok != 0) {
        func_020eed18((int) self, 0);
    }
    func_020eedb8((unsigned short) (n + 0x14), 0xd3, (int) self);
}
