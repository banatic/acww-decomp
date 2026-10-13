#ifndef CPP_OV048_OBJ_OV048_02264298_H
#define CPP_OV048_OBJ_OV048_02264298_H

// ov048's scene (vtable 0x02264298, 0xe74 bytes; main base vtable 0x020d8c64,
// destructor func_0202ee5c). Holds an Obj_ov048_02264208 at 0x658.
class Obj_ov048_02264298 {
  public:
    virtual ~Obj_ov048_02264298();

    // states run by func_ov048_02262db0
    int func_ov048_02263238();
    int func_ov048_022631cc();
    int func_ov048_02263174();
    int func_ov048_02263084();
    int func_ov048_02262f58();
    int func_ov048_02262e94();

    // dispatchers and helpers
    int func_ov048_02262db0();

    char pad_04[0xe71 - 0x04];
    unsigned char unk_E71; // step of the setup sequence
    char pad_e72[2];
};

#endif
