/* func_ov107_0229cf08 @ 0x0229cf08, 0x50 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb8];
    unsigned char byte;
    char pad_B9[0x21fb];
    int unk_22B4;
} UnkStruct_0229cf08;

extern int func_ov107_0229cec4(UnkStruct_0229cf08 *p);
extern int func_ov107_0229ceb4(UnkStruct_0229cf08 *p);
extern void func_ov107_0229ccc8(UnkStruct_0229cf08 *p);
extern void func_ov002_0220a0b4(int *ptr, int a, int b);
extern void func_ov002_0220a374(int *ptr, int arg);

void func_ov107_0229cf08(UnkStruct_0229cf08 *p)
{
    int a = func_ov107_0229cec4(p);
    int b = func_ov107_0229ceb4(p);
    func_ov002_0220a0b4(&p->unk_22B4, a, b);
    if (p->byte == 15) {
        func_ov002_0220a374(&p->unk_22B4, 7);
    } else {
        func_ov002_0220a374(&p->unk_22B4, 1);
    }
    func_ov107_0229ccc8(p);
}
