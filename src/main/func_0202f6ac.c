/* func_0202f6ac @ 0x0202f6ac, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202f8e4(void *, int);
extern int func_0202f688(void *);

struct UnkStruct_0202f6ac {
    unsigned char unk_00[4];
    int unk_04;
    unsigned char unk_08[4];
    int unk_0C;
    unsigned char unk_10[4];
    int unk_14;
    unsigned char unk_18[4];
    int unk_1C;
};

void func_0202f6ac(struct UnkStruct_0202f6ac *a, int b, int c, int d)
{
    func_0202f8e4(&a->unk_04, b);
    func_0202f8e4(&a->unk_0C, c);
    func_0202f8e4(&a->unk_14, d);
    a->unk_1C = func_0202f688(a);
}
