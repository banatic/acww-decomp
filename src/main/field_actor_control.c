/* field_actor_control: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200dc8c @ 0x0200dc8c, 0xc bytes, Thumb
 * func_0200dc80 @ 0x0200dc80, 0xc bytes, Thumb
 * func_0200dc48 @ 0x0200dc48, 0x38 bytes, Thumb
 * func_0200dc2c @ 0x0200dc2c, 0x1c bytes, Thumb
 * func_0200dc10 @ 0x0200dc10, 0x1c bytes, Thumb
 * func_0200dc04 @ 0x0200dc04, 0xc bytes, Thumb
 */

struct UnkStruct_0200dc80 {
    char pad_00[0x138];
    short unk_138;
};

typedef struct UnkStruct_0200dc48 {
    unsigned char pad_00[0x170];
    int unk_170;
} UnkStruct_0200dc48;

extern short func_0203c568(void *object);
extern int data_021c67a4;
extern int func_02064594(int param);
extern int func_02064558(int);

unsigned int func_0200dc8c(void *this)
{
    return *(unsigned int *) ((char *) this + 0x134);
}

short func_0200dc80(struct UnkStruct_0200dc80 *ptr)
{
    return ptr->unk_138;
}

short func_0200dc48(UnkStruct_0200dc48 *arg0)
{
    short r4;
    r4 = func_0200dc80((struct UnkStruct_0200dc80 *) arg0);
    if (arg0->unk_170 != 2 && data_021c67a4 != 0) {
        r4 = (short) (r4 + func_0203c568((void *) data_021c67a4));
    }
    return r4;
}

int func_0200dc2c(void *param)
{
    int result;
    int offset;
    int value;

    result = (int) func_0200dc48((UnkStruct_0200dc48 *) param);
    offset = *(short *) ((char *) param + 0x8e);
    value = result - offset;
    value = (value << 16) >> 16;
    return func_02064594(value);
}

int func_0200dc10(int r0)
{
    int r4 = r0;
    int r0_2 = (int) func_0200dc48((UnkStruct_0200dc48 *) ((void *) r0));
    int r1 = *(short *) ((char *) r4 + 0x8e);
    r0_2 = r0_2 - r1;
    r0_2 = (r0_2 << 16) >> 16;
    return func_02064558(r0_2);
}

unsigned char func_0200dc04(unsigned char *arg0)
{
    return arg0[0x13b];
}
