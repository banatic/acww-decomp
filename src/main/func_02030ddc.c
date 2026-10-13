/* func_02030ddc @ 0x02030ddc, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Elem {
    unsigned char pad_00[0x120];
    int unk_120;
    int unk_124;
    int unk_128;
    unsigned char pad_12C[0x130 - 0x128 - 4];
    unsigned char unk_130;
    unsigned char pad_131[0x138 - 0x130 - 1];
};

extern struct Elem data_021c31ec[];

extern int func_02030c34(int);
extern void func_02030e4c(int);

int func_02030ddc(unsigned int a0, unsigned int a1, int a2, int a3)
{
    struct Elem *e = &data_021c31ec[a3];
    int result = 1;

    func_02030c34(a3);

    if (a0 <= 6) {
        e->unk_124 = (unsigned char) a0;
    } else {
        result = 0;
    }

    if (a1 <= 6) {
        e->unk_128 = (unsigned char) a1;
    } else {
        result = 0;
    }

    e->unk_120 = a2;
    e->unk_130 = 0;

    func_02030e4c(0);

    return result;
}
