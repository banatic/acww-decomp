/* func_02050a10 @ 0x02050a10, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int limit;
    int handle;
} UnkStruct_02050a10;

extern int OS_GetLockID(unsigned int size, int sum);
extern void func_0211ec44(unsigned short value);
extern int CARDi_RequestStreamCommand(unsigned int a, unsigned int b, unsigned int c, int d, int e, int f, int g, int h,
                                      int i);
extern void func_0211ec34(unsigned short value);
extern void OS_ReleaseLockID(unsigned short value);

int func_02050a10(UnkStruct_02050a10 *s, unsigned int a, unsigned int b, unsigned int c)
{
    int success = 1;
    if ((c + b) > s->limit) {
        goto exit;
    }
    s->handle = OS_GetLockID(s->limit, c + b);
    if (s->handle == -3) {
        goto exit;
    }
    func_0211ec44((unsigned short) s->handle);
    if (CARDi_RequestStreamCommand(c, a, b, 0, 0, 0, 6, success, 0) != 0) {
        success = 0;
    }
    func_0211ec34((unsigned short) s->handle);
    OS_ReleaseLockID((unsigned short) s->handle);
    s->handle = -3;
exit:
    return success;
}
