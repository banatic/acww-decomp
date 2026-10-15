/* func_0207dac8 @ 0x0207dac8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003704(void *);
extern unsigned int func_0207f1c8(int);
extern int func_0209b5ec(void *);
extern void func_0209bee8(int, int, int);

void func_0207dac8(int arg1, int arg2, int arg3)
{
    if (func_02003704((void *) func_0208150c(arg1)) != 0) {
        func_0209bee8(func_0209b5ec((void *) func_0207f1c8(arg1)), arg2, arg3);
    }
}
