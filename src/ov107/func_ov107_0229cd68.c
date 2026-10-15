/* func_ov107_0229cd68 @ 0x0229cd68, 0x64 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *ptr, int a);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char a);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    char pad_00[0xbc];
    unsigned char unk_BC;
    unsigned char unk_BD;
    char pad_BE[0x21f6];
    char unk_22B4[0x64];
    char unk_2318[1];
} UnkStruct_0229cd68;

void func_ov107_0229cd68(UnkStruct_0229cd68 *p)
{
    int v1, v2;
    p->unk_BC = 0x4;
    p->unk_BD = func_ov002_022090e4(p->unk_2318, 1);
    v1 = func_ov002_02208ae4(p->unk_2318);
    v2 = func_ov002_02208ad8(p->unk_2318, p->unk_BD);
    func_ov002_0220a0b4(p->unk_22B4, v1, v2);
    func_0208e4c0(p->unk_22B4, 8);
    func_ov002_02208098((void *) (p), 12);
}
