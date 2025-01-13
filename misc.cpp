void swap(char& ch1, char& ch2)
{
	ch1 = ch1 ^ ch2;
	ch2 = ch1 ^ ch2;
	ch1 = ch1 ^ ch2;
}

unsigned getDigitsCount(unsigned n)
{
	if (n == 0)
		return 1;

	unsigned count = 0;
	while (n != 0)
	{
		count++;
		n /= 10;
	}

	return count;
}