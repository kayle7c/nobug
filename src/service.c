char *my_strncpy(char *dst,const char*src,int n)
{
		if (n != 0)
    {
        char *d = dst;
        const char *s = src;
        do
        {
            if ((*d++ = *s++) == 0)
            {
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }

    return (dst);
}

int my_strlen(char* src)
{
		int len=0;
		while(*src++ != '\0')
		{
				len++;
		}
		return len;
}

//如果src1被包含于src2返回1，否则返回0
int my_strcmp(char *src1,char *src2)
{
		while(*src1 == *src2)
		{
				src1++;
				src2++;
				if(*src1=='\0')
				{
						return 1;
				}
		}
		return 0;
}

void *my_memmove(void *dest, const void *src, int n)
{
    char *tmp = (char *)dest, *s = (char *)src;

    if (s < tmp && tmp < s + n)
    {
        tmp += n;
        s += n;

        while (n--)
            *(--tmp) = *(--s);
    }
    else
    {
        while (n--)
            *tmp++ = *s++;
    }

    return dest;
}
