/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/01 14:03:40 by yubae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE	1

/**
 * @example $prompt : 'hello "hola world" world' -> one set. not two.
 */
int	convert_quote(char *script)
{
	char	in_quote;

	while (*script != '\0')
	{
		if (*script == '\"' || *script == '\'')
		{
			in_quote = *script;
			script++;
			while (*script != '\0' && *script != in_quote)
			{
				*script = *script * -1;
				script++;
			}
			if (*script == '\0')
				return (EXIT_FAILURE);
		}
		script++;
	}
	return (EXIT_SUCCESS);
}

int	reconvert_quote(char *str)
{
	if (*str == '\"' || *str == '\'')
	{
		str++;
		while (*str != '\0' && *str < 0)
		{
			*str = *str * -1;
			str++;
		}
	}
	return (0);
}

/**
 * @example 'echo|sleep 3' -> 'echo | sleep 3'
 */
int	convert_symbols(char *script)
{

	while (*script != '\0')
	{
		if (ft_strchr("|<>", *script))
		{
			printf("SYMBOLS!\n");
			/* 1. Add space Here*/
			/* Buffer? */
			/* 2. n-split -> join */
		}
		script++;
	}
	return (EXIT_SUCCESS);
}

int	split_symbols(char *str)
{
	int	i;

	while (*str != '\0')
	{
		if (ft_strchr("|<>", *str))
		{
			printf("");
		}

		str++;
	}
	str = ft_split();

	if (*str == '\"' || *str == '\'')
	{
		str++;
		while (*str != '\0' && *str < 0)
		{
			*str = *str * -1;
			str++;
		}
	}
}

int	tokenizer(char *script, char ***strs)
{
	int	i;

	if (convert_quote(script) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	convert_symbols(script);
	count_symbols(script);
	//스크립트 심볼에 ' '을 삽입하기 위해 버퍼가 필요한 시점
	*strs = ft_split(script, ' ');
	i = 0;
	while ((*strs)[i])
	{
		reconvert_quote((*strs)[i]);
		printf("[%s]\n", (*strs)[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @param script string entered at the prompt
 */
int	parse(char *script)
{
	//t_lst	*tokens;
	char	**strs;	//token들을 저장할 2차원 배열

	if(!tokenizer(script, &strs))
		return (EXIT_FAILURE);
	//lexer(script, tokens);
	//relace_env();
	//parser();
	return (EXIT_SUCCESS);
}

int	main(void)
{

/* readline함수를 활용하여 간단한 프로그램 작성하기 */
/* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
	char *str;
/* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
	while(1)
	{
		/* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
		str = readline(MAGENTA"minihell"RESET": ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
		if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{
			printf("input\t: %s\n", str);/* 주소안에 문자열을 출력해보자 */
			parse(str);
		}
		else/* str = NULL 이라면 (EOF, cntl + D)*/
			break ;/* 반복문을 탈출해준다.*/
	/* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
		add_history(str);
	/* 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		free(str);
	}
	/* 함수종료 */
	return(0);
}
