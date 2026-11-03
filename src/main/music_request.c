/* music_request: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020374fc @ 0x020374fc, 0x10 bytes, Thumb
 * func_020374d0 @ 0x020374d0, 0x2a bytes, Thumb
 * func_020374cc @ 0x020374cc, 0x2 bytes, Thumb
 * func_020374ac @ 0x020374ac, 0x20 bytes, Thumb
 * func_02037470 @ 0x02037470, 0x3c bytes, Thumb
 * func_02037458 @ 0x02037458, 0x18 bytes, Thumb
 */

typedef struct {
    int unk_00;
    short unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
} UnkStruct_020374d0;

typedef struct {
    char pad_00[0x18];
    int counter;
} UnkStruct_02037458;

void func_020374ac(void *r0);

int func_020374fc(int arg)
{
    func_020374ac((void *) arg);
    return arg;
}

UnkStruct_020374d0 *func_020374d0(UnkStruct_020374d0 *p, int x, int y, int z, int w, int c)
{
    func_020374ac((void *) p);
    p->unk_00 = x;
    p->unk_04 = y;
    p->unk_0C = z;
    p->unk_08 = w;
    p->unk_10 = *(unsigned char *) &c;
    return p;
}

void func_020374cc(void *object) {}

void func_020374ac(void *r0)
{
    unsigned short *p16 = (unsigned short *) ((char *) r0 + 4);
    unsigned char *p8 = (unsigned char *) r0;
    unsigned int *p32 = (unsigned int *) r0;

    p32[0] = 0x25;
    *p16 = 0xffff;
    p32[2] = 0;
    p32[3] = 0;
    p8[0x10] = 0;
    p8[0x11] = 0;
    p8[0x12] = 0;
    p8[0x13] = 0;
    p8[0x14] = 0;
    p32[6] = 0;
}

void func_02037470(void *dst, const void *src)
{
    func_020374ac(dst);
    *(unsigned int *) ((char *) dst + 0) = *(const unsigned int *) ((const char *) src + 0);
    *(unsigned short *) ((char *) dst + 4) = *(const unsigned short *) ((const char *) src + 4);
    *(unsigned int *) ((char *) dst + 8) = *(const unsigned int *) ((const char *) src + 8);
    *(unsigned int *) ((char *) dst + 0xc) = *(const unsigned int *) ((const char *) src + 0xc);
    *(unsigned char *) ((char *) dst + 0x10) = *(const unsigned char *) ((const char *) src + 0x10);
    *(unsigned char *) ((char *) dst + 0x11) = *(const unsigned char *) ((const char *) src + 0x11);
    *(unsigned char *) ((char *) dst + 0x12) = *(const unsigned char *) ((const char *) src + 0x12);
    *(unsigned char *) ((char *) dst + 0x13) = *(const unsigned char *) ((const char *) src + 0x13);
    *(unsigned char *) ((char *) dst + 0x14) = *(const unsigned char *) ((const char *) src + 0x14);
    *(unsigned int *) ((char *) dst + 0x18) = *(const unsigned int *) ((const char *) src + 0x18);
}

int func_02037458(UnkStruct_02037458 *obj)
{
    int res = 0;
    if (obj->counter > 0) {
        obj->counter--;
        if (obj->counter <= 0) {
            res = 1;
        }
    }
    return res;
}
