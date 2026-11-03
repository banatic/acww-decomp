/* villager_state: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207918c @ 0x0207918c, 0x18 bytes, Thumb
 * func_02079174 @ 0x02079174, 0x18 bytes, Thumb
 * func_0207915c @ 0x0207915c, 0x18 bytes, Thumb
 * func_02079144 @ 0x02079144, 0x18 bytes, Thumb
 */

extern int func_02079350(void);

int func_0207918c(void)
{
    int result;
    result = func_02079350();
    return *(signed char *) (result + 0x16c);
}

void func_02079174(unsigned char arg0)
{
    unsigned char *ptr;
    unsigned int offset;

    ptr = (unsigned char *) func_02079350();
    offset = 0x164;
    ptr[offset] = arg0;
}

int func_0207915c(void)
{
    int result;
    result = func_02079350();
    return ((signed char *) result)[0x164];
}

void func_02079144(void)
{
    int *ptr;
    int value;

    ptr = (int *) func_02079350();
    value = 0;
    ptr[0x5A] = value;
}
