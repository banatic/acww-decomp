/* func_0207eaf4 @ 0x0207eaf4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996f8(void);
extern int func_0204bcdc(void);
extern void *func_0204bc64(void *p);

int func_0207eaf4(void)
{
    unsigned short *ptr = func_020996f8();
    if (func_0204bcdc()) {
        unsigned short local = 0x13c1;
        void *a = func_0204bc64(ptr);
        void *b = func_0204bc64(&local);
        if (a != b) {
            return 0;
        }
        return 1;
    } else {
        if (*ptr == 0x13c1) {
            return 1;
        }
        return 0;
    }
}
