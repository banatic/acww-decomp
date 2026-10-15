/* func_020089dc @ 0x020089dc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *p);
extern int func_02056f28(void *p, int n);
extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_020f1fb4(unsigned int a, int b);
extern int func_0200f328(void *p, int n);

struct UnkStruct020089dc {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x800 - 0x2d0 - 1];
    unsigned int unk_800;
};

extern unsigned char data_021fd1bc[];

void func_020089dc(struct UnkStruct020089dc *p)
{
    func_02010f5c(p);
    if (func_02056f28(&p->unk_2D0, 1)) {
        if (func_02073908(data_020ccf94, p->unk_800)) {
            func_020f1fb4((unsigned int) data_021fd1bc, 0x79);
        } else {
            func_0200f328(p, 0x79);
        }
    }
}
