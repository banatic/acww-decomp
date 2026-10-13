/* func_02035ff8 @ 0x02035ff8, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035fc0(void *self, int value);

void *func_02035ff8(void *self, int value)
{
    *(int *) self = value;
    func_02035fc0(self, value);
    return self;
}
