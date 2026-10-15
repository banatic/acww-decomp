/* func_020371c8 @ 0x020371c8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_02036648(void);
extern void func_020371f0(void *);
extern void func_02037210(void *);

struct UnkStruct_020371c8 {
    unsigned char pad_00[8];
    unsigned int unk_08;
};

void func_020371c8(struct UnkStruct_020371c8 *p)
{
    unsigned char b;
    b = func_02036648()[7];
    if (b != p->unk_08) {
        func_020371f0(p);
        p->unk_08 = b;
        func_02037210(p);
    }
}
