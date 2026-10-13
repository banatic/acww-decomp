/* func_ov109_0229c988 @ 0x0229c988, 0x68 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c988 {
    char pad_00[0xcc];
    char unk_CC;
    char pad_CD[0x218c - 0xcd];
    char unk_218C;
    char pad_218D[0x29d1 - 0x218d];
    unsigned char unk_29D1;
} UnkStruct_0229c988;

extern int func_ov109_0229cbd4(UnkStruct_0229c988 *p, unsigned char c);
extern int func_ov109_0229cb9c(UnkStruct_0229c988 *p, unsigned char c);
extern int func_0206fe54(int b);
extern void func_0208aa60(void *dst, int a, int b);
extern int func_ov109_0229ccb4(UnkStruct_0229c988 *p, unsigned char c);
extern int func_ov109_0229cc98(UnkStruct_0229c988 *p, unsigned char c);
extern void func_ov094_0229abb8(void *dst, void *src, int val);

void func_ov109_0229c988(UnkStruct_0229c988 *p)
{
    int x;
    int b;
    int y;
    int val;

    x = func_ov109_0229cbd4(p, p->unk_29D1) - 0x6d;
    b = func_ov109_0229cb9c(p, p->unk_29D1);
    y = b - 0x78;
    if (func_0206fe54(b)) {
        y -= 8;
    }
    func_0208aa60(&p->unk_218C, x, y);
    if (func_ov109_0229ccb4(p, p->unk_29D1)) {
        val = func_ov109_0229cc98(p, p->unk_29D1);
        func_ov094_0229abb8(&p->unk_CC, &p->unk_218C, val);
    }
}
