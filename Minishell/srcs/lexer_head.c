/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_head.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:06:00 by aoumad            #+#    #+#             */
/*   Updated: 2022/05/23 11:00:39 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int search_token(char token)
{
    if (token ==  ' ')
        return white_space;
    else if (token == '\n')
        return new_lin;
    else if (token == '\t')
        return (tab);
    else if ( token == '|')
        return (pipe);
    else if (token == '&')
        return (token);
    else if (token == '>')
        return (redirect_out);
    else if (token ==  '<')
        return (redirect_in);
    else if (token == '$')
        return (dollar);
    else if (token == '\'')
        return (single_quo);
    else if (token == '\"')
        return (double_quo);
    else if (token == '\0')
        return (char_null);
    else
        return (-1);
}

int ft_leaxer(char *line)
{
    int type;
    int i;
    int j;
    int len;
    int start;

    len = 0;
    start = 0;  
    while (line[i])
    {
        j = 0;
        type = search_token(line[i]);
        type = handle__input(line, &i, len, type) // return type of token
        if ()
    }
}

/*int ft_leaxer(char *line)
{
    int type;
    int i;
    int j;
    int len;
    int start;

    start = 0;  
    while (line[i])
    {
        j = 0;
        type = words_numbers;
        if (search_token(line[i]) == -1)
        {
            if (start != 0)
                start = (char *)&line[i];
            while (search_token(line[i++] == -1))
                j++;
            len = j;
            ft_fill(start, len, type);
        }
        else
        {
            start = 0;
            type = search_token(line[i]);
            
        }
    }
}*/

int handle_input(char *line, int *i, int len, int saved_type)
{
    int start;
    
    start = (*i);
    while (line[*i])
    {
        if (saved_type == search_token(line[*i]))
        {
            len++;
            i++;
        }
    }
    
}

void    ft_fill(char *line, int *i, int len, int saved_type)
{
    t_node  *token_head;
    t_node  *token_new;
    t_node  *token_elm;
    
    token_head = (t_node *)malloc(sizeof(t_node));
    while (line[*i])
    {
        if (saved_type == search_token(line[*i]))
            len++;
            i++;
    }
    token_head->data.start = line[*i];
    token_head->data.len = len;
    token_head->data.type = saved_type;
    
}

/*
    while (line[i])
    {
        if (search_token(line[i]) == -1)
            i++;
        else
        {
            end = i - 1;
            ft_fill(line, start, end);
            start = i + 1;   
        }
    }  
*/