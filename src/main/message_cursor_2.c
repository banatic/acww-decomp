/* message_cursor_2: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b4ca4 @ 0x020b4ca4, 0x34 bytes, Thumb
 * func_020b4c84 @ 0x020b4c84, 0x20 bytes, Thumb
 * func_020b4c5c @ 0x020b4c5c, 0x28 bytes, Thumb
 * func_020b4c40 @ 0x020b4c40, 0x1c bytes, Thumb
 */

typedef struct {
    volatile unsigned int unk_00;
    char pad_04[0x20];
    volatile int unk_24;
    volatile int unk_28;
    volatile int unk_2C;
    volatile int unk_30;
    volatile unsigned char unk_34;
    char pad_35[3];
    volatile int unk_38;
    volatile int unk_3C;
} UnkStruct_020b4ca4;

extern void *func_020a9484(void *);
extern unsigned char data_020e3e68[];
extern unsigned char data_020e5254[];
extern void *func_020a941c(void *);
extern void func_020edb3c(void *);
extern void func_020a94a4(void *);

UnkStruct_020b4ca4 *func_020b4ca4(UnkStruct_020b4ca4 *this)
{
    func_020a9484(this);
    this->unk_00 = (unsigned int) data_020e3e68;
    this->unk_00 = (unsigned int) data_020e5254;
    this->unk_24 = 0;
    this->unk_28 = 0;
    this->unk_2C = 0;
    this->unk_30 = 0;
    this->unk_34 = 0;
    this->unk_38 = 0;
    this->unk_3C = 0;
    return this;
}

void *func_020b4c84(void *obj)
{
    volatile void **p = (volatile void **) obj;
    *p = (void *) ((char *) data_020e5254);
    *p = (void *) ((char *) data_020e3e68);
    func_020a941c(obj);
    return obj;
}

void *func_020b4c5c(void *arg)
{
    *(void **) arg = ((char *) data_020e5254);
    *(void **) arg = ((char *) data_020e3e68);
    func_020a941c(arg);
    func_020edb3c(arg);
    return arg;
}

void func_020b4c40(void *r0)
{
    unsigned int *p = (unsigned int *) r0;
    unsigned char *b = (unsigned char *) r0;

    p[9] = 0;  // offset 0x24
    p[10] = 0; // offset 0x28
    p[11] = 0; // offset 0x2c
    p[12] = 0; // offset 0x30
    b[0x34] = 0;
    p[14] = 0; // offset 0x38
    p[15] = 0; // offset 0x3c

    func_020a94a4(r0);
}
