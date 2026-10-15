/* func_02028648 @ 0x02028648, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02028648_3 {
    u8 pad_00[0x40];
    void *unk_40;
} UnkStruct_02028648_3;
typedef struct UnkStruct_02028648 {
    unsigned int w[8];
    u8 a;
    u8 b;
} UnkStruct_02028648;
typedef struct UnkStruct_02028648_2 {
    int a, b;
} UnkStruct_02028648_2;

extern int data_021c2a34, data_021c2a4c, data_021c2a1c;
extern const UnkStruct_02028648_2 data_020d9140;

extern unsigned int func_0202d9c4(UnkStruct_02028648_3 *c);
extern int func_0209bc40(unsigned char *);
extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098eb8(int);
extern int func_0209a1e8(void);
extern void func_0201cfb4(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w);
extern void func_0201cf90(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w, int i, int a, int b, void *p);
extern void func_0201cec8(UnkStruct_02028648_3 *c, UnkStruct_02028648 *w);
extern void func_0202da74(UnkStruct_02028648_3 *c, UnkStruct_02028648_2 s);
extern void func_02068388(void *h, int n);

void func_02028648(UnkStruct_02028648_3 *c)
{
    UnkStruct_02028648 w;
    void *p;

    p = &data_021c2a34;
    switch (func_0209bc40((unsigned char *) func_0202d9c4(c))) {
        case 0xa:
            if (func_020984e8()) {
                if (func_02098eb8((int) func_02099734((int) func_020984e8())) != -1) {
                    p = &data_021c2a4c;
                }
            }
            break;
        case 0x13:
            if (func_0209a1e8() != -1) {
                p = &data_021c2a4c;
            }
            break;
    }
    func_0201cfb4(c, &w);
    func_0201cf90(c, &w, 0, 0x21, 0x21, p);
    func_0201cf90(c, &w, 1, 0x22, 0x22, &data_021c2a1c);
    w.a = 2;
    w.b = w.a - 1;
    func_0201cec8(c, &w);
    func_0202da74(c, data_020d9140);
    func_02068388(c->unk_40, 1);
}
