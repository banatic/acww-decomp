/* func_ov004_02213938 @ 0x02213938, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_022110e4(char *argument0);
extern void *data_ov004_02251c6c;
extern void *data_ov004_02251d18;

void *func_ov004_02213938(char *self)
{
    func_ov004_022110e4(self);
    *(void **) (self) = &data_ov004_02251c6c;
    *(void **) (self + 0xec) = &data_ov004_02251d18;
    *(short *) (self + 0x844) = -1;
    return self;
}
