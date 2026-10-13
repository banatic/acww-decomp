/* func_ov003_02212728 @ 0x02212728, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f794(char *buf, unsigned char a, unsigned char b);
extern void func_02010d88(void *p, char *buf, int c, int d);
extern void func_02089fc8(void *p);

struct UnkStruct_02212728 {
    char pad_00[0x1c4];
    unsigned char unk_1C4;
    char pad_1C5[0x60f];
    unsigned char arr[2];
};

void func_ov003_02212728(struct UnkStruct_02212728 *p)
{
    char buf[16];
    unsigned char *bp = &p->arr[0];
    func_0204f794(buf, *bp, *(bp + 1));
    func_02010d88(p, buf, 0xf33, 0x1000);
    func_02089fc8(&p->unk_1C4);
}
