/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrasolof <hrasolof@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:43:17 by hrasolof          #+#    #+#             */
/*   Updated: 2024/09/28 14:28:32 by hrasolof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// C program to illustrate 
// pipe system call in C 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MSGSIZE 16 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 

int main() 
{ 
    char inbuf[MSGSIZE]; 
    int p[2], pid, nbytes; 
  
    if (pipe(p) < 0) 
        exit(1); 
  
    /* continued */
    if ((pid = fork()) > 0) { 
        write(p[1], msg1, MSGSIZE); 
        write(p[1], msg2, MSGSIZE); 
        write(p[1], msg3, MSGSIZE); 
  
        // Adding this line will 
        // not hang the program 
        // close(p[1]); 
        wait(NULL); 
    } 
  
    else { 
        // Adding this line will 
        // not hang the program 
        // close(p[1]); 
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) 
            printf("%s\n", inbuf); 
        if (nbytes != 0) 
            exit(2); 
        printf("Finished reading\n"); 
    } 
    return 0; 
}





