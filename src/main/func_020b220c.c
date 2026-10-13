/* func_020b220c @ 0x020b220c, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern int func_020b67e8(int v);
extern int func_020b6694(int v);
extern void __register_global_object(void *a, void (*fn)(void), void *c);
extern void func_0206e9ec(void *a, int b);
extern void func_020012dc(void);

extern int data_021f4b54;
extern int data_021f4b7c[3];
extern int data_021f4b64;

void func_020b220c(void)
{
    int v = func_020b65c4();
    int r = -1;

    if (func_020b67e8(v) != 0 || func_020b6694(v) != 0) {
        r = 0;
    } else if (v == 0x1a) {
        r = 1;
    } else if (v == 9) {
        r = 2;
    } else if (v == 10) {
        r = 3;
    }

    if (r != -1) {
        if ((data_021f4b54 & 1) == 0) {
            data_021f4b7c[0] = 0x10000;
            data_021f4b7c[1] = 0;
            data_021f4b7c[2] = 0x1e000;
            __register_global_object(data_021f4b7c, func_020012dc, &data_021f4b64);
            data_021f4b54 |= 1;
        }
        func_0206e9ec(data_021f4b7c, r);
    }
}
