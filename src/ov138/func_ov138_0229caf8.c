/* func_ov138_0229caf8 @ 0x0229caf8, 0x84 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov138_0229c574(void *, int);
extern int func_ov134_02299b70(void *);
extern int func_ov134_022997b0(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov138_0229c8f8(void *);
extern void func_ov138_0229c630(void *);
extern void func_ov138_0229c978(void *);
extern void func_ov138_0229c950(void *);
extern void func_ov138_0229c924(void *, int);

void func_ov138_0229caf8(void *a0)
{
    if (func_0208e484((char *) a0 + 0x98)) {
        if (func_ov138_0229c574(a0, 2)) {
            if (func_ov134_02299b70((char *) a0 + 0x2c8)) {
                func_ov002_02208098((void *) (a0), 6);
            } else if (func_ov134_022997b0((char *) a0 + 0x2c8)) {
                func_ov138_0229c8f8(a0);
            } else {
                func_ov002_02208098((void *) (a0), 5);
                func_ov138_0229c630(a0);
            }
        } else {
            unsigned char v = *((unsigned char *) a0 + 0x95);
            if (v == 3) {
                func_ov138_0229c978(a0);
            } else if (v == 4) {
                func_ov138_0229c950(a0);
            } else {
                func_ov138_0229c924(a0, v);
            }
        }
    }
}
