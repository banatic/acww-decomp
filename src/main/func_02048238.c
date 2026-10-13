/* func_02048238 @ 0x02048238, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02048298(int, int, int, int, int, int);
extern void func_02042efc(void *p);

typedef struct {
    char pad_00[0xe];
    unsigned char cnt;
} GlobalA;

typedef struct {
    char pad_00[0x30];
    signed int field : 4;
} GlobalB;

extern GlobalA data_021c79e4;
extern GlobalB data_021c79c4;

extern unsigned char data_021c80b4[];

void func_02048238(int a0, int a1, int a2, int a3)
{
    int count = data_021c79e4.cnt;
    int i = 0;

    while (i < 4) {
        if (count <= 0) {
            return;
        }
        if (((1 << i) & data_021c79c4.field) == 0) {
            if (func_02048298(a0, a1, a2, a3, i, count)) {
                count--;
            }
        }
        i++;
    }

    func_02042efc((void *) data_021c80b4);
}
