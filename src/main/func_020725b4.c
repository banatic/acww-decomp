/* func_020725b4 @ 0x020725b4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char *ptr;
    unsigned char *array[16];
} UnkStruct_020725b4;

extern void *func_02064b18(void *arg);

extern unsigned char data_020e1838[];

void func_020725b4(UnkStruct_020725b4 *param)
{
    if (param->ptr == 0) {
        param->ptr = func_02064b18((void *) data_020e1838);
        if (param->ptr != 0) {
            unsigned int i;
            for (i = 0; i < 16; i++) {
                param->array[i] = param->ptr + (i << 5);
            }
        }
    }
}
