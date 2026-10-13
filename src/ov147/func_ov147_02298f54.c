/* func_ov147_02298f54 @ 0x02298f54, 0x34 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov147_0229baac[];
extern unsigned int data_ov147_0229f2ac[];

void func_ov147_02298f54(int unused, unsigned int *src, int idx)
{
    unsigned int *mask = data_ov147_0229baac + idx * 8;
    unsigned int *dst = data_ov147_0229f2ac + idx * 8;
    int i;

    for (i = 0; i < 8; i++) {
        *dst++ = *mask & *src;
        src++;
        mask++;
    }
}
