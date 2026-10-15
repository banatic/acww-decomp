/* func_ov106_0229df70 @ 0x0229df70, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov106_0229ca3c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229df70(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22a0)) {
        func_ov106_0229ca3c(arg0);
        func_ov002_02208098((void *) (arg0), 7);
    }
}
