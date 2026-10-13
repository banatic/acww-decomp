/* func_ov050_02263394 @ 0x02263394, 0x74 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *p);
extern int func_02099640(void);
extern int func_0209abb0(void);
extern void *func_02099710(void *p);
extern int func_0204bcdc(void);
extern int func_0204bc64(void *p);

int func_ov050_02263394(void *p0, unsigned char *p1)
{
    void *obj;
    void *r4;
    int matched;

    obj = func_020984e8(p0);
    func_02099640();
    if (!func_0209abb0()) {
        goto fail;
    }
    if (!obj) {
        goto fail;
    }

    r4 = func_02099710(obj);
    if (func_0204bcdc()) {
        unsigned short local = 0x11a8;
        int a = func_0204bc64(r4);
        int b = func_0204bc64(&local);
        matched = (a == b);
    } else {
        matched = (*(unsigned short *) r4 == 0x11a8);
    }
    if (matched) {
        goto fail;
    }
    p1[4] = 0xe;
    return 1;
fail:
    return 0;
}
