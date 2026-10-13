/* func_020461e0 @ 0x020461e0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020461e0 {
    unsigned char : 3;
    unsigned char kind : 5;
    unsigned char pad_01[7];
    unsigned short unk_08;
};

extern void func_020465b0(struct UnkStruct_020461e0 *p);
extern void func_0204629c(struct UnkStruct_020461e0 *p);

void func_020461e0(struct UnkStruct_020461e0 *p)
{
    if (p->unk_08 == 0xffff) {
        return;
    }

    switch (p->kind) {
        case 4:
        case 10:
        case 22:
        case 25:
            func_020465b0(p);
            break;
        default:
            func_0204629c(p);
            break;
    }
}
