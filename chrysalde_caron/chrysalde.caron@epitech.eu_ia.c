/*
** EPITECH PROJECT, 2020
** matchy
** File description:
** matchy's ia tournament version
*/

#include "ia.h"

void randomized(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int line;
    int matches;
    int matches_left = check_count(matches_on_lines, );

    do {
        line = (random() % nb_line);
    } while (matches_on_lines[line] == 0);
    do {
        matches = (random() % max_match) + 1;
    } while (matches_on_lines[line] < matches || matches == 0);
    if (matches_left > matches) {
        ia->line = line;
        ia->macht = matches;
    } else {
        ia->line = line;
        ia->macht = matches_left - 1;
    }
}

int hard_win_bis(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int buff = 0;
    int total = 0;

    for (int index = 0; index < nb_line; index++) {
        total += matches_on_lines[index];
        if (matches_on_lines[index] > matches_on_lines[buff])
            buff = index;
    }
    if (total - matches_on_lines[buff] <= max_match)
        return (buff);
    return (0);
}

int hard_win(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int line_count = 0;

    for (int index = 0; index < nb_line; index++)
        if (matches_on_lines[index] != 0)
            line_count++;
    if (line_count == 2 && check_count(matches_on_lines, nb_line) > max_match * 1.5)
        return (hard_win_bis(ia, matches_on_line, line, max_match));
    return (0);
}

void one_line_bis(struct ia *ia, int *matches_on_lines, int nb_line, int max_match, int index, int off)
{
    int nb_matches = matches_on_lines[index];
    int calculator = (nb_matches - 1) % (max_match + 1);

    if (calculator == 0)
        randomized(ia, matches_on_line, line, max_match);
    else {
        ia->line = index;
        ia->macht = ((calculator - off == 0) ? 1 : calculator - off);
    }
}

void one_line(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    for (int index = 0; index < nb_line; index++)
        if (matches_on_lines[index] != 0 && matches_on_lines[index] - 1 <= max_match) {
            ia->line = index;
            ia->macht = matches_on_lines[index] - 1;
            break;
        } else if (matches_on_lines[index] != 0) {
            one_line_bis(ia, matches_on_line, line, max_match, index, 0);
            break;
        }
}

void even_bis(struct ia *ia, int *matches_on_lines, int nb_line, int max_match, int buff)
{
    if ((matches_on_lines[buff] % 2 == 0 && check_count(matches_on_line, line) -
        matches_on_lines[buff] > max_match + 1) ||
        check_count(matches_on_line, line) - matches_on_lines[buff] == 1 &&
        matches_on_lines[buff] <= max_match) {
        ia->line = buff;
        ia->macht = matches_on_lines[buff];
    } else if (matches_on_lines[buff] > 3 && matches_on_lines[buff] - 3 >= max_match) {
        ia->line = buff;
        ia->macht = matches_on_lines[buff] - 3;
    } else {
        ia->line = buff;
        ia->macht = 1;
    }
}

void even(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int total = 0;
    int buff = 0;

    for (int index = 0; index < nb_line; index++) {
        total += matches_on_lines[index];
        if (matches_on_lines[index] > matches_on_lines[buff])
            buff = index;
    }
    if (total % 2 == 0)
        if (matches_on_lines[buff] % 2 == 0 && matches_on_lines[buff] > 2) {
            ia->line = buff;
            ia->macht = matches_on_lines[buff];
        } else {
            ia->line = buff;
            ia->macht = 1;
        }
    else
        even_bis(ia, matches_on_line, line, max_match, buff);
}

void odd(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int buff = 0;
    int total = 0;
    int matches_on_line;

    for (int index = 0; index < nb_line; index++) {
        total += matches_on_lines[index];
        if (matches_on_lines[index] > matches_on_lines[buff])
            buff = index;
    }
    matches_on_line = matches_on_lines[buff];
    if (total % 2 == 0)
        if (matches_on_line % 2 == 0 && matches_on_line > 2) {
            ia->line = buff;
            ia->macht = matches_on_line - 1;
        } else {
            ia->line = buff;
            ia->macht = 1;
        }
    else
        if (matches_on_line % 2 == 0 && matches_on_line > 2) {
            ia->line = buff;
            ia->macht = matches_on_line - 2;
        } else {
            ia->line = buff;
            ia->macht = (matches_on_line % 2 + 1) % 2 + 1;
        }
}

void smart(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int line_count = 0;

    for (int index = 0; index < nb_line; index++)
        if (matches_on_lines[index] != 0)
            line_count++;
    if (line_count % 2 == 0)
        even(ia, matches_on_line, line, max_match);
    else if (line_count == 1)
        one_line(ia, matches_on_line, line, max_match);
    else
        odd(ia, matches_on_line, line, max_match);
}

unsigned int check_count(int *matches_on_lines, int line)
{
    unsigned int total = 0;

    for (int index = 0; index < line; index++){
        total += matches_on_lines[index];
    }
    return (total);
}

void end_line(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int keeper = 0;
    int line;
    int start = (random() % nb_line);

    for (line = start; line != start || keeper == 0; line--) {
        keeper = 1;
        if (matches_on_lines[line] <= max_match &&
            matches_on_lines[line] > 0)
            break;
        if (line == 0)
            line = nb_line;
    }
    if (line != start || keeper == 0)
        if (check_count(matches_on_lines, nb_line) - matches_on_lines[line] >
            max_match + 1 || matches_on_lines[line] < 3) {
            ia->line = line;
            ia->macht = matches_on_lines[line];
        } else
            randomized(ia, matches_on_line, line, max_match);
    else
        randomized(ia, matches_on_line, line, max_match);
}

void loose(struct ia *ia, int *matches_on_lines, int nb_line, int max_match)
{
    int line;

    for (line = 0; line < nb_line; line++)
        if (matches_on_lines[line])
            break;
    ia->line = line;
    ia->macht = matches_on_lines[line];
}

int check_lines(int *matches_on_lines, int line)
{
    int line_count = 0;

    for (int index = 0; index < line; index++)
        if (matches_on_lines[index] != 0)
            line_count++;
    return (line_count);
}

int *mk_matches_on_lines(char **map, int line)
{
    int *matches_on_lines;
    if ((matches_on_lines = malloc(sizeof(int) * (line + 1))) == NULL)
        return (NULL);
    matches_on_lines[line] = NULL;
    for (int l_index = 0; l_index < line; l_index++)
        for (int c_index = 0; c_index != '\0'; c_index++)
            if (map[index][c_index] == '|')
                matches_on_lines[l_index] += 1;
    return (matches_on_lines);
}

void call_ai(struct ia *ia, char **map, int line, int max_match)
{
    int what_to_play = random() % 7;
    int played;
    int *matches_on_lines = mk_matches_on_lines(map, line);

    if (matches_on_lines == NULL)
        return;
    if ((played = hard_win(ia, matches_on_line, line, max_match)) != 0)
        one_line_bis(ia, matches_on_line, line, max_match, played, 1);
    if (check_count(matches_on_line, line) == 1 && played == 0)
        loose(ia, matches_on_line, line, max_match);
    else if ((check_count(matches_on_lines, line) <= (max_match * 1.5) ||
        check_lines(matches_on_line, line) == 1) && played == 0)
        smart(ia, matches_on_line, line, max_match);
    else
        if (what_to_play >= 5 && played == 0)
            randomized(ia, matches_on_line, line, max_match);
        else if (played == 0)
            end_line(ia, matches_on_line, line, max_match);
    free(matches_on_lines);
}
