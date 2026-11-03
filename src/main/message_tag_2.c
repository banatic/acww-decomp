/* message_tag_2: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a87c8 @ 0x020a87c8, 0x16 bytes, Thumb
 * func_020a87a8 @ 0x020a87a8, 0x1e bytes, Thumb
 * func_020a8764 @ 0x020a8764, 0x42 bytes, Thumb
 * func_020a8754 @ 0x020a8754, 0xe bytes, Thumb
 * func_020a8750 @ 0x020a8750, 0x2 bytes, Thumb
 * func_020a873c @ 0x020a873c, 0x14 bytes, Thumb
 * func_020a8718 @ 0x020a8718, 0x22 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xc];
    void *ptr;
} UnkStruct020a873c;

extern int func_020a9adc(void *);
extern int func_020a9ae0(unsigned short *p);

int func_020a87c8(unsigned char *r0, int r1)
{
    unsigned char local;
    local = r0[r1];
    return func_020a9adc(&local);
}

int func_020a87a8(unsigned char *data, int offset)
{
    unsigned char *p = data + offset;
    unsigned short value = p[0] | (p[1] << 8);
    return func_020a9ae0(&value);
}

void func_020a8764(int *out, int value)
{
    int a, b, c;
    func_020a87a8((unsigned char *) value, 0);
    a = func_020a87c8((unsigned char *) value, 2);
    b = func_020a87c8((unsigned char *) value, 3);
    c = func_020a87a8((unsigned char *) value, 4);
    out[0] = b;
    out[1] = c;
    out[2] = a - 6;
    out[3] = value + 6;
    out[4] = value;
}

void func_020a8754(int *r0)
{
    int r1;
    int r2;

    r1 = 0;
    r2 = ~r1;
    r0[0] = r2;
    r0[1] = r2;
    r0[2] = r1;
    r0[3] = r1;
}

void func_020a8750(void *object) {}

void func_020a873c(UnkStruct020a873c *a, unsigned char *out)
{
    *out = (unsigned char) func_020a87c8((unsigned char *) a->ptr, 0);
}

void func_020a8718(void *arg0, unsigned char *arg1, unsigned char *arg2)
{
    unsigned char *r4;
    unsigned char *r6;
    void *r5;
    unsigned char temp;

    r5 = arg0;
    r4 = arg1;
    r6 = arg2;

    temp = (unsigned char) func_020a87c8((unsigned char *) (*(void **) ((unsigned int) r5 + 0xc)), 0);
    *r4 = temp;
    temp = (unsigned char) func_020a87c8((unsigned char *) (*(void **) ((unsigned int) r5 + 0xc)), 1);
    *r6 = temp;
}
