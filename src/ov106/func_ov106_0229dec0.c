/* func_ov106_0229dec0 @ 0x0229dec0, 0x54 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f9c(void *);
extern void func_ov106_0229ce0c(void *);
extern int func_ov106_0229d29c(void *, int argument1);
extern void func_ov106_0229cea8(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov094_022999d8(void);
extern void func_ov106_0229d518(void *, unsigned char, int);

void func_ov106_0229dec0(unsigned char *arg)
{
    unsigned char ba;
    unsigned char b8;

    if (func_ov002_02209f9c(arg + 0x22a0) == 0) {
        ba = arg[0xba];
        b8 = arg[0xb8];
        if (b8 == ba) {
            func_ov106_0229d29c(arg, ba);
            func_ov106_0229cea8(arg);
            func_ov002_02208098((void *) (arg), 7);
            func_ov094_022999d8();
        } else {
            func_ov106_0229d518(arg, ba, 4);
        }
    } else {
        func_ov106_0229ce0c(arg);
    }
}
