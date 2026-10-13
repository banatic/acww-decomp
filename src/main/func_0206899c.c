/* func_0206899c @ 0x0206899c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020045dc(void);

typedef struct {
    char pad_00[0x24];
    int unk_24;
} UnkStruct_0206899c;

void func_0206899c(UnkStruct_0206899c *p)
{
    if (p->unk_24 != 5) {
        func_020045dc();
    }
    p->unk_24 = 5;
}
