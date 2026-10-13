#ifndef CPP_MAIN_BASE_02038828_H
#define CPP_MAIN_BASE_02038828_H

struct Base_02038828 {
    virtual ~Base_02038828();
    unsigned char pad_04[0xbc - 4];
    int unk_BC;
    unsigned char pad_C0[0xc9 - 0xc0];
    unsigned char unk_C9;

    void func_020382d0();
    void func_0203827c();
    void func_0203822c();
    void func_020381d8();
    void func_020380f4();
    void func_020380a8();
    void func_02037fe8();
    void func_02037fa8();

    typedef void (Base_02038828::*PMF)();
};

#endif
