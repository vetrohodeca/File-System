#include<string>
#include<vector>

inline std::vector<std::string> splitByChar(std::string input, char delimiter)
{
	static std::vector<std::string> result(50);
	static int counter = 0;

	for (static unsigned i = 0; i < input.size(); i++)
	{
		if (input[i] != delimiter)
		{
			result[counter].push_back(input[i]);
		}
		else
		{
			counter++;
		}
	}
	return result;
}

