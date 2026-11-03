/* sky_object_kinds_5: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c0440 @ 0x020c0440, 0x4a bytes, Thumb
 * func_020c0428 @ 0x020c0428, 0x18 bytes, Thumb
 * func_020c0420 @ 0x020c0420, 0x8 bytes, Thumb
 */

struct UnkStruct_020c0440 {
    char pad_00[0x0c];
    int unk_0C;
    char pad_10[0x34 - 0x10];
    int arr[3];
    char pad_40[0x58 - 0x40];
    int unk_58;
};

extern int func_020644cc(int);
extern int func_0208a160(void *ptr);
extern void func_020bf590(void *);

void func_020c0440(struct UnkStruct_020c0440 *s)
{
    int a;
    int v;
    int *p;

    a = func_020644cc(0x80);
    a = (a * (func_020644cc(2) * 2 - 1) + 0x80) << 12;
    v = (func_020644cc(0x50) + 0x50) << 12;
    p = &s->arr[0];
    p[0] = a;
    p[1] = v;
    p[2] = 0;
    s->unk_0C = func_020644cc(8) + 8;
    s->unk_58 = 2;
}

void func_020c0428(void *arg)
{
    int result;
    void *ptr = arg;

    result = func_0208a160((char *) ptr + 0x10);
    if (result != 0) {
        *(int *) ((char *) ptr + 4) = 3;
    }
}

void func_020c0420(void *argument0)
{
    func_020bf590((void *) argument0);
}
