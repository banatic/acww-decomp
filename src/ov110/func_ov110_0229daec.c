/* func_ov110_0229daec @ 0x0229daec, 0x2c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov110_0229cdb4(void *);

void func_ov110_0229daec(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x22e0)) {
        func_ov002_02208098((void *) (arg0), *(unsigned char *) ((char *) arg0 + 0xf8));
    }
    func_ov110_0229cdb4(arg0);
}
