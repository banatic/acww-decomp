/* func_ov121_0229b37c @ 0x0229b37c, 0x28 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *object);
extern void func_ov121_0229a190(void *object);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov121_0229b37c(unsigned int param1)
{
    if (func_0208e484((void *) (param1 + 0x3a8)) != 0) {
        func_ov121_0229a190((void *) param1);
        func_ov002_02208098((void *) param1, 4);
    }
}
