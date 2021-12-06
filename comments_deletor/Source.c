#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	//printf(" This is // not comment ");
	char temp_file_name[35], temp_str[1024];
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
	short int flag_slash, flag_mlt_cmnt, flag_ct_ln_cmnt, flag_ln_cmnt,	flag_quotes, EOF_flag, flag_spec_symb_out;
	
	for (int i = 0; i < number_of_f; i++)
	{
		fgets(temp_file_name, 35, files_names);
		//finding the index of name's ending
		z = 0;
		do
		{
			z++;
		} while (temp_file_name[z] != '\n' && temp_file_name[z] != '\0');
		temp_file_name[z] = '\0';
		z--;

		
		file_with_comments = fopen(temp_file_name, "r");
		
		//fot testing
		//temp_file_name[0] = 'Z';
		
		//working part
		//naming of the new file
		temp_file_name[z] = 'w';
		temp_file_name[z + 1] = 'c';
		temp_file_name[z + 2] = '\0';
		
		// flag for different cases
		EOF_flag = 0;
		flag_slash = 0;
		flag_mlt_cmnt= 0;
		flag_ct_ln_cmnt = 0;
		flag_ln_cmnt = 0;
		flag_quotes = 0;
		flag_spec_symb_out = 0;
		new_file = fopen(temp_file_name, "w");
		
		char temp_c = '1';
		int k;
		short int flag_EOF = 0, flag_nll;
		while (temp_c != EOF)
		{
			//getting string out of the file
			k = 0;
			flag_nll = 0;
			while (!flag_nll)
			{
				if ((temp_c = getc(file_with_comments)) != EOF)
				{
					if (temp_c == '\0' || temp_c == '\n')
						flag_nll = 1;
					temp_str[k] = temp_c;
					k++;
				}
				else
					flag_nll = 1;
			}
			
			
			for (int t = 0; t < k; t++)
			{
				if (temp_str[t] == '\"')
				{
					if (t > 0 && temp_str[t - 1] == '\\')
						flag_spec_symb_out = 1;
					if (flag_slash == 0 && flag_mlt_cmnt == 0 && flag_spec_symb_out == 0)
						flag_quotes = (flag_quotes + 1) % 2;				

					flag_spec_symb_out = 0;
				}
				else if (flag_quotes == 0 && t + 1 < k && temp_str[t] == '/' && temp_str[t + 1] == '/')
				{			
					flag_slash = 1;
					while(t < k && temp_str[t] == '/')
						t += 1;	
				}
				else if (flag_quotes == 0 && t + 1 < k)
				{
					if (temp_str[t] == '/' && temp_str[t + 1] == '*')
					{
						flag_mlt_cmnt = 1;

					}
					else if (temp_str[t] == '*' && temp_str[t + 1] == '/')
					{
						flag_mlt_cmnt = 0;
						t += 2;
					}	
				}
				//checking for line cutting letter
				if (flag_slash == 1 && temp_str[t] == '\\' && temp_str[t + 1]== '\n')
					flag_ct_ln_cmnt = 1;

				//writing a letter to the new file
				if (t < k)
				{
					if (!flag_slash && !flag_mlt_cmnt || temp_str[t] == '\n')
						putc(temp_str[t], new_file);
				}
				else
				{
					//for the case of "*/" at the end of file
					putc('\n', new_file);
				}
				
			}
			if (flag_quotes == 0 && flag_ct_ln_cmnt == 1 && flag_slash == 1)
				flag_ct_ln_cmnt = 0;
			else
				flag_slash = 0;
		}
		

		fclose(file_with_comments);
		fclose(new_file);
	}
	
	fclose(files_names);
	
	//printf("%c", c);
}