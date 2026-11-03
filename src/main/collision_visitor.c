/* collision_visitor: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02031e74 @ 0x02031e74, 0xc bytes, Thumb
 * func_02031e68 @ 0x02031e68, 0xc bytes, Thumb
 * func_02031e64 @ 0x02031e64, 0x2 bytes, Thumb
 * func_02031e60 @ 0x02031e60, 0x2 bytes, Thumb
 * func_02031e5c @ 0x02031e5c, 0x2 bytes, Thumb
 */

extern int data_020da1c0;

void func_02031e74(unsigned int *p)
{
    *p = (unsigned int) &data_020da1c0;
}

void func_02031e68(char **ptr)
{
    *ptr = ((char *) &data_020da1c0);
}

void func_02031e64(void) {}

void func_02031e60(void) {}

void func_02031e5c(void) {}
