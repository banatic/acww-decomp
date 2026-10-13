/* func_ov122_0229f4e0 @ 0x0229f4e0, 0x60 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f6c54;
extern void func_ov122_0229f468(void *p, int v);
extern void func_ov002_0220a4c8(void *p);

void func_ov122_0229f4e0(char *p)
{
    int v0, v1, diff, r5;

    v0 = *(unsigned char *) (p + 0xb1);
    v1 = (data_021f6c54 - *(unsigned char *) (p + 0xb0)) >> 1;
    r5 = v0 + (v1 << 2);
    if (r5 < 0) {
        r5 = 0;
    }
    if (r5 > 0x58) {
        r5 = 0x58;
    }
    func_ov122_0229f468(p, r5);
    diff = *(unsigned char *) (p + 0xaf) - r5;
    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(p + 0x4010);
        *(unsigned char *) (p + 0xaf) = r5;
    }
}
