#ifndef CPP_MAIN_OBJ_020E406C_H
#define CPP_MAIN_OBJ_020E406C_H

class Obj_020e406c {
  public:
    // embedded object; only its third virtual slot is called here
    struct Part {
        virtual void vfunc_00();
        virtual void vfunc_04();
        virtual void vfunc_08();
    };

    void func_020aa660();
    void func_020aa4f4();
    void func_020aa420();
    void func_020aa360();
    char pad_00[8];
    int unk_08;
    Part sub;
};

#endif
