/* func_02096d10 @ 0x02096d10, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096d78(void);
extern void *func_02097f14(void *buffer);
extern int func_02065ec0(int);
extern int func_02096de0(void);
extern int func_020644cc(int);
extern int func_02097e38(void *);
extern int func_02096df4(const char *);
extern void func_02097edc(void *, int);

extern unsigned char data_021f36ec;
extern unsigned char data_021f43ec;

void func_02096d10(int param0)
{
    if (param0 <= 0) {
        return;
    }
    if (func_02096d78() != 0) {
        return;
    }
    {
        int n;
        void *p = &data_021f36ec;
        char tmp;
        if (func_02065ec0((int) func_02097f14(p)) != 0) {
            func_02096de0();
            return;
        }
        if (func_020644cc(0xa) != 7) {
            return;
        }
        tmp = (char) data_021f43ec;
        n = func_02097e38(p);
        tmp = (char) n;
        if (func_02096df4(&tmp)) {
            func_02097edc(p, n);
        }
    }
}
