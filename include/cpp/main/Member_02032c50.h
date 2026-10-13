#ifndef CPP_MAIN_MEMBER_02032C50_H
#define CPP_MAIN_MEMBER_02032C50_H

// Member object with an out-of-line destructor (func_02032c50, which destroys a part
// at 0xc); only part of its size is known.
struct Member_02032c50 {
    ~Member_02032c50();
    char pad_00[0x10];
};

#endif
