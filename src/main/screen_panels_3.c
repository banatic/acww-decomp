/* screen_panels_3: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208b5ec @ 0x0208b5ec, 0x5c bytes, Thumb
 * func_0208b5b0 @ 0x0208b5b0, 0x3c bytes, Thumb
 * func_0208b56c @ 0x0208b56c, 0x44 bytes, Thumb
 * func_0208b55c @ 0x0208b55c, 0x10 bytes, Thumb
 * func_0208b54c @ 0x0208b54c, 0x10 bytes, Thumb
 * func_0208b53c @ 0x0208b53c, 0x10 bytes, Thumb
 * func_0208b52c @ 0x0208b52c, 0x10 bytes, Thumb
 * func_0208b520 @ 0x0208b520, 0xc bytes, Thumb
 * func_0208b514 @ 0x0208b514, 0xc bytes, Thumb
 * func_0208b508 @ 0x0208b508, 0xc bytes, Thumb
 * func_0208b500 @ 0x0208b500, 0x8 bytes, Thumb
 * func_0208b4f8 @ 0x0208b4f8, 0x8 bytes, Thumb
 * func_0208b4ac @ 0x0208b4ac, 0x4c bytes, Thumb
 * func_0208b478 @ 0x0208b478, 0x34 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    int unk_04;
    char pad_08[0x340];
    unsigned char byte0;
    unsigned char byte1;
    unsigned char byte2;
} UnkStruct_0208b5ec;

struct BigStruct {
    void *unk_00;
    char pad_04[4];
    char sub_8;
    char pad_09[0xe0 - 9];
    char sub_e0;
    char pad_E1[0x1c4 - (0xe0 + 1)];
    char sub_1c4;
    char pad_1C5[0x2c4 - (0x1c4 + 1)];
    char sub_2c4;
};

extern void *func_0208df44(void *);
extern void *func_0208d338(void *);
extern void *func_0208c1dc(void *);
extern void *func_0208bbbc(void *);
extern void *func_0208bb8c(void *p);
extern void *func_0208c1ac(void *p);
extern void *func_0208d2e8(void *p);
extern void *func_0208def4(void *p);
extern void func_020edb3c(void *p);
extern unsigned char data_020e21d4[];
extern unsigned char data_021d3258[];
extern void func_0208b3ac(void *ptr);
extern void func_0208b37c(void *ptr);
extern unsigned char data_021d3598[];
extern int data_021d3338;
extern int data_021d351c;
extern void func_0208b090(void *p);
extern void func_0208dd68(void *p);
extern void func_0208d164(void *p);
extern void func_0208c020(void *p);
extern void func_0208ba30(void *p);
extern void func_0208ba10(void *);
extern void func_0208c008(void *);
extern void func_0208d15c(void *);
extern void func_0208dd60(void *);

void func_0208b4ac(void *p);
void func_0208b478(void *arg0);

UnkStruct_0208b5ec *func_0208b5ec(UnkStruct_0208b5ec *self)
{
    self->unk_00 = ((unsigned char *) data_020e21d4);
    self->unk_04 = 0;
    func_0208df44((char *) self + 8);
    func_0208d338((char *) self + 0xe0);
    func_0208c1dc((char *) self + 0x1c4);
    func_0208bbbc((char *) self + 0x2c4);
    self->byte0 = 0;
    self->byte1 = 0;
    self->byte2 = 0;
    return self;
}

struct BigStruct *func_0208b5b0(struct BigStruct *self)
{
    self->unk_00 = (void *) ((char *) data_020e21d4);
    func_0208bb8c(&self->sub_2c4);
    func_0208c1ac(&self->sub_1c4);
    func_0208d2e8(&self->sub_e0);
    func_0208def4(&self->sub_8);
    return self;
}

void *func_0208b56c(void *obj)
{
    *(void **) obj = (void *) data_020e21d4;
    func_0208bb8c((char *) obj + 0x2c4);
    func_0208c1ac((char *) obj + 0x1c4);
    func_0208d2e8((char *) obj + 0xe0);
    func_0208def4((char *) obj + 0x8);
    func_020edb3c(obj);
    return obj;
}

void func_0208b55c(void)
{
    func_0208b4ac((void *) data_021d3258);
}

void func_0208b54c(void)
{
    func_0208b478((void *) data_021d3258);
}

void func_0208b53c(void)
{
    func_0208b3ac((void *) data_021d3258);
}

void func_0208b52c(void)
{
    func_0208b37c(((int *) data_021d3258));
}

void func_0208b520(void)
{
    unsigned char *ptr;
    ptr = (unsigned char *) data_021d3598;
    ptr[8] = 1;
}

void func_0208b514(unsigned int value)
{
    ((char *) data_021d3598)[8] = 0;
}

void func_0208b508(void)
{
    data_021d3598[9] = 0;
}

int func_0208b500(void)
{
    return (int) &data_021d3338;
}

int func_0208b4f8(void)
{
    return (int) &data_021d351c;
}

void func_0208b4ac(void *p)
{
    func_0208b514((unsigned int) p);
    func_0208b508();
    func_0208b090(p);
    func_0208dd68((char *) p + 8);
    func_0208d164((char *) p + 0xe0);
    func_0208c020((char *) p + 0x1c4);
    func_0208ba30((char *) p + 0x2c4);
    *((char *) p + 0x34a) = 0;
}

void func_0208b478(void *arg0)
{
    func_0208ba10((char *) arg0 + 0x2c4);
    func_0208c008((char *) arg0 + 0x1c4);
    func_0208d15c((char *) arg0 + 0xe0);
    func_0208dd60((char *) arg0 + 8);
}
