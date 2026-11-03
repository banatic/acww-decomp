/* mailbox_6: 3 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221e78c @ 0x0221e78c, 0x20 bytes, Thumb
 * func_ov003_0221e788 @ 0x0221e788, 0x4 bytes, Thumb
 * func_ov003_0221e718 @ 0x0221e718, 0x70 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x32];
    short unk_8E;
    unsigned char pad_90[0xa4];
    unsigned char unk_134;
} UnkStruct_0221e718;

extern void func_ov003_0221e4e8(void *a0);
extern int func_020b6590(void);
extern int func_020b7db0(int x, void *y);
extern void func_0203edd0(void *);
extern int func_ov003_0221e6a0(void *);
extern int func_020ea990(void *, void *);
extern int func_020e8b4c(int, int);

int func_ov003_0221e78c(void *a0)
{
    func_020b7db0(((void) (func_ov003_0221e4e8(a0)), func_020b6590()), (char *) a0 + 0x2d8);
    return 1;
}

int func_ov003_0221e788(void)
{
    return 0;
}

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
