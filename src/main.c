/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 12:29:33 by jisokang          #+#    #+#             */
/*   Updated: 2021/10/30 15:59:57 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -lreadline *.c */

# include "../include/minishell.h"

#define		SPACE	1

int	old_parse(char *script)
{
	t_lst	*head;
	char	**str;
	int		i;
	int		j;

	str = ft_split(script, ' ');
	/* SPACE를 추가 하기 어려움
	-> linked list로 구현 예정 */
	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			// if (ft_strchr(DO_QUOTE, str[i][j]) != NULL)
			if (str[i][j] == '\"')
			{
				printf("DOUBLE IN %d\n", j);
				j++;
				while (str[i][j] != '\0' && str[i][j] != '\"')
				{
					printf("%d - %c\n", j, str[i][j]);
					if (str[i][j] == ' ')
					{
						str[i][j] = SPACE;
						printf("SPACE CHANGE\n");
					}
					j++;
				}
			}
			else
				j++;
		}
		i++;
	}
	j = 0;
	head = NULL;
	while (j < i)
	{
		printf("[%d]-[%s]\n", j, str[j]);
		lst_add_back(&head, lst_new(str[j]));
		j++;
	}
	printf("value : %s\n", script);
	print_lst_nul(head);
	printf("insert_TEST\n");

	return (EXIT_SUCCESS);
}

/**
 * @example $prompt : 'hello "hola world" world' -> one set. not two.
 */
int	convert_quote(char *script)
{
	char	in_quote;

	printf(BLUE"START CONVERT\n"RESET);
	while (*script != '\0')
	{
		script++;
		if (*script == '\"' || *script == '\'')
		{
			in_quote = *script;
			printf("in_quote : [%c]\n", in_quote);
			script++;
			while (*script != '\0' && *script != in_quote)
			{
				printf("CHANGE\n");
				*script = *script * -1;
				script++;
			}
			if (*script == '\0')
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);

}

int	tokenizer(char *script, char ***strs)
{
	int	i;
	if (convert_quote(script) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//convert_symbols()
	*strs = ft_split(script, ' ');
	i = 0;
	while ((*strs)[i])
	{
		/* revert_quote() */
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

	tokenizer(script, &strs);
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
		str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
		if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{
			printf("input : %s\n", str);/* 주소안에 문자열을 출력해보자 */
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
