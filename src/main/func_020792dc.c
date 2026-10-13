/* func_020792dc @ 0x020792dc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1d];
    unsigned char flags;
    char pad_1E[0x2c - 0x1d - 1];
} UnkStruct_020792dc;

extern void func_02079540(UnkStruct_020792dc *p, int a);
extern void func_020794c0(UnkStruct_020792dc *p, int a);
extern void func_020794a4(UnkStruct_020792dc *p, int a);
extern void func_0207944c(UnkStruct_020792dc *p);
extern void func_02079438(void);

void func_020792dc(UnkStruct_020792dc *p)
{
    int i = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    do {
        func_02079540(p, a);
        p->flags &= ~1;
        func_020794c0(p, b);
        func_020794a4(p, c);
        p->flags &= ~4;
        func_0207944c(p);
        func_02079438();
        p++;
        i++;
    } while (i < 8);
}
