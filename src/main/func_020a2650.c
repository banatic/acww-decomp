/* func_020a2650 @ 0x020a2650, 0x2d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a2650 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xbc - 0xa2];
    void *unk_BC;
    char pad_C0[0xd8 - 0xc0];
    unsigned char unk_D8;
    char pad_D9[0xef - 0xd9];
    unsigned char unk_EF;
    char pad_F0[0x10e - 0xf0];
    unsigned char b_lo : 4;
    unsigned char b_hi : 4;
};

extern void *data_020ccf94;
extern char data_021dc7a8[];
extern char data_021f3ba0[];

extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020757e0(void);
extern int func_020757ac(unsigned char *p);
extern int func_02075774(unsigned char *p);
extern int func_0207570c(void);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_0208b4f8(void);
extern void func_0208b9b8(int);
extern void func_0208b9b0(int);
extern void *func_020984e8(void);
extern void *func_020984d4(void);
extern void MI_CpuCopy8(void *d, void *s, int n);
extern void func_02099a38(void *p);
extern void func_0209ef10(char *p, void *q);
extern int func_020a238c(struct UnkStruct_020a2650 *o);
extern void func_020732b4(void *g, int a);
extern int func_020a2120(struct UnkStruct_020a2650 *o, int a);
extern void func_0209fb54(char *p);
extern int func_02075aa4(int a, int b);
extern int func_0209ffb0(void *receiver);
extern int func_020a0174(void);
extern int func_020a0848(struct UnkStruct_020a2650 *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a4e94(struct UnkStruct_020a2650 *o, int a);

void func_020a2650(struct UnkStruct_020a2650 *self)
{
    int n;

    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020757e0()) {
                return;
            }
            self->state = 1;
            return;

        case 1:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020757ac(&self->unk_D8)) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 2;
            return;

        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_02075774(&self->unk_D8)) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 3;
            return;

        case 3:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_0207570c()) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            func_0208b9b8((int) func_0208b4f8());
            MI_CpuCopy8(func_020984e8(), self->unk_BC, 0x249c);
            func_02099a38(func_020984e8());
            func_0209ef10(data_021dc7a8, func_020984d4());
            self->state = 5;
            return;

        case 5:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            n = func_020a238c(self);
            if (n == 1) {
                self->state = 0xb;
                return;
            }
            if (n == 3) {
                return;
            }
            func_020732b4(data_020ccf94, 2);
            self->state = 6;
            return;

        case 6:
            func_02073fdc(1);
            n = func_020a2120(self, self->b_hi);
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
                return;
            }
            if (n != 0) {
                return;
            }
            self->state = 7;
            return;

        case 7:
            if (func_02073fdc(1)) {
                func_0209fb54(data_021f3ba0);
                self->state = 0xa;
                return;
            }
            if (!func_02075aa4(1, 1)) {
                return;
            }
            self->state = 8;
            return;

        case 8:
            if (func_02073fdc(1)) {
                func_0209fb54(data_021f3ba0);
                self->state = 0xa;
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            n = self->unk_EF;
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 9;
                return;
            }
            if (n != 2) {
                return;
            }
            func_0209fb54(data_021f3ba0);
            self->state = 0xa;
            return;

        case 9:
            if (func_0209ffb0(self)) {
                func_020a0174();
            }
            MI_CpuCopy8(self->unk_BC, func_020984e8(), 0x249c);
            func_0208b9b0((int) func_0208b4f8());
            self->state = 0x16;
            return;

        case 10:
            func_02073fdc(1);
            n = func_020a2120(self, self->b_hi);
            if (n == 1) {
                func_020732b4(data_020ccf94, 0);
                self->state = 0xb;
                return;
            }
            if (n != 0) {
                return;
            }
            func_020732b4(data_020ccf94, 0);
            self->state = 0x11;
            return;

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
            func_020a0848(self, &self->state, 0xb, 0x11, 1, 1);
            return;

        default:
            func_020a4e94(self, 0);
            return;
    }
}
