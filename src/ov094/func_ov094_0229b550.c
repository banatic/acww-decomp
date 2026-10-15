/* func_ov094_0229b550 @ 0x0229b550, 0x78 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b1e8(void *a, int b);
extern int func_020896b8(int a, void *b, int c, int d, int e, int f, int g);

struct UnkStruct_0229b550 {
    int pad_00;
    unsigned short unk_04;
};

struct UnkStruct_0229b550_2 {
    char pad_00[0x20];
    int unk_20;
};

extern struct UnkStruct_0229b550 data_ov094_0229c0f4;
extern unsigned short data_ov094_0229c134[];

void func_ov094_0229b550(struct UnkStruct_0229b550_2 *p0, int p1, int p2, int p3, int p4, int p5)
{
    int ret = func_ov094_0229b1e8(p0, p4);
    if (ret == -1) {
        return;
    }

    data_ov094_0229c0f4.unk_04 = (data_ov094_0229c0f4.unk_04 & 0xffff0fff) | ((((unsigned char) p3) & 0xf) << 12);
    data_ov094_0229c0f4.unk_04 = (data_ov094_0229c0f4.unk_04 & 0xfffffc00) | (data_ov094_0229c134[ret] & 0x3ff);

    func_020896b8(1, &data_ov094_0229c0f4, p1, p2, -1, p0->unk_20, p5);
}
