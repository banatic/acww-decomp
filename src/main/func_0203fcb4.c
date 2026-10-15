/* func_0203fcb4 @ 0x0203fcb4, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern int func_0203fae4(void);
extern int func_0203fec4(void *out, const void *in, int param);
extern int func_0203fd38(void *out, const void *src, const void *param);
extern const unsigned char data_021c74d0[3];
extern const unsigned char data_021c74d4[4];

int func_0203fcb4(void *out, const unsigned char *src, int flag)
{
    unsigned char buf0[8];
    unsigned char buf1[8];
    unsigned char buf2[8];
    unsigned char buf3[0x58];
    int ret = 0;

    if (src[5] == data_021c74d0[2] && src[4] == data_021c74d0[1] && src[3] == data_021c74d0[0]) {
        if (flag == 0 && func_0203fae4() != 0) {
            // empty
        } else {
            MI_CpuCopy8(src, buf0, 8);
            ret = func_0203fd38(out, buf0, data_021c74d4);
        }
    } else {
        MI_CpuCopy8(src, buf1, 8);
        func_0203fec4(buf3, buf1, 0);
        MI_CpuCopy8(src, buf2, 8);
        ret = func_0203fd38(out, buf2, buf3);
    }
    return ret;
}
