/* func_0209b7ac @ 0x0209b7ac, 0xa4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *dst, int val, int len);
extern int func_020535f0(const unsigned short *ptr);
extern int func_020644cc(int);
extern unsigned char data_020d1a60[];

unsigned char func_0209b7ac(unsigned short *ptr, int count)
{
    int rem = 10;
    int flag = 0;
    int j0 = 0;
    unsigned char local[10];
    int i, j, k, n;

    MI_CpuFill8(local, 0, rem);
    for (i = 0; i < count; i++, ptr++) {
        int ok = flag;
        if ((unsigned int) *ptr >= 0x450cU && (unsigned int) *ptr <= 0x45dbU) {
            ok = 1;
        }
        if (ok) {
            for (j = j0; j < 10; j++) {
                if (func_020535f0(ptr) == data_020d1a60[j] && local[j] == 0) {
                    local[j] = 1;
                    rem--;
                    break;
                }
            }
        }
    }
    n = func_020644cc(rem);
    k = 0;
    while (n >= 0) {
        if (local[k] == 0) {
            if (n == 0) {
                break;
            }
            n--;
            k++;
        } else {
            k++;
        }
    }
    return data_020d1a60[k];
}
