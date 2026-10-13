/* func_020933c0 @ 0x020933c0, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8ed8(int a, int b);

typedef struct OtherStruct {
    char pad_00[0x20];
    short result;
} OtherStruct;

typedef struct UnkStruct_020933c0 {
    char pad_00[8];
    OtherStruct *ptr;
    char pad_0C[48];
    short short1;
    char pad_3E[2];
    short short2;
    char pad_42[54];
    int flag;
} UnkStruct_020933c0;

void func_020933c0(UnkStruct_020933c0 *a, int b)
{
    if (b == 1) {
        OtherStruct *p = a->ptr;
        if (p != 0) {
            p->result = func_020e8ed8(a->short1, a->short2);
            a->flag = 0;
        }
    }
}
