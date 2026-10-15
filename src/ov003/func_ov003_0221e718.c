/* func_ov003_0221e718 @ 0x0221e718, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203edd0(void *);
extern int func_ov003_0221e6a0(void *);
extern int func_020ea990(void *, void *);
extern int func_020e8b4c(int, int);

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x32];
    short unk_8E;
    unsigned char pad_90[0xa4];
    unsigned char unk_134;
} UnkStruct_0221e718;

int func_ov003_0221e718(UnkStruct_0221e718 *a, UnkStruct_0221e718 *b)
{
    func_0203edd0(a);
    if (!func_ov003_0221e6a0(a)) {
        return 0;
    }
    if (a->unk_134 == 2 && b != 0 && func_020ea990((char *) b + 0x5c, (char *) a + 0x5c) < 0x2333 &&
        func_020e8b4c((short) (a->unk_8E + 0x8000), b->unk_8E) < 0x1200) {
        return 1;
    }
    return 0;
}
