/* text_chars: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a798c @ 0x020a798c, 0x8 bytes, Thumb
 * func_020a7984 @ 0x020a7984, 0x8 bytes, Thumb
 */

extern int func_02050c78(unsigned char *, int);
extern unsigned short func_02050c58(void *, void *);

int func_020a798c(unsigned char *argument0, int argument1)
{
    return func_02050c78((unsigned char *) argument0, (int) argument1);
}

unsigned short func_020a7984(void *argument0, void *argument1)
{
    return func_02050c58((void *) argument0, (void *) argument1);
}
