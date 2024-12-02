/*Purpose of this code is in order to integrate pipe handling, we need to adjust how we split the string,
treating the pipe (|) symbol as a delimiter between commands, while still 
respecting quotes and handling special characters properly. In short, this is an update for the
token split function to take account delimeter. Will test it later*/

static size_t word_count(const char *str)
{
    size_t i = 0;
    size_t w_count = 0;

    while (str[i]) {
        // Skip spaces and special characters
        while (str[i] && ft_isspace(str[i])) {
            i++;
        }

        if (str[i] && str[i] != '|') { // If not a pipe
            w_count++;
            while (str[i] && str[i] != '|' && !ft_isspace(str[i]) && !ft_special_char(str[i])) {
                i++;
            }
        } else if (str[i] == '|') { // If it's a pipe
            w_count++;
            i++;
        }

        // Skip over pipes and special characters
        while (str[i] && (ft_special_char(str[i]) || str[i] == '|')) {
            i++;
        }
    }

    return w_count;
}

int extract_word(t_datatok *data, const char *str)
{
    size_t len;
    int in_quotes = 0;

    // Handle quotes if present
    if (str[data->index] == '"')
        in_quotes = 1;
    else if (str[data->index] == '\'')
        in_quotes = 2;

    if (in_quotes) {
        data->index++;
    }

    data->index2 = data->index;
    
    // Extract the word
    while (str[data->index] && ((in_quotes &&
            ((in_quotes == 1 && str[data->index] != '"') || 
            (in_quotes == 2 && str[data->index] != '\''))) ||
            (!in_quotes && str[data->index] != '|' && !ft_isspace(str[data->index]) && !ft_special_char(str[data->index])))) {
        data->index++;
    }

    len = data->index - data->index2;
    data->out[data->tab_i] = malloc(sizeof(char) * (len + 1));
    if (!data->out[data->tab_i]) {
        free_tab_struct(data);
        return 0;
    }

    ft_strncpy(data->out[data->tab_i], &str[data->index2], len);
    data->out[data->tab_i++][len] = '\0';

    // Handle closing quotes
    if (in_quotes && (str[data->index] == '"' || str[data->index] == '\'')) {
        data->index++;
    }

    return 1;
}

char **ft_toksplit(const char *str)
{
    t_datatok data;
    int i = 0;

    if (!str)
        return NULL;

    ft_assigne(&data, str);
    
    while (str[data.index]) {
        // Skip spaces and special characters (including pipes)
        while (str[data.index] && (ft_isspace(str[data.index]) || ft_special_char(str[data.index]) || str[data.index] == '|'))
            data.index++;

        if (str[data.index] && !ft_isspace(str[data.index]) && !ft_special_char(str[data.index]) && str[data.index] != '|') {
            if (!extract_word(&data, str))
                return NULL;
        }
    }
    data.out[data.tab_i] = NULL;
    return data.out;
}
