/* func_020604c8 @ 0x020604c8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206026c(void *p, int val);
extern int func_ov003_0222aba4(int a);

struct UnkStruct_020604c8 {
    unsigned char pad_00[0x2c];
    int unk_2C;
};

int func_020604c8(struct UnkStruct_020604c8 *p)
{
    int v = p->unk_2C;
    if (v == 0) {
        func_0206026c(p, 7);
        return 0;
    }
    return func_ov003_0222aba4(v);
}
