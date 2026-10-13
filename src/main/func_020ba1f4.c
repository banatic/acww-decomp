/* func_020ba1f4 @ 0x020ba1f4, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064328(void *dst, void *src, int n);
extern int func_02064af4(void *dst, void *self, int mode);
extern void func_020051b0(void);
extern void __register_global_object(void *a, void *b, void *c);
extern unsigned short data_021f6ca8;
extern unsigned int data_021f6cac;
extern unsigned int data_021f6cb0;
extern char data_020e5958[];

int func_020ba1f4(int a, unsigned short *b)
{
    int local[8];
    int in_range = 0;
    unsigned int value = *b;
    int offset;

    if (value >= 0x1100 && value <= 0x1143) {
        in_range = 1;
    }

    if (in_range) {
        offset = value - 0x1100;
    } else {
        offset = -1;
    }

    if (offset != -1) {
        func_02064328(local, data_020e5958, offset);
        if (func_02064af4(local, (void *) a, -1)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if ((data_021f6cac & 1) == 0) {
            data_021f6ca8 = 0x1100;
            __register_global_object(&data_021f6ca8, func_020051b0, &data_021f6cb0);
            data_021f6cac |= 1;
        }
        return func_020ba1f4(a, &data_021f6ca8);
    }
}