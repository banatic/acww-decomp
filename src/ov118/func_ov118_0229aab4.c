/* func_ov118_0229aab4 @ 0x0229aab4, 0x24 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

void func_ov118_0229aab4(void *arg0);

extern void func_ov118_0229a450(void *arg0, int arg1);
extern void func_ov118_0229a440(void *arg0, int arg1);

void func_ov118_0229aab4(void *arg0)
{
    func_ov118_0229a450(arg0, 0x40);
    func_ov118_0229a440(arg0, 0x100);
    *(unsigned char *) ((char *) arg0 + 0xa8) = 0xf;
}
