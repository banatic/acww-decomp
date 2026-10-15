/* func_020be784 @ 0x020be784, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    char pad_0C[12];
    unsigned char unk_18;
} UnkStruct_020be784;

extern void func_020be6ac(UnkStruct_020be784 *self, int a, int b);
extern int func_02095794(int x);
extern int func_0208602c(void);
extern int func_020860c0(int);
extern int func_02087b8c(int a, int b, unsigned char c);
extern int func_ov003_02219774(void);
extern int func_0203aeac(void);
extern void func_020be758(UnkStruct_020be784 *self);

void func_020be784(UnkStruct_020be784 *self)
{
    int r5;
    func_020be6ac(self, 0x190, 0x190);
    self->unk_08--;
    if (self->unk_08 > 0) {
        return;
    }
    r5 = func_02095794(self->unk_04);
    if (r5 != 0) {
        func_02087b8c(func_020860c0((int) func_0208602c()), r5, self->unk_18);
    }
    func_ov003_02219774();
    func_0203aeac();
    func_020be758(self);
}
