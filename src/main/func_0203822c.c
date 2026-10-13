/* func_0203822c @ 0x0203822c, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020382b8(void *p);
extern void func_02038208(void *p);

typedef struct {
    unsigned char pad_00[192];
    int unk_C0;
    unsigned char pad_C4[5];
    unsigned char unk_C9;
} UnkStruct_0203822c;

void func_0203822c(UnkStruct_0203822c *p)
{
    if (p->unk_C9 == 0) {
        func_020382b8(p);
    } else {
        p->unk_C0--;
        if (p->unk_C0 <= 0) {
            func_02038208(p);
        }
    }
}
