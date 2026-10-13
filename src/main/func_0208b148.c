/* func_0208b148 @ 0x0208b148, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2c4];
    char unk_2C4;
    char pad_2C5[0x348 - 0x2c4 - 1];
    unsigned char unk_348;
    unsigned char unk_349;
} Struct0208b148;

extern void func_0208b9d8(void *);
extern void func_0208b9d0(void *);
extern int func_0208b9c0(void *);
extern void func_02011f74(int, int);
extern void func_0208b090(void *);
extern void func_0208b0d8(void *);

void func_0208b148(Struct0208b148 *self)
{
    if (self->unk_348 || self->unk_349) {
        func_0208b9d8(&self->unk_2C4);
    } else {
        func_0208b9d0(&self->unk_2C4);
        if (func_0208b9c0(&self->unk_2C4)) {
            func_02011f74(4, 1);
            func_0208b090(self);
        }
    }
    func_0208b0d8(self);
}
