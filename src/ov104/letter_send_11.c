/* letter_send_11: 2 functions, module ov104
 * mwccarm 1.2/base -O4,s
 * func_ov104_0229f440 @ 0x0229f440, 0x20 bytes, Thumb
 * func_ov104_0229f424 @ 0x0229f424, 0x1a bytes, Thumb
 */

extern void func_ov104_0229eaa8(void *unused0);
extern void func_ov002_02208090(void *p, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(int arg);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov104_0229ea5c(int arg);

int func_ov104_0229f440(void *p)
{
    func_ov104_0229eaa8(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov104_0229f424(int arg)
{

    func_ov092_0229929c((void *) func_020ee45c(arg));
    func_ov104_0229ea5c(arg);
    return 1;
}
