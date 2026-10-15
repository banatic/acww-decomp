/* func_ov112_022a0144 @ 0x022a0144, 0x6c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229f900(void *p);
extern void func_02051bf8(void *p, int size);
extern int func_02051c08(void *dst, void *src, int n);
extern void func_ov112_0229fe60(void *p, int n);
extern void func_ov095_022999f4(void);
extern void func_ov112_0229f488(void *p);

void func_ov112_022a0144(void *arg)
{
    unsigned char b_bf;
    unsigned char b_be;
    unsigned int min;
    unsigned int diff;

    if (func_ov112_0229f900(arg) == 0) {
        return;
    }

    b_bf = *((unsigned char *) arg + 0xbf);
    b_be = *((unsigned char *) arg + 0xbe);
    if (b_be > b_bf) {
        min = b_bf;
        diff = b_be - b_bf;
    } else {
        min = b_be;
        diff = b_bf - b_be;
    }

    func_02051bf8((char *) arg + 0x184, 0x60);
    func_02051c08((char *) arg + 0xC4 + min * 2, (char *) arg + 0x184, diff);
    func_ov112_0229fe60(arg, 0x200);
    asm {
        ldr r0, =0x384
        add r0, arg, r0
    }
    func_ov095_022999f4();
    func_ov112_0229f488(arg);
}
