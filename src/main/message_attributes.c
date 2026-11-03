/* message_attributes: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a9b50 @ 0x020a9b50, 0x20 bytes, Thumb
 * func_020a9b44 @ 0x020a9b44, 0xc bytes, Thumb
 * func_020a9b2c @ 0x020a9b2c, 0x18 bytes, Thumb
 * func_020a9b1c @ 0x020a9b1c, 0xe bytes, Thumb
 * func_020a9b04 @ 0x020a9b04, 0x18 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
} UnkStruct_020a9b50;

extern unsigned char data_021f43ec;
extern void func_020edb3c(void *arg);
extern unsigned char data_020e3d24[];

void func_020a9b50(UnkStruct_020a9b50 *p)
{
    p->unk_00 = ((char *) data_020e3d24);
    p->unk_04 = -1;
    p->unk_08 = data_021f43ec;
    p->unk_09 = data_021f43ec;
}

void func_020a9b44(char **ptr)
{
    *ptr = ((char *) data_020e3d24);
}

void *func_020a9b2c(void *arg)
{
    void **pp = (void **) arg;
    *pp = (void *) data_020e3d24;
    func_020edb3c(arg);
    return arg;
}

void func_020a9b1c(void *r0, const void *r1)
{
    *(unsigned int *) ((char *) r0 + 4) = *(const unsigned int *) ((const char *) r1 + 4);
    *(unsigned char *) ((char *) r0 + 8) = *(const unsigned char *) ((const char *) r1 + 8);
    *(unsigned char *) ((char *) r0 + 9) = *(const unsigned char *) ((const char *) r1 + 9);
}

void func_020a9b04(unsigned int *r0)
{
    unsigned int r1;
    unsigned char r2;

    r1 = 0;
    r1 = ~r1;
    r0[1] = r1;

    r2 = data_021f43ec;
    *((unsigned char *) r0 + 8) = r2;

    r1 = data_021f43ec;
    *((unsigned char *) r0 + 9) = (unsigned char) r1;
}
