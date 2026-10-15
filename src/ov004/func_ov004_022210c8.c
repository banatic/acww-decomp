/* func_ov004_022210c8 @ 0x022210c8, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *argument0, int argument1, int argument2, int argument3, int argument4, short argument5,
                         short argument6, int argument7, int argument8, unsigned short argument9, unsigned short argument10);

int func_ov004_022210c8(int param)
{
    func_02019d0c((void *) ((void *) (param + 0x564)), (int) ((int) (1)), (int) ((int) (1)), (int) ((int) (0)),
                  (int) ((int) (0)), (short) ((short) (0)), (short) ((short) (0)), (int) ((int) (0)), (int) ((int) (0)),
                  (unsigned short) ((unsigned short) (data_020c80f8)), (unsigned short) ((unsigned short) (0)));
    return 1;
}
