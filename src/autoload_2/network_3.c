/* network_3: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eb064 @ 0x020eb064, 0xc bytes, ARM
 * func_020eb058 @ 0x020eb058, 0xc bytes, ARM
 * func_020eb04c @ 0x020eb04c, 0xc bytes, ARM
 * func_020eb040 @ 0x020eb040, 0xc bytes, ARM
 */

extern int func_021012c4(void *data);
extern int func_0210101c(const void *a, const void *b);
extern int DWC_GetFriendDataType(void *friendData);
extern int DWC_IsBuddyFriendData(int data);

int func_020eb064(void *data)
{
    return func_021012c4(data);
}

int func_020eb058(const void *a, const void *b)
{
    return func_0210101c(a, b);
}

int func_020eb04c(void *friendData)
{
    return DWC_GetFriendDataType(friendData);
}

int func_020eb040(int data)
{
    return DWC_IsBuddyFriendData(data);
}
