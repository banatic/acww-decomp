/* func_02016024 @ 0x02016024, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015da0(int a, int c);
extern void *func_0201c274(void);
extern int func_02015ff4(void);
extern int func_02019e00(void *p);
extern void func_02019c90(void *p, int n, unsigned char c, unsigned short s);
extern unsigned short data_020c80f8;

typedef struct {
    char pad_00[0x564];
    int unk_564;
} UnkStruct_02016024;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
} UnkStruct_02016024_2;

void func_02016024(int a, int b, int c)
{
    UnkStruct_02016024 *r4;
    UnkStruct_02016024_2 *r6;

    r4 = (UnkStruct_02016024 *) func_02015da0(a, c);
    if (r4 == 0) {
        return;
    }
    r6 = (UnkStruct_02016024_2 *) func_0201c274();
    if (r6 == 0) {
        return;
    }
    if (func_02015ff4() != 0) {
        return;
    }
    if (r6->unk_5C == b) {
        if (func_02019e00(&r4->unk_564) == 8) {
            return;
        }
    }
    func_02019c90(&r4->unk_564, 2, (unsigned char) b, data_020c80f8);
    r6->unk_5C = b;
}
