/* func_ov119_0229a560 @ 0x0229a560, 0x6c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov119_0229b408(void *self);
extern void func_ov119_0229b450(void *self);
extern void func_ov119_0229b3dc(void *self, int arg);
extern void func_ov119_0229b38c(void *self);
extern void func_ov119_0229b284(void *self);
extern void func_ov119_0229bbe4(void *self);

void func_ov119_0229a560(void *self)
{
    unsigned char val = ((unsigned char *) self)[0xad];
    switch (val) {
        case 1:
            func_ov119_0229b408(self);
            break;
        case 0:
            func_ov119_0229b450(self);
            break;
        case 2:
            func_ov119_0229b3dc(self, 9);
            break;
        case 3:
            func_ov119_0229b3dc(self, 11);
            break;
        case 4:
            func_ov119_0229b3dc(self, 13);
            break;
        case 5:
            func_ov119_0229b38c(self);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            func_ov119_0229b284(self);
            break;
        case 10:
        default:
            func_ov119_0229bbe4(self);
            break;
    }
}
