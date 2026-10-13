/* func_ov146_02299d84 @ 0x02299d84, 0x68 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuClear16(unsigned short a, char *b, unsigned int c);
extern void MIi_CpuCopy16(char *dst, char *src, unsigned int size);
extern void func_ov146_02299660(char *obj, int param);

void func_ov146_02299d84(char *obj)
{
    volatile unsigned short tmp = 16;
    int i;

    MIi_CpuClear16(tmp, obj + 0xd8a, 0x800);

    for (i = 0; i < 7; i++) {
        int sum = *(short *) (obj + 0xae) + i;
        int rem = sum % 7;
        char *dst = obj + 0x58a + ((rem * 2 + 7) * 64);
        char *src = obj + 0xd8a + ((sum & 0xf) * 128);
        MIi_CpuCopy16(dst, src, 128);
    }

    func_ov146_02299660(obj, 2);
}
