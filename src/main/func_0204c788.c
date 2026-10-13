/* func_0204c788 @ 0x0204c788, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0204c788 UnkStruct_0204c788;
extern int func_0204c7f0(UnkStruct_0204c788 *p);
extern int func_0204c7c8(UnkStruct_0204c788 *p);
extern int func_0204c7c0(void);
extern int func_020afb90(int a);
int func_0204c788(UnkStruct_0204c788 *p)
{
    int v = func_0204c7f0(p);
    if (func_0204c7c8(p) != 0) {
        return v;
    }
    v = v >> func_020afb90(func_0204c7c0() + 0x171b4);
    return v;
}
