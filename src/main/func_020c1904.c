/* func_020c1904 @ 0x020c1904, 0xe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_0206837c(int);
extern int func_020ab504(int);
extern void func_0206844c(int, char *, int);
extern void func_0208602c(void);
extern void func_020860c4(void);
extern void func_02087f28(void);
extern void func_02087f20(void);
extern int func_020b65c4(void);
extern int data_020e7ad8;

typedef struct {
    char pad_00[0x1e];
    unsigned char state;
    char pad_1F[0x40 - 0x1f];
    int something;
    char pad_44[0xb0 - 0x44];
    unsigned char *unk_B0;
} UnkStruct_020c1904;

void func_020c1904(UnkStruct_020c1904 *self)
{
    char arr[2];
    int r;
    switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
        case 36:
            r = func_020ab504(func_0206837c(self->something));
            switch (r) {
                case 0:
                    arr[0] = (char) (func_020644cc(3) + 0x1c);
                    func_0206844c(self->something, arr, data_020e7ad8);
                    func_0208602c();
                    func_020860c4();
                    func_02087f28();
                    break;
                case 1:
                    arr[1] = (char) (func_020644cc(3) + 0x1f);
                    func_0206844c(self->something, &arr[1], data_020e7ad8);
                    if (func_020b65c4() == 0) {
                        func_0208602c();
                        func_020860c4();
                        func_02087f20();
                    }
                    self->unk_B0[0x711] = 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
