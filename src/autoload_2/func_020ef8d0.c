/* func_020ef8d0 @ 0x020ef8d0, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ef8d0 {
    unsigned char pad_00[9];
    unsigned char flags;
};

extern void OS_Terminate(struct UnkStruct_020ef8d0 *p, int bit, int mode);

void func_020ef8d0(struct UnkStruct_020ef8d0 *p, int bit, int mode)
{
    if (p == 0) {
        OS_Terminate(p, bit, mode);
    }
    if (mode == 1) {
        p->flags |= (1u << bit);
    } else {
        p->flags &= ~(1u << bit);
    }
}
