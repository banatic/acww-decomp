/* my_designs_7: 10 functions, module ov121
 * mwccarm 1.2/base -O4,s
 * func_ov121_0229b008 @ 0x0229b008, 0x16 bytes, Thumb
 * func_ov121_0229afd8 @ 0x0229afd8, 0x30 bytes, Thumb
 * func_ov121_0229afb8 @ 0x0229afb8, 0x20 bytes, Thumb
 * func_ov121_0229af7c @ 0x0229af7c, 0x3c bytes, Thumb
 * func_ov121_0229af58 @ 0x0229af58, 0x24 bytes, Thumb
 * func_ov121_0229af40 @ 0x0229af40, 0x18 bytes, Thumb
 * func_ov121_0229af00 @ 0x0229af00, 0x40 bytes, Thumb
 * func_ov121_0229aec4 @ 0x0229aec4, 0x3c bytes, Thumb
 * func_ov121_0229ae68 @ 0x0229ae68, 0x5c bytes, Thumb
 * func_ov121_0229ae18 @ 0x0229ae18, 0x50 bytes, Thumb
 */

typedef struct {
    char pad_00[0xb0];
    unsigned char b0;
} UnkStruct_0229aec4;

extern void func_ov121_0229a358(void *arg0);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern void func_ov121_0229a3fc(void *);
extern void func_ov121_0229a450(void *);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern unsigned char data_021f43ec;
extern int func_ov002_0220b9b8(void *, void *, int, int);
extern int func_ov090_022990b8(int);
extern const unsigned char data_ov121_0229c248[];
extern unsigned char data_ov121_0229c238[];
extern unsigned short data_ov121_0229c228[];
extern unsigned short data_ov121_0229c218[];
extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov121_02299a4c(void *, int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

unsigned char *func_ov121_0229b008(void *p)
{
    func_ov121_0229a358((void *) p);
    return func_ov002_02208098(p, 0);
}

unsigned char *func_ov121_0229afd8(void *param)
{
    unsigned char *p = (unsigned char *) param;
    p[0xae] = 0x18;
    p[0xad] = 0x18;
    func_ov121_0229a3fc(param);
    func_ov002_02207fc0(param);
    func_ov121_0229a450(param);
    return func_ov002_02208098(param, 4);
}

unsigned char *func_ov121_0229afb8(void *p)
{
    if (func_0206fe60()) {
        return func_ov121_0229b008(p);
    } else {
        return func_ov121_0229afd8(p);
    }
}

void func_ov121_0229af7c(int p0, char p1, int p2)
{
    char c;
    c = data_021f43ec;
    c = p1;
    func_ov002_0220b9b8((void *) (p0 + 0x40c), &c, p2, 0);
    func_ov002_02208098((void *) p0, 19);
    func_ov121_0229a358((void *) p0);
}

int func_ov121_0229af58(int a, unsigned int b)
{
    if (b >= 0x10 && b <= 0x17) {
        b -= 0x10;
        return func_ov090_022990b8(b);
    } else {
        return data_ov121_0229c248[b];
    }
}

int func_ov121_0229af40(int unused, unsigned int index)
{
    if (index >= 0x10 && index <= 0x17) {
        return 8;
    } else {
        return data_ov121_0229c238[index];
    }
}

void func_ov121_0229af00(void *arg0, int arg1, int arg2)
{
    int idx;
    unsigned short x, y;

    idx = arg1 - 9;
    x = data_ov121_0229c228[idx];
    y = data_ov121_0229c218[idx];
    func_0206fdd4((char *) arg0 + 0x98c, y, x, y + 3, x + 3, arg2);
    func_ov121_02299a4c(arg0, 2);
}

void func_ov121_0229aec4(UnkStruct_0229aec4 *obj, int value)
{
    unsigned char b = obj->b0;
    if (value == b) {
        return;
    }
    if (b != 0x18) {
        func_ov121_0229af00((void *) obj, b, 2);
    }
    obj->b0 = value;
    if (obj->b0 != 0x18) {
        func_ov121_0229af00((void *) obj, obj->b0, 6);
    }
}

int func_ov121_0229ae68(void *p, unsigned char a, unsigned char b, unsigned int c)
{
    unsigned char i;
    int amin = a - 0x10;
    int aplus = a + 0x10;
    int bmin = b - 0x10;
    int bplus = b + 0x10;
    for (i = 0; i <= c; i = (unsigned char) (i + 1)) {
        int v = func_ov121_0229af58((int) p, i);
        if (amin < v && v < aplus) {
            int w = func_ov121_0229af40((int) p, i);
            if (bmin < w && w < bplus) {
                return i;
            }
        }
    }
    return 0x18;
}

int func_ov121_0229ae18(void *param)
{
    unsigned char g1;
    unsigned char g2;
    int ret;
    int tmp1;
    int tmp2;

    g1 = data_021f6c58;
    g2 = data_021f6c54;
    ret = func_ov121_0229ae68(param, g1, g2, 7);
    if (ret != 0x18) {
        tmp1 = func_ov121_0229af58((int) param, ret) - g1;
        *((unsigned short *) ((char *) param + 0xa8)) = tmp1;
        tmp2 = func_ov121_0229af40((int) param, ret) - g2;
        *((unsigned short *) ((char *) param + 0xaa)) = tmp2;
    }
    return ret;
}
