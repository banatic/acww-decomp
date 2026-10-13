/* func_020955e0 @ 0x020955e0, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984fc(void *obj);
extern void func_02099704(void *ctx, void *p);
extern void func_020996d4(void *ctx, void *p);
extern void func_020996ec(void *ctx, void *p);
extern void *func_02096718(void *obj);
extern void func_02010680(void *obj, void *p);
extern void func_0201063c(void *obj);
extern void func_020103c0(void *obj, unsigned short *buf);
extern int func_020112e4(void *obj);
extern int func_020112d0(void *obj);
extern void func_020100e8(void *obj, unsigned short *buf, int a, int b, int c);

int func_020955e0(void *p, int mode, void *obj)
{
    void *ctx;
    unsigned short buf[2];
    int a, b;

    ctx = func_020984fc(obj);
    if (ctx == 0) {
        return 0;
    }

    switch (mode) {
        case 0:
            func_02099704(ctx, p);
            break;
        case 1:
            func_020996d4(ctx, p);
            break;
        case 2:
            func_020996ec(ctx, p);
            break;
        default:
            break;
    }

    obj = func_02096718(obj);
    if (obj == 0) {
        return 0;
    }
    if (*(int *) ((char *) obj + 0x704) >= 0xa1) {
        return 0;
    }

    switch (mode) {
        case 0:
            func_02010680(obj, p);
            func_0201063c(obj);
            break;
        case 1:
            buf[0] = *(unsigned short *) p;
            func_020103c0(obj, buf);
            break;
        case 2:
            buf[1] = *(unsigned short *) p;
            a = func_020112e4(obj);
            b = func_020112d0(obj);
            func_020100e8(obj, &buf[1], a, b, 0);
            break;
        default:
            break;
    }
    return 1;
}
