/* ENV_AppendResourceSet @ 0x020eed48, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern int func_0210b7e0(void *self);

int ENV_AppendResourceSet(void *self)
{
    if (self == 0) {
        OS_Terminate();
    }
    return func_0210b7e0(self);
}
