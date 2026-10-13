/* func_020a887c @ 0x020a887c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9b44(void *);
extern unsigned int data_020e3d7c;
extern unsigned int data_020da6c4;

void *func_020a887c(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e3d7c;
    func_020a9b44((char *) self + 4);
    *(unsigned int *) self = (unsigned int) &data_020da6c4;
    return self;
}
