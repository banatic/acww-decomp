#ifndef CPP_MAIN_BASE_02027460_H
#define CPP_MAIN_BASE_02027460_H

struct Out_02027460 {
    int n;
    unsigned char b;
};

class Base_02027460 {
  public:
    typedef void (Base_02027460::*Pmf)(Out_02027460 *);
    void func_020274e0();
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x12c - 0xb8];
    int unk_12C;
};

#endif
