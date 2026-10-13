/* func_02060bf8 @ 0x02060bf8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02060c60(int x);

typedef struct {
    unsigned char pad_00[0x15a0];
    unsigned int : 18;
    unsigned int field : 6;
    unsigned int : 8;
} UnkStruct_02060bf8;

int func_02060bf8(UnkStruct_02060bf8 *self, int input, int flag)
{
    int result = func_02060c60(input);
    if (result != 0) {
        if (flag) {
            self->field |= result;
        } else {
            self->field &= ~result;
        }
        return 1;
    } else {
        return 0;
    }
}
