/* friend_roster_input: 4 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229a5cc @ 0x0229a5cc, 0xc bytes, Thumb
 * func_ov119_0229a560 @ 0x0229a560, 0x6c bytes, Thumb
 * func_ov119_0229a50c @ 0x0229a50c, 0x54 bytes, Thumb
 * func_ov119_0229a4e4 @ 0x0229a4e4, 0x28 bytes, Thumb
 */

extern void func_ov119_0229b408(void *self);
extern void func_ov119_0229b450(void *self);
extern void func_ov119_0229b3dc(void *self, int arg);
extern void func_ov119_0229b38c(void *self);
extern void func_ov119_0229b284(void *self);
extern void func_ov119_0229bbe4(void *self);
extern void func_ov002_02208c58(void *a, void *b, int c);
extern void func_ov002_022098ec(void *a, int b, int c);
extern void func_ov002_0220970c(void *a, int b);
extern unsigned char *func_ov002_02208098(void *a, unsigned char value);
extern void func_ov119_0229a400(void *a, int b);
extern void func_ov119_0229b9a4(void *);
extern void func_ov002_022096d8(void *, int);

unsigned char func_ov119_0229a5cc(const unsigned char *p, int i)
{
    return *(p + i + 0x4c9);
}

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

void func_ov119_0229a50c(void *self, int arg2)
{
    int size;
    func_ov002_02208c58((char *) self + 0xdc, (char *) self + 0x4c4, arg2);
    size = (*(unsigned char *) ((char *) self + 0xa0) == 0x16) ? 0x9c : 0xb8;
    func_ov002_022098ec((char *) self + 0xdc, 0x100, size);
    func_ov002_0220970c((char *) self + 0xdc, 0);
    func_ov002_02208098(self, 0xa);
    func_ov119_0229a400(self, 0x10);
}

void func_ov119_0229a4e4(void *param)
{
    *(unsigned char *) ((char *) param + 0xad) = 0xa;
    func_ov119_0229b9a4(param);
    func_ov002_022096d8((char *) param + 0xdc, 0);
    func_ov002_02208098(param, 0xc);
}
