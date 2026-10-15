/* func_0206d83c @ 0x0206d83c, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0206d83c {
    u8 b[0xa14];
};
struct UnkStruct_0206d83c_2 {
    u8 pad_00[0xe];
    u16 buf[0x503];
};

extern u16 data_021ce3f4[];
extern int data_021ce2f4;
extern int data_020df1f8;

extern void *func_0206d9d8(struct UnkStruct_0206d83c *);
extern void *func_0206d964(struct UnkStruct_0206d83c_2 *);
extern void func_020a8c1c(struct UnkStruct_0206d83c *);
extern int func_0206d97c(struct UnkStruct_0206d83c *, void *, int);
extern int func_020a87e0(struct UnkStruct_0206d83c_2 *, struct UnkStruct_0206d83c *);
extern int func_02051ce0(u16 *, int, int);
extern void *func_0206d94c(struct UnkStruct_0206d83c_2 *);
extern void *func_0206d9c0(struct UnkStruct_0206d83c *);

void func_0206d83c(void)
{
    struct UnkStruct_0206d83c o1;
    struct UnkStruct_0206d83c_2 o2;
    int j;
    int i;
    int count;
    int n;
    u16 *out;
    u16 *p;

    func_0206d9d8(&o1);
    func_0206d964(&o2);
    count = 0;
    out = data_021ce3f4;
    data_021ce2f4 = 0;
    for (i = 0; i < 0x2d; i++) {
        func_020a8c1c(&o1);
        func_0206d97c(&o1, &data_020df1f8, i);
        func_020a87e0(&o2, &o1);
        p = o2.buf;
        while (*p != 0) {
            n = func_02051ce0(p, 3, 0);
            if (n != 0) {
                if (count < 1000) {
                    for (j = 0; j < n; j++) {
                        out[j] = p[j];
                    }
                    for (; j < 3; j++) {
                        out[j] = 0;
                    }
                    out += 3;
                }
                count++;
            }
            p += n + 1;
        }
        data_021ce2f4 = count;
    }
    func_0206d94c(&o2);
    func_0206d9c0(&o1);
}
