/* func_02051d44 @ 0x02051d44, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern void *data_021c80bc;
extern void *func_ov004_0223cd50(void **pp);
extern void *func_ov004_0223cc10(void *p, int x, int y, int z);
extern void *func_0204f5e0(void *p, int a, int b, int c, int d, int e);
extern int func_ov004_0220fde0(void *p);
extern int func_0205395c(int v);
extern int func_0204bcdc(void *p);
extern int func_0204bc64(const void *p);

int func_02051d44(int x, int y)
{
    unsigned int flag = (data_020e54a8 == 1);
    if (flag) {
        void *p = data_021c80bc;
        void *q;
        int success;

        q = func_ov004_0223cc10(func_ov004_0223cd50(&data_021c80bc), x, y, 0);
        if (p == 0 || q == 0) {
            goto fail;
        }

        {
            int qx = x >> 4;
            int qy = y >> 4;
            int ry = y - (qy << 4);
            int rx = x - (qx << 4);
            p = func_0204f5e0(p, qx, qy, rx, ry, 1);
        }

        if (func_0205395c(func_ov004_0220fde0(q)) != 1) {
            goto fail;
        }
        if (p == 0) {
            goto fail;
        }

        if (func_0204bcdc(p) != 0) {
            unsigned short tmp = 0xfff1;
            success = (func_0204bc64(p) == func_0204bc64(&tmp)) ? 1 : 0;
        } else {
            success = (*(unsigned short *) p == 0xfff1) ? 1 : 0;
        }

        if (success) {
            return 1;
        }
    }
fail:
    return 0;
}
