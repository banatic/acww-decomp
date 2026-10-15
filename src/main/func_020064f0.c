/* func_020064f0 @ 0x020064f0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c7864[];
extern void func_0208ffcc(void);
extern void func_0208ffc0(void);
extern void func_0208ffd8(void);
extern void func_0200f234(void *);

struct UnkStruct_020064f0 {
    unsigned char pad_00[0x170];
    int unk_170;
};

void func_020064f0(struct UnkStruct_020064f0 *p, int index)
{
    unsigned char b = data_020c7864[index];

    if (b != 0) {
        switch (p->unk_170) {
            case 1:
                func_0208ffcc();
                break;
            case 2:
                func_0208ffc0();
                break;
            default:
                func_0208ffd8();
                break;
        }
    } else {
        func_0200f234(p);
    }
}
