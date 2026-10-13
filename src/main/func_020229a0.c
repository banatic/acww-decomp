/* func_020229a0 @ 0x020229a0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202e118(void *buf, int arg);
extern void func_02022bbc(void *p, int a, void *b);
extern char data_020c8d30;

struct UnkStruct_020229a0 {
    unsigned char pad_00[0x100];
    int unk_100;
};

int func_020229a0(struct UnkStruct_020229a0 *p)
{
    unsigned char buf[8];
    volatile unsigned short *vp;
    unsigned short a, b;
    int cond;

    func_0202e118(buf, p->unk_100);

    cond = 0;
    vp = (volatile unsigned short *) buf;
    b = vp[0];
    a = vp[0];

    if (a >= 0x1369 && b <= 0x1369) {
        cond = 1;
    }

    if (cond) {
        func_02022bbc(p, 2, &data_020c8d30);
        return 1;
    }
    return 0;
}
