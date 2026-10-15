/* func_ov110_0229db48 @ 0x0229db48, 0x28 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(char *addr);
extern void func_ov110_0229ca28(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov110_0229db48(void *param)
{
    if (func_0208e484((char *) param + 0x22e0) != 0) {
        func_ov110_0229ca28(param);
        func_ov002_02208098((void *) (param), 4);
    }
}
