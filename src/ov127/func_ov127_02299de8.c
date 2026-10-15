/* func_ov127_02299de8 @ 0x02299de8, 0x74 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov127_0229b5f4[4];
extern int data_ov127_0229b604[4];

typedef struct {
    int a;
    int b;
} UnkStruct_02299de8;

extern UnkStruct_02299de8 data_ov127_0229b614[4];

extern int func_020896b8(int, UnkStruct_02299de8 *, int, int, int, int, int);

#pragma opt_loop_invariants off
void func_ov127_02299de8(unsigned char *obj, int a2, int a3)
{
    int local = 0;
    int i;
    int fifth;

    for (i = 0; i < 4; i++) {
        if (i == obj[0x2834]) {
            fifth = 7;
        } else {
            fifth = a3;
        }

        func_020896b8(1, &data_ov127_0229b614[i], data_ov127_0229b5f4[i] * (a2 >> 2) + 0x80,
                      data_ov127_0229b604[i] * (a2 >> 2) + 0x60, fifth, 1, local);
    }
    obj[0x2834] = 4;
}
