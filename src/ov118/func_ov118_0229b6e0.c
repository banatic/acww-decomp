/* func_ov118_0229b6e0 @ 0x0229b6e0, 0x98 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void MIi_CpuCopy16(void *, void *, int);
extern void *func_ov118_0229b3b0(void *);
extern unsigned int func_ov118_0229b68c(void *self, unsigned int x, int idx);
extern void func_ov118_0229a450(void *, int);

void func_ov118_0229b6e0(char *base)
{
    int i;
    int srcIdx, dstIdx;
    unsigned char *saved;

    MIi_CpuCopy16(base + 0x1f24, base + 0x1724, 0x800);
    saved = (unsigned char *) func_ov118_0229b3b0(base);

    for (i = 0; i < 13; i++) {
        srcIdx = (func_ov118_0229b68c(base, saved[i], i) << 6) + 0x13;
        dstIdx = (i << 6) + 0x13;

        *(unsigned short *) (base + (dstIdx * 2) + 0x1724) = *(unsigned short *) (base + (srcIdx * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 1) * 2) + 0x1724) = *(unsigned short *) (base + ((srcIdx + 1) * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 0x20) * 2) + 0x1724) =
            *(unsigned short *) (base + ((srcIdx + 0x20) * 2) + 0x1f24);
        *(unsigned short *) (base + ((dstIdx + 0x21) * 2) + 0x1724) =
            *(unsigned short *) (base + ((srcIdx + 0x21) * 2) + 0x1f24);
    }

    func_ov118_0229a450(base, 2);
}
