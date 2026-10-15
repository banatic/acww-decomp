/* func_0203c76c @ 0x0203c76c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203c068(void *);
extern void func_0203f684(void *dst, void *src);
extern void func_01ffcbb0(void *dst, void *src);

extern unsigned char data_021c749c[];

int func_0203c76c(void *arg0)
{
    char sp[0x10];
    func_0203c068(arg0);
    func_01ffcbb0(sp, arg0);
    func_0203f684((void *) data_021c749c, sp);
    return 1;
}
