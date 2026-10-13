/* func_0208f288 @ 0x0208f288, 0x1e4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x0c];
    int unk_0C;
    int unk_10;
    int unk_14;
    char pad_18[0x44 - 0x18];
    int unk_44;
    char pad_48[0x72 - 0x48];
    unsigned char unk_72;
    unsigned char unk_73;
    unsigned char unk_74;
} Func_0208f288_Struct;

extern int func_0208a1d0(const void *ptr);
extern int func_0208a1b0(const void *ptr, int a);
extern int func_0208a198(const void *ptr, int a);
extern int func_0208aef0(const void *ptr);
extern int func_0208aeec(const void *ptr);
extern void func_02088df8(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11);
extern void func_0208ef7c(const void *ptr);

void func_0208f288(Func_0208f288_Struct *self)
{
    int a, b, c, d, e, f, x, y, x2, y2, x3, y3;
    int flag74;

    if (self->unk_44 == 0) {
        goto exit;
    }

    e = func_0208a1d0((char *) self + 0x1c);
    f = func_0208a1d0((char *) self + 0x30);
    a = func_0208a1b0((char *) self + 0x1c, -1);
    b = func_0208a198((char *) self + 0x1c, -1);
    c = func_0208a1b0((char *) self + 0x30, -1);
    d = func_0208a198((char *) self + 0x30, -1);
    x = func_0208aef0(self) + self->unk_0C;
    y = func_0208aeec(self) + self->unk_10;
    x2 = x + a;
    y2 = y + b;
    x3 = x + c;
    y3 = y + d;

    flag74 = (self->unk_74 == 0);

    if (self->unk_72) {
        func_02088df8(0, e, x2, y2, self->unk_14, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        if (flag74) {
            func_02088df8(0, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_73) {
            func_02088df8(0, e, x2, y2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            if (flag74) {
                func_02088df8(0, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    } else {
        func_02088df8(1, e, x2, y2, self->unk_14, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        if (flag74) {
            func_02088df8(1, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
        }
        if (self->unk_73) {
            func_02088df8(1, e, x2, y2, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            if (flag74) {
                func_02088df8(1, f, x3, y3, -1, -1, 0x1000, 0x1000, 0, 2, 0, 0);
            }
        }
    }

exit:
    func_0208ef7c(self);
}
