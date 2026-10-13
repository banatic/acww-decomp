/* func_02015f38 @ 0x02015f38, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b5630(void *);
extern void func_020b45d0(void *, int, int, int, int, int);
extern void func_020a8228(void *);
extern void func_020b4a20(void *, void *, void *);
extern void func_020a89dc(void *, void *);
extern void func_020a8210(void *);
extern void func_020683b4(int, int, void *, int);
extern void func_020b5618(void *);

struct UnkStruct_02015f38 {
    char pad_00[0x40];
    int unk_40;
};

extern unsigned char data_020d8d0c[];

void func_02015f38(struct UnkStruct_02015f38 *p1, int p2, int p3, int p4, unsigned char p5, int p6, int p7)
{
    int saved_arg4;
    unsigned char temp;
    int buf1[0x10];
    int buf2[0x17];
    int r4;

    saved_arg4 = p4;
    if (p2 < 0) {
        return;
    }

    func_020b5630(buf1);
    r4 = 7;
    func_020b45d0(buf1, p2, saved_arg4, p6, p7, 0);
    if (p5 != 0) {
        func_020a8228(buf2);
        temp = 0x1c;
        func_020b4a20(buf2, &temp, (void *) data_020d8d0c);
        func_020a89dc(buf1, buf2);
        r4 = 0;
        func_020a8210(buf2);
    }
    func_020683b4(p1->unk_40, p3, buf1, r4);
    func_020b5618(buf1);
}
