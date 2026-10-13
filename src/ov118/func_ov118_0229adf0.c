/* func_ov118_0229adf0 @ 0x0229adf0, 0x1c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov118_0229a450(void *self, int flag, unsigned short value);

typedef struct {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
} FuncoV118;

void func_ov118_0229adf0(FuncoV118 *self, unsigned short value)
{
    unsigned short tmp;
    self->unk_98 = value;
    tmp = self->unk_98;
    self->unk_9A = tmp;
    func_ov118_0229a450(self, 0x10, tmp);
}
