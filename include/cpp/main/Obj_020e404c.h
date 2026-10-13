#ifndef CPP_MAIN_OBJ_020E404C_H
#define CPP_MAIN_OBJ_020E404C_H

class Obj_020e404c {
  public:
    // embedded object; only its third virtual slot is called here
    struct Part {
        virtual void vfunc_00();
        virtual void vfunc_04();
        virtual void vfunc_08();
    };

    void func_020aa13c();
    void func_020a9fac();
    void func_020a9ebc();
    void func_020a9e04();
    char pad_00[8];
    int unk_08;
    Part sub;
};

#endif
