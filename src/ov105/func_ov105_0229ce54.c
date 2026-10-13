/* func_ov105_0229ce54 @ 0x0229ce54, 0x68 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2be];
    unsigned char unk_2BE;
    unsigned char unk_2BF;
    char pad_2C0[0x21e4];
    char thing_24a4[0x64];
    char buf_2508[1];
} UnkStruct_0229ce54;

extern int func_ov002_022090e4(void *, int);
extern int func_ov002_02208ae4(void *);
extern int func_ov002_02208ad8(void *, unsigned char);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_0208e4c0(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov105_0229ce54(UnkStruct_0229ce54 *this)
{
    int a, b;
    this->unk_2BE = 4;
    this->unk_2BF = func_ov002_022090e4(this->buf_2508, 1);
    a = func_ov002_02208ae4(this->buf_2508);
    b = func_ov002_02208ad8(this->buf_2508, this->unk_2BF);
    func_ov002_0220a0b4(this->thing_24a4, a, b);
    func_0208e4c0(this->thing_24a4, 8);
    func_ov002_02208098(this, 0x17);
}
