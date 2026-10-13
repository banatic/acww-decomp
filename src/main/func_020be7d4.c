/* func_020be7d4 @ 0x020be7d4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int state;
    int pad_04;
    int counter;
    int a;
    int b;
    int c;
} UnkStruct_020be7d4;

void func_020be6ac(UnkStruct_020be7d4 *self, int a, int b);
void func_0203aeec(int a);
void func_020bf2b8(int *dst, int a, int b, int c);
void func_020be5d0(int a, int b, int c, int *d);

extern unsigned char data_021fbb14[];

void func_020be7d4(UnkStruct_020be7d4 *self)
{
    int buffer[4];
    func_020be6ac(self, 0x50, 0);
    if (self->counter > 0) {
        self->counter--;
    } else {
        func_0203aeec(0x5c3);
        func_020bf2b8(buffer, self->a, self->b, self->c);
        func_020be5d0((unsigned int) data_021fbb14, 0, 0x800, buffer);
        self->counter = 0x1e;
        self->state = 9;
    }
}
