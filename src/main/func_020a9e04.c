/* func_020a9e04 @ 0x020a9e04, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d368(int, int);
extern void func_020ac39c(void *, int, int);
extern void func_020aae14(void *);
extern void func_020aa154(void *);

struct UnkStruct_020a9e04 {
    char pad_00[0xc];
    char sub[0x148];
    char sub154[0x38];
    int unk_18C;
    int unk_190;
    int unk_194;
    char unk_198;
};

void func_020a9e04(struct UnkStruct_020a9e04 *p)
{
    int flag;

    p->unk_198 = 0;
    p->unk_18C += func_0209d368(0x65, 3) + 11;
    p->unk_190 += func_0209d368(0x65, 4) - 11;
    p->unk_194--;
    flag = (p->unk_194 > 0) ? 0 : 1;
    func_020ac39c(p->sub, p->unk_18C, p->unk_190);
    if (flag) {
        func_020aae14(p->sub154);
        func_020aa154(p);
    }
}
