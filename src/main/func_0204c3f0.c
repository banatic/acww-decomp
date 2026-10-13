/* func_0204c3f0 @ 0x0204c3f0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0204c3f0 UnkStruct_0204c3f0;
extern int func_0204c3c8(UnkStruct_0204c3f0 *p);
extern void func_0204c3a0(UnkStruct_0204c3f0 *p);
extern int func_0204fa68(void);
int func_0204c3f0(UnkStruct_0204c3f0 *p)
{
    if (func_0204c3c8(p) != 0) {
        func_0204c3a0(p);
        switch (func_0204fa68()) {
            case 1:
                return 0;
            case 3:
                return 1;
            case 2:
                return 2;
            case 0:
                return 3;
        }
    }
    return 4;
}
