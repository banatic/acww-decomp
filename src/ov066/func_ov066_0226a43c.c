/* func_ov066_0226a43c @ 0x0226a43c, 0x58 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

struct UnkStruct_0226a43c;
typedef struct UnkStruct_0226a43c_2 {
    unsigned char pad_00;
    unsigned char unk_01;
    unsigned char pad_02[10];
    void (*unk_0C)(struct UnkStruct_0226a43c *);
} UnkStruct_0226a43c_2;

typedef struct UnkStruct_0226a43c {
    unsigned short unk_00;
    unsigned char pad_02[0x12];
    UnkStruct_0226a43c_2 *unk_14;
} UnkStruct_0226a43c;

void func_ov066_0226a43c(UnkStruct_0226a43c *p)
{
    UnkStruct_0226a43c_2 *q = p->unk_14;
    if (p->unk_00 != 1) {
        return;
    }
    q->unk_01--;
    p->unk_00 = 0;
    if (q->unk_0C) {
        q->unk_0C(p);
    }
}
