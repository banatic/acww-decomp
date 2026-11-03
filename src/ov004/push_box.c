/* push_box: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220e008 @ 0x0220e008, 0x20 bytes, Thumb
 * func_ov004_0220dff0 @ 0x0220dff0, 0x18 bytes, Thumb
 * func_ov004_0220dfe8 @ 0x0220dfe8, 0x6 bytes, Thumb
 * func_ov004_0220dfe0 @ 0x0220dfe0, 0x8 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[156];
    unsigned long unk_9C;
} UnkStruct_0220dfe8;

extern void *func_02032564(void *self);
extern char data_ov004_0224fe0c;
extern void *func_0203248c(void *);

void func_ov004_0220dfe0(int p0);

void *func_ov004_0220e008(void *self)
{
    func_02032564(self);
    *(void **) self = (void *) &data_ov004_0224fe0c;
    func_ov004_0220dfe0((int) self);
    return self;
}

void *func_ov004_0220dff0(void *arg)
{
    *((void **) arg) = ((int *) &data_ov004_0224fe0c);
    func_0203248c(arg);
    return arg;
}

void func_ov004_0220dfe8(UnkStruct_0220dfe8 *p, unsigned long v)
{
    p->unk_9C = v;
}

void func_ov004_0220dfe0(int p0)
{
    *(int *) ((char *) (((int) (p0) + (156))) + (0)) = 0;
}
