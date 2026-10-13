/* func_0200f11c @ 0x0200f11c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

func_0200f11c(unsigned int param1)
{
    extern unsigned int data_020ccf94;
    extern int func_02073d90(unsigned int);
    extern int func_020112bc(unsigned int);
    extern void func_02073820(unsigned int);
    extern void func_020737f0(unsigned int, unsigned char *, int);
    extern void func_02073770(unsigned int, int, int);
    unsigned char local;
    unsigned int r4;

    if (func_02073d90(*(unsigned int *) &data_020ccf94) != 0) {
        local = (unsigned char) func_020112bc(param1);
        r4 = *(unsigned int *) &data_020ccf94;
        func_02073820(r4);
        func_020737f0(r4, &local, 1);
        func_02073770(r4, 0x2e, 4);
    }
}
