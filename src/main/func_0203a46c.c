/* func_0203a46c @ 0x0203a46c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203a4ec(int arg);
extern void func_0209e100(void *ptr, int a);
extern unsigned int func_0209de88(int a, int b, int c);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_0203a46c(int arg0, const void *arg1, int arg2)
{
    if (arg2 == 0) {
        return;
    }
    if (arg2 >= 4) {
        func_0203a4ec(arg0);
        return;
    }
    {
        union {
            unsigned long long value;
            unsigned char bytes[8];
        } temp;
        temp.value = 0;
        MI_CpuCopy8(arg1, &temp, 8);
        func_0209e100(&temp, 6);
        {
            unsigned int result = func_0209de88(temp.bytes[5], temp.bytes[4], temp.bytes[3]);
            switch (result) {
                case 0:
                    break;
                case 1:
                case 4:
                    func_0203a4ec(arg0);
                    break;
                case 2:
                case 5:
                    if (arg2 >= 2) {
                        func_0203a4ec(arg0);
                    }
                    break;
                case 3:
                case 6:
                    if (arg2 >= 3) {
                        func_0203a4ec(arg0);
                    }
                    break;
            }
        }
    }
}
