/* func_020ad238 @ 0x020ad238, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f47c8;
extern int data_021f4824[3];
extern int data_021f4818;
extern void func_020012dc(void);
extern void __register_global_object(int *data_021f4824, void (*fp)(void), int *data_021f4818);
extern void func_01ffd070(int *out, int in, int *data_021f4824);
extern void func_020aced0(int *addr, int *buf);
extern int data_021f4904;
extern int data_021f4938;
extern int data_021f496c;

void func_020ad238(int a, unsigned int b)
{
    if (b < 2) {
        return;
    }
    if ((data_021f47c8 & 1) == 0) {
        data_021f4824[0] = 0;
        data_021f4824[1] = 0;
        data_021f4824[2] = 0;
        __register_global_object(data_021f4824, func_020012dc, &data_021f4818);
        data_021f47c8 |= 1;
    }
    {
        int local[3];
        func_01ffd070(local, a, data_021f4824);
        if (b == 2) {
            func_020aced0(&data_021f4904, local);
        } else if (b == 3) {
            func_020aced0(&data_021f4938, local);
        } else if (b == 4) {
            func_020aced0(&data_021f496c, local);
        }
    }
}
