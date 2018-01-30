#include "../libft.h"

char	*concat_strs(char *str, ...)
{
	va_list	ap;
	char	*res;

	res = NULL;
	if (str)
	{
		va_start(ap, str);
		if (!(res = ft_strnew(ft_strlen(str))))
			return (NULL);
		ft_strcpy(res, str);
		while ((str = va_arg(ap, char *)))
		{
			res = ft_realloc(res, ft_strlen(str));
			ft_strcat(res, str);
		}

		va_end(ap);
	}
	return (res);
}
