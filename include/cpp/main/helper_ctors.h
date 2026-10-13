#ifndef CPP_MAIN_HELPER_CTORS_H
#define CPP_MAIN_HELPER_CTORS_H

// Out-of-line constructors and destructors of small polymorphic helper
// objects. Each pair installs the same vtable; callers keep the object on
// the stack and run the pair by hand, so they are plain C functions here.
extern "C" {
void *func_02094fd4(void *self); // vtable data_020e2f6c
void *func_02094fbc(void *self);
void *func_02094f7c(void *self); // vtable data_020e2f54
void *func_02094f64(void *self);
void *func_020b5630(void *self); // vtable data_020e5218
void *func_020b5618(void *self);
void *func_020b55d0(void *self); // vtable data_020e51d0
void *func_020b55b8(void *self);
void *func_020821bc(void *self); // vtable data_020e1904
void *func_020821a4(void *self);
void func_02063e98(void *self); // vtable data_020de664
void func_02063e8c(void *self);
}

#endif
