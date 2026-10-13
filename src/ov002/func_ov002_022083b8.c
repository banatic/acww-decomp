/* func_ov002_022083b8 @ 0x022083b8, 0x60 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    int unk_0C;
    unsigned char pad_10[0x18 - 0xc - 4];
    unsigned char dir;
} UnkStruct_022083b8;

extern void func_0200284c(int a, int b, int c);

void func_ov002_022083b8(UnkStruct_022083b8 *p, int a, int b, int c)
{
    switch (p->dir) {
        case 0:
            func_0200284c(a, -b, -(p->unk_0C + c));
            break;
        case 1:
            func_0200284c(a, -b, p->unk_0C - c);
            break;
        case 2:
            func_0200284c(a, p->unk_0C - b, -c);
            break;
        case 3:
            func_0200284c(a, -(p->unk_0C + b), -c);
            break;
    }
}
