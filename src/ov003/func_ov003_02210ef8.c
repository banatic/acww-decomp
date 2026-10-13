/* func_ov003_02210ef8 @ 0x02210ef8, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02210ef8 {
    unsigned char x, y, z;
} UnkStruct_02210ef8;

typedef struct Src {
    char pad_00[0xc];
    UnkStruct_02210ef8 sub;
} Src;

typedef struct UnkStruct_02210ef8_2 {
    char pad_00[0x7d4];
    unsigned char unk_7D4[3];
    char pad_7D7[0x8f0 - 0x7d4 - 3];
    unsigned char unk_8F0[3];
} UnkStruct_02210ef8_2;

extern void func_ov003_02210f50(unsigned char *p0, int p1, int p2, int p3);
extern void func_020109a0(int, int, int, int);
extern void func_0200f328(int, int);

void func_ov003_02210ef8(UnkStruct_02210ef8_2 *self, Src *src)
{
    UnkStruct_02210ef8 *p = &src->sub;
    unsigned char *fA = self->unk_7D4;
    unsigned char t2 = p->z;
    unsigned char t0 = src->sub.x;
    unsigned char t1 = p->y;
    fA[2] = t2;
    fA[0] = t0;
    fA[1] = t1;
    func_ov003_02210f50(self->unk_8F0, t0, t1, t2);
    func_020109a0((int) self, 0x50, 3, 0);
    func_0200f328((int) self, 0x4f);
}
