/* func_ov092_022994a0 @ 0x022994a0, 0x24 bytes, Thumb, module ov092
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int argument0);
extern void *func_ov002_0220830c(void *argument0);
extern void *data_ov092_02299508;

void *func_ov092_022994a0(void)
{
    // DECLS
    char *self;
    // ENDDECLS
    self = (char *) func_ov002_02207f80(0x94);
    if (self != 0) {
        func_ov002_0220830c(self);
        *(void **) (self) = &data_ov092_02299508;
    }
    return self;
}
