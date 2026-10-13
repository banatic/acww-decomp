/* func_02021b4c @ 0x02021b4c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02021b4c {
    char pad_00[0x830];
    int value;
} UnkStruct_02021b4c;

typedef struct UnkStruct_02021b4c_2 {
    char pad_00[0x100];
    UnkStruct_02021b4c *ptr;
} UnkStruct_02021b4c_2;

extern void func_02021b8c(void);
extern int func_02021ea8(int a, int b, int c, void (*fp)(void));
extern int func_02081d64(void);
extern void func_02015e70(void *a, int b, int c);

int func_02021b4c(UnkStruct_02021b4c_2 *a, int b, int c)
{
    int result = func_02021ea8(a->ptr->value, b, c, func_02021b8c);
    if (result != 0) {
        func_02015e70(a, func_02081d64(), 9);
    }
    return result;
}
