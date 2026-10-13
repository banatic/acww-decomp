#ifndef CPP_OV002_ANIMSTATE_H
#define CPP_OV002_ANIMSTATE_H

// State object embedded in many scene objects; its mode helpers live in
// ov002 and are plain C functions taking the object pointer.
struct AnimState {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};

extern "C" {
// Sets the mode unless it is already active (6 and 12 always restart).
void func_ov002_0220a374(void *state, int mode);
// Folds a transient mode back to its resting mode.
void func_ov002_0220a0ec(void *state);
}

#endif
