/* villager_mode_record_3: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209c448 @ 0x0209c448, 0x26 bytes, Thumb
 * func_0209c42c @ 0x0209c42c, 0x1a bytes, Thumb
 * func_0209c410 @ 0x0209c410, 0x1c bytes, Thumb
 * func_0209c3e4 @ 0x0209c3e4, 0x2c bytes, Thumb
 * func_0209c3c8 @ 0x0209c3c8, 0x1a bytes, Thumb
 * func_0209c398 @ 0x0209c398, 0x30 bytes, Thumb
 * func_0209c38c @ 0x0209c38c, 0xc bytes, Thumb
 * func_0209c380 @ 0x0209c380, 0xc bytes, Thumb
 * func_0209c370 @ 0x0209c370, 0xe bytes, Thumb
 * func_0209c334 @ 0x0209c334, 0x3c bytes, Thumb
 * func_0209c330 @ 0x0209c330, 0x4 bytes, Thumb
 * func_0209c32c @ 0x0209c32c, 0x4 bytes, Thumb
 * func_0209c310 @ 0x0209c310, 0x1c bytes, Thumb
 * func_0209c304 @ 0x0209c304, 0xc bytes, Thumb
 * func_0209c2d4 @ 0x0209c2d4, 0x30 bytes, Thumb
 */

typedef struct {
    char pad_00[0x10];
    unsigned char unk_10;
} Func0209c380;

extern int func_0209c53c(void *ptr);
extern void func_0209c538(void *ptr);
extern void func_0209c52c(void *ptr);
extern void MI_CpuFill8(void *ptr, int val, int size);
extern void func_0209c51c(unsigned char *p, int a);
extern int func_0209c4a8(unsigned char *p);
extern void func_0209c470(unsigned char *p, int n);
extern void func_0209e474(unsigned char *p);
extern unsigned char data_020d1a20[];

void func_0209c398(void *arg);
int func_0209c38c(unsigned int x);

void func_0209c448(unsigned char *array, int index, int delta)
{
    if (func_0209c38c(index)) {
        unsigned char *ptr = &array[index];
        int val = *ptr;
        val += delta;
        if (val >= 255) {
            val = 255;
        }
        *ptr = (unsigned char) val;
    }
}

void func_0209c42c(char *dst, int idx, char val)
{
    if (func_0209c38c(idx)) {
        dst[idx] = val;
    }
}

int func_0209c410(unsigned char *r5, unsigned char r6)
{
    unsigned char r4 = 0;
    unsigned char r0;

    if (func_0209c38c((unsigned char) r6) != 0) {
        r4 = r5[r6];
    }
    return r4;
}

void *func_0209c3e4(void *obj)
{
    int *p = (int *) obj;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    func_0209c53c((char *) obj + 0x11);
    func_0209c53c((char *) obj + 0x19);
    func_0209c398(obj);
    return obj;
}

char *func_0209c3c8(char *param)
{
    func_0209c538(param + 0x19);
    func_0209c538(param + 0x11);
    return param;
}

void func_0209c398(void *arg)
{
    void *ptr = arg;
    MI_CpuFill8(ptr, 0, 0x24);
    *(unsigned char *) ((char *) ptr + 0x10) = 7;
    func_0209c52c((char *) ptr + 0x11);
    func_0209c52c((char *) ptr + 0x19);
    *(unsigned int *) ptr = 0;
    *(unsigned int *) ((char *) ptr + 4) = 0;
    *(unsigned int *) ((char *) ptr + 8) = 0;
    *(unsigned int *) ((char *) ptr + 0xc) = 0;
}

int func_0209c38c(unsigned int x)
{
    if (x < 8) {
        return 1;
    }
    return 0;
}

int func_0209c380(Func0209c380 *self)
{
    return func_0209c38c((unsigned char) self->unk_10);
}

unsigned int func_0209c370(void *arg0)
{
    unsigned char val;
    val = *(unsigned char *) ((char *) arg0 + 0x10);
    if (val < 0xc) {
        return 1;
    }
    return 0;
}

void func_0209c334(unsigned char *p, int a, int b)
{
    func_0209c51c(p + 0x11, a);
    p[0x10] = (unsigned char) func_0209c4a8(p + 0x11);
    if (b) {
        func_0209c470(p + 0x11, p[0x10]);
    }
    func_0209e474(p);
    p += 8;
    func_0209e474(p);
}

int func_0209c330(unsigned char *p0)
{
    return p0[16];
}

void func_0209c32c(unsigned char *p0, int p1)
{
    p0[16] = p1;
}

unsigned func_0209c310(unsigned r0)
{
    unsigned result = 3;
    if (r0 < 5) {
        result = 0;
    } else {
        if (r0 < 8) {
            result = 1;
        } else {
            if (r0 < 12) {
                result = 2;
            }
        }
    }
    return result;
}

unsigned func_0209c304(unsigned char *r0)
{
    return func_0209c310((unsigned char) r0[0x10]);
}

int func_0209c2d4(unsigned char *arg0, unsigned char arg1)
{
    unsigned char local_1;
    int local_2;
    unsigned char local_3;

    local_3 = (unsigned char) func_0209c310((unsigned char) arg1);
    *arg0 = local_3;
    local_1 = *arg0;
    if (local_1 < 3) {
        local_2 = arg1 - data_020d1a20[local_1];
    } else {
        local_2 = -1;
    }
    return local_2;
}
