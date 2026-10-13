/* func_ov051_022606c8 @ 0x022606c8, 0x64 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov051_022614c8[];
extern unsigned char data_ov051_022614c4[];
extern int data_ov051_022615c0;

extern int func_020a12ac(void);
extern void func_020984e8(void);
extern void func_02099870(void);
extern int func_020950c0(void);
extern void func_0206844c(int, unsigned char *, int);

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0xb0 - 0x44];
    int *unk_B0;
} UnkStruct_022606c8;

void func_ov051_022606c8(UnkStruct_022606c8 *p, int p1)
{
    unsigned char ch;
    int result;

    if (func_020a12ac() != 0) {
        func_020984e8();
        func_02099870();
        result = *(unsigned char *) (data_ov051_022614c8 + 2 * p1 + func_020950c0());
    } else {
        result = data_ov051_022614c4[p1];
    }
    ch = (unsigned char) result;
    func_0206844c(p->unk_40, &ch, data_ov051_022615c0);

    if (p1 == 1) {
        *(int *) ((char *) p->unk_B0 + 0x714) += 4;
    }
}
