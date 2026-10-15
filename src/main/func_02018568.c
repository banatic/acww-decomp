/* func_02018568 @ 0x02018568, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02019de4(void *a);
extern void func_0201b1a4(void *a, void *b, int c, int d, int e);
extern void func_0201b044(void *a, void *b);
extern void func_0201afd4(void *a, void *b);
extern void func_0201b350(void *a, int b);
extern void *func_ov004_0222bf74(void *a, void *b, void *c, void *d, void *e);
extern void *func_02095a4c(void *a, void *b, void *c, void *d, void *e);
extern void func_02019af0(void *a, int b);

extern char data_021fbee8[];

struct UnkStruct_02018568 {
    char pad_00[0x1c];
    unsigned short unk_1C;
    char pad_1E[0x22 - 0x1e];
    unsigned short unk_22;
    unsigned short unk_24;
    char pad_26[0x2c - 0x26];
    unsigned int unk_2C;
    unsigned int unk_30;
};

int func_02018568(void *p0, void *p1)
{
    struct UnkStruct_02018568 *r4;
    r4 = func_02019de4(p0);
    func_0201b1a4((char *) p1 + 0x350, p1, 0, 0, r4->unk_1C);
    func_0201b044((char *) p1 + 0x350, data_021fbee8);
    func_0201afd4((char *) p1 + 0x350, data_021fbee8);
    func_0201b350((char *) p1 + 0x3aa, -2);
    if (r4->unk_30 == 1) {
        func_ov004_0222bf74(&r4->unk_22, &r4->unk_24, &r4->unk_2C, &r4->unk_30, p1);
        *(unsigned char *) ((char *) p0 + 0x98) = 13;
    } else {
        func_02095a4c(&r4->unk_22, &r4->unk_24, &r4->unk_2C, &r4->unk_30, p1);
        *(unsigned char *) ((char *) p0 + 0x98) = 0;
    }
    func_02019af0(p0, 0);
    return 1;
}
