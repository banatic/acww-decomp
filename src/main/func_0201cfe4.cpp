/* func_0201cfe4 @ 0x0201cfe4, 0x15c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201cfe4;
typedef void (UnkStruct_0201cfe4::*PMF)(int);

extern PMF __ptmf_null;
extern unsigned char data_021f43f8;
extern unsigned char data_021f43e8;

extern "C" {
extern int func_0201d198(UnkStruct_0201cfe4 *self, unsigned int idx);
extern void RtcSendPxiCommand(int command);
extern int func_0207e054(int a, int b, int c);
extern int func_02081a88(int a);
extern void func_02078864(int a, int b, int c);
extern int func_0207d4bc(int a, int b);
extern void *func_0201ce50(void *obj);
}

class UnkStruct_0201cfe4 {
  public:
    unsigned char pad_00[0x40];
    unsigned char *data;
    unsigned char pad_44[0xc0 - 0x44];
    PMF pmf_c0;
    PMF pmf_c8;
    unsigned char pad_D0[0x100 - 0xd0];
    void *obj;
    unsigned char pad_104[0x128 - 0x104];
    int id128;
    int unk_12C;
    unsigned char pad_130[0x134 - 0x130];
    int unk_134;
    unsigned char pad_138[0x15a - 0x138];
    unsigned short flag;
};

extern "C" void func_0201cfe4(UnkStruct_0201cfe4 *self, int event)
{
    unsigned char id_slot;
    *(volatile unsigned char *) &id_slot = self->data[0x1e77];

    if (func_0201d198(self, event) == 0) {
        if (self->flag != 0) {
            RtcSendPxiCommand(self->flag);
            self->flag = 0;
        }

        unsigned char id = id_slot;
        if (id == data_021f43f8) {
            if (self->pmf_c0) {
                (self->*self->pmf_c0)(event);
            }
        } else if (id == data_021f43e8) {
            if (self->pmf_c8) {
                (self->*self->pmf_c8)(event);
                self->pmf_c8 = __ptmf_null;
            }
        }
    }

    if (id_slot == data_021f43e8) {
        if (self->unk_12C != 0) {
            func_0207e054(*(int *) ((char *) self->obj + 0x830), self->unk_12C, 0);
            if (self->id128 != -1) {
                func_02078864(*(int *) ((char *) self->obj + 0x830), self->id128, func_02081a88(self->unk_12C));
            }
            if (*(int *) ((char *) self->obj + 0x830) != 0) {
                func_0207d4bc(*(int *) ((char *) self->obj + 0x830), 0);
            }
        }
        if (self->unk_134 != 0) {
            if (func_0201ce50(self->obj) != 0) {
                func_0207e054(*(int *) ((char *) func_0201ce50(self->obj) + 0x830), self->unk_134, 0);
            }
        }
    }
}
