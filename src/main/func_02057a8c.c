/* func_02057a8c @ 0x02057a8c, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02057ac0(void *);

unsigned int func_02057a8c(void *param)
{
    return func_02057ac0(*(void **) ((char *) param + 0x14));
}
