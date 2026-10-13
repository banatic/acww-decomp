/* func_020f4c4c @ 0x020f4c4c, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void ENV_AppendResourceSet(void *);

void func_020f4c4c(void *r0)
{
    ENV_AppendResourceSet((char *) r0 + 4);
    *(unsigned short *) ((char *) r0 + 8) = 0;
    *(unsigned char *) ((char *) r0 + 10) = 0;
}
