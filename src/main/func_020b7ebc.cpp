/* func_020b7ebc @ 0x020b7ebc, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_02030640(void *self, int b, int c, int d);

typedef struct {
    char pad_00[0x14];
    int unk_14;
    unsigned char unk_18;
} UnkStruct_020b7ebc;

// A position; the empty destructor keeps the sixteen frame bytes the ROM reserves for it.
struct Vec3 {
    int x, y, z;
    Vec3() {}
    ~Vec3() {}
};

extern "C" int func_020b7ebc(UnkStruct_020b7ebc *self, int b, int c, int d, int e, unsigned char f)
{
    Vec3 pos;
    self->unk_14 = e;
    self->unk_18 = f;
    func_02030640(self, b, c, d);
    return 1;
}
