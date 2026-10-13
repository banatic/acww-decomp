#ifndef CPP_MAIN_MEMBER_020B33B8_H
#define CPP_MAIN_MEMBER_020B33B8_H

// Member object with an out-of-line destructor (func_020b33b8), which destroys its
// own parts at 0x34, 0x18, 0x14 and 0. Its owner keeps byte fields right after
// its first 0x41 bytes.
struct Member_020b33b8 {
    ~Member_020b33b8();
    char pad_00[0x41];
};

#endif
