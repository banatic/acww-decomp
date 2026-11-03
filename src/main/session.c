/* session: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020731c4 @ 0x020731c4, 0x5c bytes, Thumb
 * func_020731a4 @ 0x020731a4, 0x20 bytes, Thumb
 * func_0207318c @ 0x0207318c, 0x18 bytes, Thumb
 * func_02073180 @ 0x02073180, 0xc bytes, Thumb
 * func_02073174 @ 0x02073174, 0xc bytes, Thumb
 * func_02073168 @ 0x02073168, 0xc bytes, Thumb
 * func_0207315c @ 0x0207315c, 0xc bytes, Thumb
 * func_02073150 @ 0x02073150, 0xc bytes, Thumb
 * func_02073144 @ 0x02073144, 0xc bytes, Thumb
 * func_02073138 @ 0x02073138, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x128];
    unsigned short arr[64];
} UnkStruct_020731a4;

extern void *data_020ccf94;
extern int func_02073dd4(void *p, int idx);
extern int func_02073918(void *p, int idx);
extern int func_02077b58(int idx);
extern unsigned int func_02073220(void *p, int idx);
extern int func_02077a64(void);

int func_020731c4(void *object)
{
    int idx = 3;
    void *p = data_020ccf94;

    while (idx >= 0) {
        if (func_02073dd4(p, idx) && !func_02073918(p, idx)) {
            unsigned int result;

            func_02077b58(idx);
            result = func_02073220(p, idx);
            func_02077a64();
            if (result > 600U) {
                return 1;
            }
        }
        idx--;
    }
    return 0;
}

void func_020731a4(UnkStruct_020731a4 *s, int value)
{
    s->arr[func_02077b58(value)] = 0;
}

void func_0207318c(char *base)
{
    unsigned short *p;
    int i;
    p = (unsigned short *) (base + 0x128);
    for (i = 2; i >= 0; i--) {
        *p++ = 0;
    }
}

void func_02073180(unsigned short *param0, unsigned short param1)
{
    param0[0x97] = param1;
}

unsigned short func_02073174(unsigned short *r0)
{
    return r0[0x97];
}

void func_02073168(unsigned short *param0, unsigned short param1)
{
    param0[0x98] = param1;
}

unsigned short func_0207315c(unsigned short *r0)
{
    return r0[0x98];
}

void func_02073150(unsigned short *arg0, unsigned short arg1)
{
    arg0[0x99] = arg1;
}

int func_02073144(int r0)
{
    return r0 + 0x134;
}

int func_02073138(int arg0)
{
    return arg0 + 0x714;
}
