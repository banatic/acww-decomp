/* func_ov068_02266968 @ 0x02266968, 0x5c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02266a00(void *a, int b, int c);
extern int func_ov068_02266a70(void *a, void *b, int c, void *d, int e);
extern void func_ov068_02266c70(void *a, void *b);
extern void func_0201ad78(void *a, void *b);

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
} FuncStruct5;

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char pad_5C[0x3b0];
    int unk_40C;
} FuncStruct4;

void func_ov068_02266968(FuncStruct5 *r5, FuncStruct4 *r4)
{
    unsigned char buf[0x10];

    if (func_ov068_02266a00(r5, r5->unk_0C, r5->unk_10)) {
        if (func_ov068_02266a70(r5, buf, r5->unk_0C, (char *) r4 + 0x5c, r4->unk_40C)) {
            func_0201ad78((char *) r4 + 0x3b0, buf);
        } else {
            func_ov068_02266c70(r5, r4);
        }
    } else {
        func_ov068_02266c70(r5, r4);
    }
}
