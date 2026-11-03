/* joint_blend_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02056f04 @ 0x02056f04, 0x24 bytes, Thumb
 * func_02056ee0 @ 0x02056ee0, 0x24 bytes, Thumb
 * func_02056ed4 @ 0x02056ed4, 0xc bytes, Thumb
 * func_02056ebc @ 0x02056ebc, 0x18 bytes, Thumb
 * func_02056eb0 @ 0x02056eb0, 0xc bytes, Thumb
 */

typedef struct {
    void *data;        // 0x00
    char buffer[0x24]; // 0x04
    char pad_28[12];   // 0x28
    int unk_34;        // 0x34
    int unk_38;        // 0x38
} UnkStruct_02056f04;

typedef struct {
    void *data;
    unsigned char bytes[0x24];
    unsigned char pad_28[0xc];
    int unk_34;
    int unk_38;
} TStruct;

extern void MI_CpuFill8(void *s, int c, unsigned int n);
extern void func_020edb3c(unsigned int *);
extern unsigned char data_020dd174[];

UnkStruct_02056f04 *func_02056f04(UnkStruct_02056f04 *self)
{
    self->data = (void *) ((char *) data_020dd174);
    MI_CpuFill8(self->buffer, 0, 0x24);
    self->unk_34 = 0;
    self->unk_38 = 0;
    return self;
}

TStruct *func_02056ee0(TStruct *this)
{
    this->data = ((int *) data_020dd174);
    MI_CpuFill8(this->bytes, 0, 0x24);
    this->unk_34 = 0;
    this->unk_38 = 0;
    return this;
}

void func_02056ed4(int *out)
{
    *out = (int) ((int *) data_020dd174);
}

unsigned int *func_02056ebc(unsigned int *arg)
{
    *arg = (unsigned int) data_020dd174;
    func_020edb3c(arg);
    return arg;
}

void func_02056eb0(void **ptr)
{
    *ptr = ((int *) data_020dd174);
}
