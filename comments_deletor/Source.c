#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char temp_file_name[35];
	FILE *files_names;

	files_names = fopen("project.txt", "r");
	fgets(temp_file_name, 35, files_names);

	int len_numb_files = 0, number_of_f = 0;

	while (temp_file_name[len_numb_files] != '\0' && temp_file_name[len_numb_files] != '\n')
		len_numb_files++;
	len_numb_files--;

	for (int i = 0; i <= len_numb_files; i++)
		number_of_f = number_of_f * 10 + ((int)temp_file_name[i] - (int)'0');

	FILE *file_with_comments, *new_file;
	int z;

	for (int i = 0; i < number_of_f; i++)
	{
		fgets(temp_file_name, 35, files_names);
		//finding the index of name's ending
		z = 0;
		do
		{
			z++;
		} while (temp_file_name[z] != '.');
		temp_file_name[z + 2] = '\0';
		z++;

		file_with_comments = fopen(temp_file_name, "r");

		//fot testing
		//temp_file_name[0] = 'Z';

		//working part
		//naming of the new file
		temp_file_name[z] = 'w';
		temp_file_name[z + 1] = 'c';
		temp_file_name[z + 2] = '\0';

		new_file = fopen(temp_file_name, "w");

		char prev, last;
		last = getc(file_with_comments);

		while (!feof(file_with_comments))
		{
			prev = last;
			last = getc(file_with_comments);
			if (prev == '\"')
			{
				fputc(prev, new_file);
				do
				{
					if (last == '\\')
					{
						fputc(last, new_file);
						last = getc(file_with_comments);
						fputc(last, new_file);
						last = getc(file_with_comments);
					}
					prev = last;
					last = getc(file_with_comments);
					fputc(prev, new_file);

				} while (prev != '\"');
			}
			else if (prev == '\'')
			{
				fputc(prev, new_file);
				do
				{
					if (last == '\\')
					{
						fputc(last, new_file);
						last = getc(file_with_comments);
						fputc(last, new_file);
						last = getc(file_with_comments);
					}
					prev = last;
					last = getc(file_with_comments);
					fputc(prev, new_file);

				} while (prev != '\'');
			}
			else if (prev == '/')
			{
				if (last == '/')
				{
					while (prev != '\n' && !feof(file_with_comments))
					{
						prev = last;
						last = getc(file_with_comments);
						if (last == '\n')
						{
							
							if (prev == '\\')
							{
								prev = getc(file_with_comments);
								last = getc(file_with_comments);
							}
							fputc('\n', new_file);
						}
					}
				}
				else if (last == '*')
				{
					prev = getc(file_with_comments);
					last = getc(file_with_comments);

					while (!(prev == '*' && last == '/') && !feof(file_with_comments))
					{
						prev = last;
						last = getc(file_with_comments);
					}
					last = getc(file_with_comments);
				}
			}
			else
				fputc(prev, new_file);
		}
		fclose(file_with_comments);
		fclose(new_file);
	}
	fclose(files_names);
}
