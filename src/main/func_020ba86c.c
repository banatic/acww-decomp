/* func_020ba86c @ 0x020ba86c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    int unk_24;
} G1T;
extern G1T data_021f8ab0;
extern unsigned char data_020d22b0[];
extern int data_021f75b0;
extern int data_021f8b30;
extern int data_021f8b2c;

extern int func_020bb89c(int idx);
extern int func_020bb66c(void *p, int a, int b);
extern int func_020bb608(void *p1, void *p2, void *p3, int flag, int extra);
extern int func_02002b40(int a, int b, int c, int d);

int func_020ba86c(int idx)
{
    unsigned char byteval;
    int f24;
    int result;
    int *p_g3;

    f24 = data_021f8ab0.unk_24;
    result = 0;
    byteval = data_020d22b0[idx];

    if (func_020bb89c(idx) == 0) {
        goto done;
    }

    if (func_020bb66c(&data_021f75b0, f24, byteval) == 0) {
        goto done;
    }

    p_g3 = &data_021f8b30;

    if (func_020bb608(&data_021f75b0, &data_021f8b2c, p_g3, result, f24) == 0) {
        goto done;
    }

    if (func_02002b40(data_021f8b2c, byteval, *p_g3, result) == 0) {
        goto done;
    }

    result = 1;
done:
    return result;
}
