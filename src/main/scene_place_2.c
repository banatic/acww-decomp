/* scene_place_2: 11 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6580 @ 0x020b6580, 0x10 bytes, Thumb
 * func_020b657c @ 0x020b657c, 0x2 bytes, Thumb
 * func_020b6518 @ 0x020b6518, 0x64 bytes, Thumb
 * func_020b64f0 @ 0x020b64f0, 0x28 bytes, Thumb
 * func_020b64ec @ 0x020b64ec, 0x2 bytes, Thumb
 * func_020b64e8 @ 0x020b64e8, 0x4 bytes, Thumb
 * func_020b64e0 @ 0x020b64e0, 0x6 bytes, Thumb
 * func_020b64dc @ 0x020b64dc, 0x4 bytes, Thumb
 * func_020b64d4 @ 0x020b64d4, 0x6 bytes, Thumb
 * func_020b64cc @ 0x020b64cc, 0x6 bytes, Thumb
 * func_020b64c0 @ 0x020b64c0, 0xc bytes, Thumb
 */

typedef struct In {
    unsigned int a;
    unsigned int b;
    unsigned int c;
} In;

typedef struct UnkStruct_020b64f0 {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    short e;
    unsigned char unk_12;
    unsigned char g;
    unsigned char h;
} UnkStruct_020b64f0;

extern unsigned int data_021f6938;
extern int data_021f6994[3];
extern int data_021f6988;
extern void __register_global_object(void *, void *, void *);
extern void func_020012dc(void *);

void func_020b6518(int param);
void func_020b64f0(UnkStruct_020b64f0 *out, unsigned char b, In *in, unsigned int d, short e, unsigned int f, unsigned int g);

int func_020b6580(int arg)
{
    func_020b6518(arg);
    return arg;
}

void func_020b657c(void *object) {}

void func_020b6518(int param)
{
    if ((data_021f6938 & 1) == 0) {
        data_021f6994[0] = 0x00030000;
        data_021f6994[1] = 0;
        data_021f6994[2] = 0x00030000;
        __register_global_object((void *) ((unsigned int) data_021f6994), (((void *) func_020012dc)),
                                 (void *) ((unsigned int) &data_021f6988));
        data_021f6938 |= 1;
    }
    {
        int a0 = 0;
        int a1 = -1;
        int a2 = -1;
        func_020b64f0((UnkStruct_020b64f0 *) param, 0, (In *) data_021f6994, 0x00800000, a0, a1, a2);
    }
}

void func_020b64f0(UnkStruct_020b64f0 *out, unsigned char b, In *in, unsigned int d, short e, unsigned int f, unsigned int g)
{
    out->unk_12 = b;
    out->a = in->a;
    out->b = in->b;
    out->c = in->c;
    out->d = d;
    out->e = e;
    out->g = (unsigned char) f;
    out->h = (unsigned char) g;
}

void *func_020b64ec(void *record)
{
    return record;
}

int func_020b64e8(int *p0)
{
    return p0[3];
}

int func_020b64e0(short *p)
{
    return p[8];
}

int func_020b64dc(unsigned char *p0)
{
    return p0[18];
}

signed char func_020b64d4(signed char *p)
{
    return p[0x13];
}

signed char func_020b64cc(signed char *p)
{
    return p[0x14];
}

int func_020b64c0(unsigned int param)
{
    if (param < 0x33) {
        return 1;
    } else {
        return 0;
    }
}
