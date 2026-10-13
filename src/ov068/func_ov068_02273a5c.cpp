/* func_ov068_02273a5c @ 0x02273a5c, 0xa8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
int func_0201c2a4(void *self, int arg);
void func_02016108(void *e, int value);
void func_ov068_022746b8(void *e, int param);
void func_ov068_022749dc(void *self, int param);
}

class UnkStruct_02273a5c {
  public:
    virtual void virt0();
    virtual void virt1();
    virtual void virt2();
};

struct UnkStruct_02273a5c_2 {
    char pad_00[0x65c];
    UnkStruct_02273a5c e;  // offset 0x65c
    char pad_660[0xd0];    // 0x660..0x730
    int unk_730;           // offset 0x730
    char pad_734[0x18];    // 0x734..0x74c
    unsigned char unk_74C; // offset 0x74c
};

extern "C" void func_ov068_02273a5c(UnkStruct_02273a5c_2 *self, int cmd)
{
    switch (cmd) {
        case 0:
            self->e.virt2();
            {
                int v = func_0201c2a4(self, 4);
                func_02016108(&self->e, v);
            }
            if (self->unk_730 == 7) {
                func_ov068_022746b8(&self->e, 0);
            }
            func_ov068_022749dc(self, 1);
            break;
        case 1:
            self->e.virt2();
            {
                int v = func_0201c2a4(self, 4);
                func_02016108(&self->e, v);
            }
            if (self->unk_74C != 0) {
                func_ov068_022746b8(&self->e, 1);
            } else {
                func_ov068_022746b8(&self->e, 2);
            }
            func_ov068_022749dc(self, 3);
            break;
        case 8:
            func_ov068_022749dc(self, 0);
            break;
        default:
            break;
    }
}
