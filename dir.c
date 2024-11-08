/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:41:38 by aquissan          #+#    #+#             */
/*   Updated: 2024/11/07 12:41:41 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void listar_conteudo(const char *path) {
    struct dirent *entry;
    struct stat info;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("Erro ao abrir o diretório");
        return;
    }

    printf("Conteúdo de %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        // Ignora "." e ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Constrói o caminho completo do item
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Usa stat para verificar se é arquivo ou diretório
        if (stat(full_path, &info) == 0) {
            if (S_ISDIR(info.st_mode)) {
                printf("Diretório: %s\n", full_path);
                // Chama a função recursivamente para listar subdiretórios
                listar_conteudo(full_path);
            } else if (S_ISREG(info.st_mode)) {
                printf("Arquivo: %s\n", full_path);
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *path = ".";  // Pode substituir pelo caminho que deseja listar
    listar_conteudo(path);
    return 0;
}

