/* func_020ab5f8 @ 0x020ab5f8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab71c(void *p);

typedef struct {
    char data[0x90];
} UnkStruct_020ab5f8_2;

typedef struct {
    UnkStruct_020ab5f8_2 elements[5];
    int count;
} UnkStruct_020ab5f8;

void func_020ab5f8(UnkStruct_020ab5f8 *arg)
{
    int i;
    for (i = 0; i < arg->count; i++) {
        func_020ab71c(&arg->elements[i]);
    }
}
