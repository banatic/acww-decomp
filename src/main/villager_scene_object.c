/* villager_scene_object: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201ce5c @ 0x0201ce5c, 0xc bytes, Thumb
 * func_0201ce50 @ 0x0201ce50, 0xc bytes, Thumb
 * func_0201ce44 @ 0x0201ce44, 0xc bytes, Thumb
 * func_0201ce38 @ 0x0201ce38, 0xc bytes, Thumb
 * func_0201ce34 @ 0x0201ce34, 0x4 bytes, Thumb
 * func_0201ce30 @ 0x0201ce30, 0x4 bytes, Thumb
 * func_0201ce2c @ 0x0201ce2c, 0x4 bytes, Thumb
 * func_0201ce18 @ 0x0201ce18, 0x14 bytes, Thumb
 * func_0201cde8 @ 0x0201cde8, 0x30 bytes, Thumb
 * func_0201cddc @ 0x0201cddc, 0xc bytes, Thumb
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0201cde8;

extern UnkStruct_0201cde8 *data_020ccf94;
extern int func_02073dd4(UnkStruct_0201cde8 *ptr, int field);
extern unsigned char func_0207af30(void);

void func_0201ce5c(unsigned int *ptr, unsigned int val)
{
    ptr[401] = val;
}

unsigned int func_0201ce50(unsigned int *r0)
{
    return r0[0x191];
}

void func_0201ce44(unsigned char *r0, unsigned char r1)
{
    r0[0x648] = r1;
}

unsigned char func_0201ce38(unsigned char *arg0)
{
    return arg0[0x648];
}

int func_0201ce34(void *object)
{
    (void) object;
    return 0;
}

int func_0201ce30(void *object)
{
    (void) object;
    return 0;
}

int func_0201ce2c(void *object)
{
    (void) object;
    return 0;
}

unsigned int func_0201ce18(void *arg0)
{
    unsigned int val;
    unsigned int *puVar2;

    puVar2 = (unsigned int *) ((unsigned int) arg0 + 0x644);
    val = *puVar2;
    if (val != 0) {
        return 1;
    }
    return 0;
}

void func_0201cde8(char *arg)
{
    arg[0x640] = 0x0B;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        arg[0x640] = func_0207af30();
    }
}

unsigned char func_0201cddc(unsigned char *param0)
{
    return param0[0x640];
}
