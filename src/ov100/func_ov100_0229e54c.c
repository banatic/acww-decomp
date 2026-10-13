/* func_ov100_0229e54c @ 0x0229e54c, 0x6c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e54c {
    char pad_00[0x28c8];
    int unk_28C8;
};

extern void func_020027f0(int);
extern void func_ov100_0229c2a0(struct UnkStruct_0229e54c *, int);
extern void func_ov002_02207f04(struct UnkStruct_0229e54c *, int, int, int, int);
extern void func_ov002_02207e80(struct UnkStruct_0229e54c *, int, int, int);
extern void func_ov002_02208090(struct UnkStruct_0229e54c *, int);
extern int func_ov002_02207f60(struct UnkStruct_0229e54c *);
extern int func_ov002_02207f3c(struct UnkStruct_0229e54c *, int);
extern void func_ov100_0229e4fc(struct UnkStruct_0229e54c *);

void func_ov100_0229e54c(struct UnkStruct_0229e54c *this)
{
    int zero = 0;

    if (func_ov002_02207f3c(this, 0)) {
        func_020027f0(4);
        func_ov100_0229c2a0(this, 0x80);
        func_ov002_02207f04(this, 8, zero, zero, 0x30);
        func_ov002_02207e80(this, 6, zero, zero);
        func_ov002_02208090(this, 6);
        func_ov100_0229e4fc(this);
    } else {
        func_ov002_02207e80(this, 4, zero, zero);
        this->unk_28C8 = func_ov002_02207f60(this);
    }
}
