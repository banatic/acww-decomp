/* func_0205ef28 @ 0x0205ef28, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205f130(void *a, unsigned char b);
extern void func_02054cf4(int a, void *b);
extern void func_0205ef5c(void);

typedef struct {
    char pad_00[0x4];
    void *unk_04;
    char pad_08[0x1C];
    void (*func24)(void);
    char pad_28[0x6A];
    unsigned char flag92;
} UnkStruct_0205ef28;

typedef struct {
    char pad_00[0x2C];
    unsigned char *unk_2C;
} InnerStruct;

extern unsigned char data_021ca16c[];

void func_0205ef28(UnkStruct_0205ef28 *p)
{
    InnerStruct *inner;
    unsigned char b;
    int ret;

    inner = (InnerStruct *) p->unk_04;
    if (inner->unk_2C) {
        b = *inner->unk_2C;
        ret = func_0205f130((void *) data_021ca16c, b);
        func_02054cf4(ret, p);
    }
    p->func24 = &func_0205ef5c;
    p->flag92 = 1;
}
