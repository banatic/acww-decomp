#ifndef CPP_MAIN_BASE_02068144_H
#define CPP_MAIN_BASE_02068144_H

// State machine run by func_02068144 (the update: per-state step by `idx`) and
// func_02067108 (the state entry: runs once when `next` is set, then clears it to 6).
class Base_02068144 {
  public:
    // per-state step
    void func_020670f8();
    void func_02066f2c();
    void func_02066dc4();
    void func_02066cd4();
    void func_02066be0();
    void func_02066bd0();
    // per-state entry
    void func_020670fc();
    void func_02066f8c();
    void func_02066f20();
    void func_02066db0();
    void func_02066c54();
    void func_02066bd4();
    int unk_00;
    int idx;
    unsigned int next;
};

#endif
