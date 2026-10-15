/* func_ov136_0229c900 @ 0x0229c900, 0x2c bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov136_0229c734(void *);
extern void func_ov134_0229a5c8(void *, void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov136_0229c900(void *arg0, void *arg1)
{
    func_ov136_0229c734(arg0);
    func_ov134_0229a5c8((char *) arg0 + 0x2c4, arg1);
    func_ov002_02208098((void *) (arg0), 0xe);
}
