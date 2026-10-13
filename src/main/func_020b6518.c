/* func_020b6518 @ 0x020b6518, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_021f6938;
extern int data_021f6994[3];
extern int data_021f6988;
extern void __register_global_object(unsigned int a, unsigned int b, unsigned int c);
extern void func_020b64f0(int a, int b, int *c, int d, int e, int f, int g);

extern void func_020012dc(void);

void func_020b6518(int param)
{
    if ((data_021f6938 & 1) == 0) {
        data_021f6994[0] = 0x00030000;
        data_021f6994[1] = 0;
        data_021f6994[2] = 0x00030000;
        __register_global_object((unsigned int) data_021f6994, (unsigned int) func_020012dc, (unsigned int) &data_021f6988);
        data_021f6938 |= 1;
    }
    {
        int a0 = 0;
        int a1 = -1;
        int a2 = -1;
        func_020b64f0(param, 0, data_021f6994, 0x00800000, a0, a1, a2);
    }
}
