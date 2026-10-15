/* func_0200f814 @ 0x0200f814, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(int);
extern int func_020997a8(int);
extern void func_0209e474(void *);
extern void MI_CpuCopy8(void *, void *, int);
extern int func_0209e3ac(void *, void *, int);

struct UnkStruct_0200f814 {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
};

int func_0200f814(int a, void *b, struct UnkStruct_0200f814 *dst)
{
    volatile unsigned short arr[3];

    arr[0] = (unsigned short) func_020997a8(func_02011368(a));
    arr[2] = arr[0];
    arr[1] = arr[2];
    func_0209e474(b);
    MI_CpuCopy8(b, dst, 8);
    dst->unk_05 = (unsigned char) (((unsigned int) arr[1] << 25) >> 25);
    dst->unk_04 = (unsigned char) (((unsigned int) arr[1] << 21) >> 28);
    dst->unk_03 = (unsigned char) (((unsigned int) arr[1] << 16) >> 27);
    return func_0209e3ac(b, dst, 0x3f);
}
