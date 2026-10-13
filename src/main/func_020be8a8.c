/* func_020be8a8 @ 0x020be8a8, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020be6ac(void *a, int b, int c);
extern void func_0203aeec(int a);
extern void func_020bf2b8(int *dst, int a, int b, int c);
extern void func_020be5d0(int *a, int b, int c, int *d);
extern int data_021fbb14;

typedef struct {
    int state;   // 0x00
    int pad_04;  // 0x04
    int counter; // 0x08
    int a;       // 0x0c
    int b;       // 0x10
    int c;       // 0x14
} UnkStruct_020be8a8;

void func_020be8a8(UnkStruct_020be8a8 *arg)
{
    int local[4]; // 16 bytes

    func_020be6ac(arg, 0x50, 0);
    arg->counter--;
    if (arg->counter > 0) {
        return;
    }

    func_0203aeec(0x0a3d);
    func_020bf2b8(local, arg->a, arg->b, arg->c);
    func_020be5d0(&data_021fbb14, 0, 0x07fd, local);
    arg->counter = 0x32;
    arg->state = 6;
}
