/* func_ov125_0229fc24 @ 0x0229fc24, 0x60 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fc24 {
    char pad_00[0x87b];
    unsigned char unk_87B;
};

extern void func_ov002_02208c58(void *a, void *b, int c);
extern int func_ov125_0229fe4c(struct UnkStruct_0229fc24 *self, int b);
extern int func_ov125_0229fe40(struct UnkStruct_0229fc24 *self, int b);
extern void func_ov002_022098ec(void *addr, int a, int b);
extern void func_ov002_0220970c(void *addr, int n);
extern unsigned char *func_ov002_02208098(struct UnkStruct_0229fc24 *self, unsigned char value);

void func_ov125_0229fc24(struct UnkStruct_0229fc24 *self)
{
    int v1, v2;

    func_ov002_02208c58((char *) self + 0x180, (char *) self + 0x568, 0);
    v1 = func_ov125_0229fe4c(self, self->unk_87B) - 0x18;
    v2 = func_ov125_0229fe40(self, self->unk_87B) - 0x10;
    func_ov002_022098ec((char *) self + 0x180, v1, v2);
    func_ov002_0220970c((char *) self + 0x180, 0);
    func_ov002_02208098(self, 7);
}
