/* func_ov096_0229dce0 @ 0x0229dce0, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022090e4(void *ptr, int a);
extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char a);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_0208e4c0(void *ptr, int a);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    char pad_00[0xbb];
    unsigned char unk_BB;
    unsigned char unk_BC;
    char pad_BD[0x2500 - 0xbd];
    char unk_2500[0x64];
    char unk_2564[1];
} UnkStruct_0229dce0;

void func_ov096_0229dce0(UnkStruct_0229dce0 *p)
{
    int v1, v2;
    p->unk_BB = 0x22;
    p->unk_BC = func_ov002_022090e4(p->unk_2564, 1);
    v1 = func_ov002_02208ae4(p->unk_2564);
    v2 = func_ov002_02208ad8(p->unk_2564, p->unk_BC);
    func_ov002_0220a0b4(p->unk_2500, v1, v2);
    func_0208e4c0(p->unk_2500, 8);
    func_ov002_02208098((void *) (p), 30);
}
