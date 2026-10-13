#ifndef CPP_OV047_OBJ_OV047_02262C14_H
#define CPP_OV047_OBJ_OV047_02262C14_H

// ov047's scene: a main-module scene class (vtable 0x020d8bd4 family) whose per-frame
// virtual picks a state handler through a pointer-to-member table.
class Obj_ov047_02262c14 {
  public:
    virtual ~Obj_ov047_02262c14();
    virtual void func_ov047_02260b14(int arg);

    // state handlers
    void func_ov047_022608f8(int arg);
    void func_ov047_02260a88(int arg);

    char pad_04[0xac];
    int unk_B0;
};

#endif
