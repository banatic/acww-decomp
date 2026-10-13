/* func_02088a78 @ 0x02088a78, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(void *);

void func_02088a78(void *param)
{
    unsigned char local[3];
    func_0209df64(local);
    ((unsigned char *) param)[2] = local[2];
    ((unsigned char *) param)[1] = local[1];
    ((unsigned char *) param)[0] = local[0];
}
