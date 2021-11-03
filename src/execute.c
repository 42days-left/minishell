/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisokang <jisokang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:11:09 by jisokang          #+#    #+#             */
/*   Updated: 2021/11/03 15:22:50 by jisokang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * t_cmd에 뭐가 들어가야 할까...?
 *
 */

/* t_proce */
//typedef struct	s_proce
//{
//	int		argc;
//	char	**argv;
//	t_env	*env;
//	int		fd_in;
//	int		fd_out;
//}			t_proce;

//int	excute_built_in_proce(t_proce *pc)
//{
//	/* error 코드를 담는 글로벌 변수 */
//	g_exit_code = builtin[type](pc->argc, pc->argv, pc->env, pc->fd_out);
//	/* builtin 배열 -> if - else if 구조로 변경 */
//}


//int	excute_single_cmd(void)
//{
//	if (/* condition */)
//	{
//		//exteranl cmds process
//	}
//	else
//	{
//		//built_in cmds process
//		excute_built_in_proce();
//	}
//}

///**
// * 입력받은 명령어를 실행하는 함수
// */
//int	execute(t_cmd cmd, t_env env)
//{
//	int	count;

//	/* count = count cmd list */
//	if (/* 1 cmd */)
//	{
//		excute_single_cmd();
//	}
//	if else ( /* 2 more cmd */)
//	{

//	}

//}
