/* scene_object_base: 16 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203ee30 @ 0x0203ee30, 0x2 bytes, Thumb
 * func_0203ee2c @ 0x0203ee2c, 0x4 bytes, Thumb
 * func_0203ee28 @ 0x0203ee28, 0x4 bytes, Thumb
 * func_0203ee24 @ 0x0203ee24, 0x4 bytes, Thumb
 * func_0203ee20 @ 0x0203ee20, 0x4 bytes, Thumb
 * func_0203ee14 @ 0x0203ee14, 0xc bytes, Thumb
 * func_0203ee08 @ 0x0203ee08, 0xc bytes, Thumb
 * func_0203edf4 @ 0x0203edf4, 0x14 bytes, Thumb
 * func_0203eddc @ 0x0203eddc, 0x18 bytes, Thumb
 * func_0203edd0 @ 0x0203edd0, 0xc bytes, Thumb
 * func_0203eda4 @ 0x0203eda4, 0x2a bytes, Thumb
 * func_0203ed98 @ 0x0203ed98, 0xc bytes, Thumb
 * func_0203ed8c @ 0x0203ed8c, 0xc bytes, Thumb
 * func_0203ed78 @ 0x0203ed78, 0x12 bytes, Thumb
 * func_0203ed68 @ 0x0203ed68, 0xe bytes, Thumb
 * func_0203ed58 @ 0x0203ed58, 0xe bytes, Thumb
 */

typedef struct {
    char pad_00[0xe4];
    int unk_E4;
} UnkStruct_0203edf4;

extern void func_0203df94(unsigned int receiver);
extern void func_0203df88(int arg1);
extern int FX_MulFunc(int a, int b);

int func_0203ed78(unsigned short *param0, unsigned short param1);
void func_0203ed68(void *arg0, unsigned short arg1);
void func_0203ed58(unsigned char *ptr, unsigned short mask);

void func_0203ee30(void) {}

int func_0203ee2c(int p0)
{
    return ((int) (p0) + (92));
}

int func_0203ee28(void)
{
    return 0;
}

int func_0203ee24(void)
{
    return 0;
}

int func_0203ee20(void)
{
    return 0;
}

void func_0203ee14(int unused, int arg)
{
    func_0203df94(arg);
}

void func_0203ee08(int arg1, int arg2)
{
    func_0203df88(arg2);
}

void func_0203edf4(UnkStruct_0203edf4 *obj, int arg)
{
    obj->unk_E4 = FX_MulFunc(arg, arg);
}

void func_0203eddc(int a)
{
    int r4 = a;
    func_0203ed58((unsigned char *) r4, 3);
    func_0203ed68((void *) r4, 2);
}

void func_0203edd0(int a)
{
    func_0203ed58((unsigned char *) a, 3);
}

int func_0203eda4(int param1)
{
    int result;

    if (func_0203ed78((unsigned short *) param1, 1) != 0) {
        result = 0;
    } else if (func_0203ed78((unsigned short *) param1, 2) != 0) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

void func_0203ed98(int a)
{
    func_0203ed68((void *) a, 4);
}

int func_0203ed8c(int a)
{
    return func_0203ed78((unsigned short *) a, 4);
}

// placeholder, not used
int func_0203ed78(unsigned short *param0, unsigned short param1)
{
    unsigned short value;
    value = *(unsigned short *) ((unsigned char *) param0 + 0xe8);
    if (value & param1) {
        return 1;
    }
    return 0;
}

void func_0203ed68(void *arg0, unsigned short arg1)
{
    unsigned short *puVar1;
    unsigned short val;

    puVar1 = (unsigned short *) ((char *) arg0 + 0xe8);
    val = *puVar1;
    val = val | arg1;
    *(unsigned short *) ((char *) arg0 + 0xe8) = val;
}

void func_0203ed58(unsigned char *ptr, unsigned short mask)
{
    *(unsigned short *) (ptr + 0xE8) &= ~mask;
}
