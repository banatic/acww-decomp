/* func_02016024 @ 0x02016024, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015da0(int a, int c);
extern void *func_0201c274(void *);
extern int func_02015ff4(void *);
extern int func_02019e00(void *p);
extern int func_02019c90(void *p, int n, unsigned char c, unsigned short s);
extern unsigned short data_020c80f8;

typedef struct {
    char pad_00[0x564];
    int unk_564;
} UnkStruct_02016024;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
} UnkStruct_02016024_2;

int func_02016024(int a, int b, int c)
{
    UnkStruct_02016024 *r4;
    UnkStruct_02016024_2 *r6;
    int result;

    r4 = (UnkStruct_02016024 *) func_02015da0(a, c);
    if (r4 == 0) {
        return (int) r4;
    }
    r6 = (UnkStruct_02016024_2 *) func_0201c274(r4);
    if (r6 == 0) {
        return (int) r6;
    }
    result = func_02015ff4(r6);
    if (result != 0) {
        return result;
    }
    if (r6->unk_5C == b) {
        result = func_02019e00(&r4->unk_564);
        if (result == 8) {
            return result;
        }
    }
    result = func_02019c90(&r4->unk_564, 2, (unsigned char) b, data_020c80f8);
    r6->unk_5C = b;
    return result;
}
