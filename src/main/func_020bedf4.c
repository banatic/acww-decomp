/* func_020bedf4 @ 0x020bedf4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the fill value is read through a volatile stack local so it is reloaded from the stack each iteration; a plain local is hoisted into a register */

extern void func_020becbc(void *self, int arg);
extern void *MI_CpuFill8(void *dst, int value, unsigned int size);
extern unsigned short data_020d22c0;
typedef struct {
    int unk_00;
    int unk_04;
    unsigned short unk_08;
    unsigned short arr[15];
    unsigned char buf[0x20];
} UnkStruct_020bedf4;
UnkStruct_020bedf4 *func_020bedf4(UnkStruct_020bedf4 *self)
{
    volatile unsigned short v;
    unsigned short *end;
    unsigned short *dst;
    self->unk_00 = 0;
    self->unk_08 = 0;
    func_020becbc(self, -1);
    end = (unsigned short *) (((char *) self) + 0x28);
    dst = (unsigned short *) (((char *) self) + 0xa);
    v = data_020d22c0;
    while (dst < end) {
        *(dst++) = v;
    }

    MI_CpuFill8(((char *) self) + 0x28, 0, 0x20);
    return self;
}
