/* func_ov068_02272d64 @ 0x02272d64, 0x50 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ffd070(void *, void *, void *);

void func_ov068_02272d64(void *dst, int cond, void *src)
{
    unsigned int tmp[3];
    unsigned int out[3];
    unsigned char *p;
    unsigned char *q;

    if (cond != 0) {
        return;
    }

    p = *(unsigned char **) ((char *) src + 0xb4);
    q = p + 0x4c;
    tmp[0] = *(unsigned int *) q;
    tmp[1] = *(unsigned int *) (q + 4);
    tmp[2] = *(unsigned int *) (q + 8);

    func_01ffd070(out, (char *) dst + 0x5c, tmp);

    *(unsigned int *) ((char *) dst + 0x2cc) = out[0];
    *(unsigned int *) ((char *) dst + 0x2d0) = out[1];
    *(unsigned int *) ((char *) dst + 0x2d4) = out[2];
}
