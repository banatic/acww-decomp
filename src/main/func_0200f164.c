/* func_0200f164 @ 0x0200f164, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *p);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, char *flag, int val);
extern void func_02073770(void *p, int a, int b);

void func_0200f164(void)
{
    if (func_02073d90(data_020ccf94) != 0) {
        char flag = 0;
        void *p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &flag, 1);
        func_02073770(p, 0x2d, 4);
    }
}
