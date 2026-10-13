/* func_0203736c @ 0x0203736c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[6];
    unsigned char unk_06;
    unsigned char unk_07;
    unsigned int unk_08;
} UnkStruct_0203736c;
unsigned int func_0203736c(UnkStruct_0203736c *p, unsigned int h2, unsigned int m2, unsigned int s2, unsigned int h3,
                           unsigned int m3, unsigned int s3)
{
    unsigned int t1 = p->unk_08 + (p->unk_07 * 3600 + p->unk_06 * 60);
    unsigned int t2 = s2 + (h2 * 3600 + m2 * 60);
    unsigned int t3 = s3 + (h3 * 3600 + m3 * 60);
    unsigned int r = 0;
    if (t2 <= t3) {
        if (t1 >= t2 && t1 < t3) {
            r = 1;
        }
    } else {
        if (t1 >= t2 || t1 < t3) {
            r = 1;
        }
    }
    return r;
}
