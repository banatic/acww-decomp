#ifndef CPP_MAIN_BASE_020B8B88_H
#define CPP_MAIN_BASE_020B8B88_H

// Object whose update (func_020b8b88) runs one of four state handlers by `index`.
class Base_020b8b88 {
  public:
    // embedded object; only its fourth virtual slot is called here
    struct Part {
        virtual void vfunc_00();
        virtual void vfunc_04();
        virtual void vfunc_08();
        virtual void vfunc_0c();
    };

    void func_020b87ac();
    void func_020b8744();
    void func_020b86e4();
    void func_020b866c();
    char pad_00[4];
    int index;
    Part sub;
    char pad_0C[0x10d - 0x0c];
    unsigned char flag;
};

#endif
