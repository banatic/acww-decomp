/* func_0203a2bc @ 0x0203a2bc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern void func_020edb3c(void *);

extern unsigned char data_020da610[];
extern unsigned char data_020da6c4[];

void *func_0203a2bc(void *obj)
{
    *((unsigned int *) obj) = (unsigned int) data_020da610;
    *((unsigned int *) obj) = (unsigned int) data_020da6c4;
    func_020edb3c(obj);
    return obj;
}
