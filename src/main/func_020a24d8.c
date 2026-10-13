/* func_020a24d8 @ 0x020a24d8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020682e0(int);
extern void func_02068440(int);
extern void func_0206844c(int, int *, int);
extern void func_020a4e94(int, int);
extern int data_021f43e8;

typedef struct {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x48 - 0x1f];
    int unk_48;
} Struct020a24d8;

void func_020a24d8(Struct020a24d8 *self)
{
    int ret = func_020682e0(0);

    switch (self->unk_1E) {
        case 10:
            func_02068440(ret);
            break;
        case 8:
            func_0206844c(ret, &data_021f43e8, 0);
            break;
        case 39:
            func_0206844c(ret, &data_021f43e8, 0);
            break;
        case 38:
            func_02068440(ret);
            func_020a4e94(self->unk_48, 0x1e);
            break;
        case 105:
            func_0206844c(ret, &data_021f43e8, 0);
            break;
    }
}
