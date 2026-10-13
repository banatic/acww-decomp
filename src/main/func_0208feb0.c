/* func_0208feb0 @ 0x0208feb0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *p);
extern void func_0208fdc8(void *p);

struct UnkStruct_0208feb0 {
    char pad_00[0x0c];
    int unk_0C;
    int unk_10;
    char unk_14[0x14];
    unsigned char flag_28;
};

void func_0208feb0(struct UnkStruct_0208feb0 *p)
{
    if (p->flag_28 != 0) {
        func_0208a0c8(&p->unk_14[0]);
    }
    if (p->unk_0C != p->unk_10) {
        func_0208fdc8(p);
        p->unk_10 = p->unk_0C;
    }
}
