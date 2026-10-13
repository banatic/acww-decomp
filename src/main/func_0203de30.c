/* func_0203de30 @ 0x0203de30, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a40(void *self, void *data);
extern int data_020da994;

void *func_0203de30(void *self)
{
    *(void **) self = &data_020da994;
    func_020a9a40(self, &data_020da994);
    return self;
}
