/* func_02045bb8 @ 0x02045bb8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(int);
extern int data_020ccf94;

struct entry_02045bb8 {
    unsigned char a : 3;
    unsigned char : 5;
    unsigned char : 2;
    unsigned char b : 3;
    unsigned char pad_02[14];
};

extern struct entry_02045bb8 data_021c7884[];

int func_02045bb8(int a, int b)
{
    struct entry_02045bb8 *p;
    int i;
    int result;

    result = -1;
    if (func_02073d90(data_020ccf94) == 0) {
        a = 0;
    }

    p = data_021c7884;
    for (i = 0; i < 20; p++, i++) {
        if (a == p->a && b == p->b) {
            result = i;
            break;
        }
    }
    return result;
}
