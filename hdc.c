if (command_tree->heredoc)
    {
        int heredoc_fd[2];
        if (pipe(heredoc_fd) == -1)
            return (perror("Pipe error"), close(old_fd_in), close(old_fd_out), -1);
        pid = fork();
        if (pid == -1)
            return (perror("Fork error"), close(heredoc_fd[0])
                , close(heredoc_fd[1]), close(old_fd_out), close(old_fd_in), -1);
        if (pid == 0) {
            close(heredoc_fd[0]);
            char *str;
            while (1)
            {
                str = readline("> ");
                if (str == NULL)
                    return (-1);
                if (strcmp(str, command_tree->heredoc_end) == 0) {
                    free(str);
                    break;
                }
                //printf("%s\n", str);
                write(heredoc_fd[1], str, ft_strlen(str));
                write(heredoc_fd[1], "\n", 1);
                free(str);
            }
            close(heredoc_fd[1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(heredoc_fd[1]);
            if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
                return (perror("Dup2 error"), close(heredoc_fd[0])
                    , close(old_fd_out), close(old_fd_in), -1);
            close(heredoc_fd[0]);
            waitpid(pid, &status, 0);
        }
    }
