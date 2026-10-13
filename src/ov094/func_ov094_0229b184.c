/* func_ov094_0229b184 @ 0x0229b184, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov094_0229bddc[];

int func_ov094_0229b184(unsigned char *p)
{
    unsigned char idx = p[0x26];
    if (idx >= 4) {
        return 10;
    }
    return data_ov094_0229bddc[idx];
}
