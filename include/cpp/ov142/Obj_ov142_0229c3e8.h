#ifndef CPP_OV142_OBJ_OV142_0229C3E8_H
#define CPP_OV142_OBJ_OV142_0229C3E8_H

#include "cpp/ov002/Obj_ov002_0220bb24.h"

// Scene of ov142 (vtable 0x0229c3e8).
class Obj_ov142_0229c3e8 : public Obj_ov002_0220bb24 {
  public:
    virtual ~Obj_ov142_0229c3e8();
    virtual int func_ov142_0229bea0();

    // states run by func_ov142_0229bd90, indexed by subState
    void func_ov142_0229b700();
    void func_ov142_0229b6cc();
    void func_ov142_0229b698();
    void func_ov142_0229b670();
    void func_ov142_0229b5e8();
    void func_ov142_0229b59c();
    void func_ov142_0229b55c();
    void func_ov142_0229b528();
    void func_ov142_0229b500();
    void func_ov142_0229b4cc();
    void func_ov142_0229b4a8();
    void func_ov142_0229b43c();
    void func_ov142_0229b394();
    void func_ov142_0229b290();

    // states run by func_ov142_0229bea0, indexed by state
    void func_ov142_0229bcfc();
    void func_ov142_0229bc9c();
    void func_ov142_0229bc64();
    void func_ov142_0229bc34();
    void func_ov142_0229bbf4();
    void func_ov142_0229bbc4();
    void func_ov142_0229bb84();
    void func_ov142_0229bb54();

    // dispatchers and helpers
    void func_ov142_0229bd90();
    void func_ov142_0229b99c();
    void func_ov142_0229b974();
    // update: runs the handlers between the two frame helpers
    int func_ov142_0229bd74();
};

#endif
