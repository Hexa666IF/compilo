int pow(int a, int n)
{
	if(n > 1)
	{
		pow(a, n - 1);
	}
}

int main()
{
	return pow(2, 3);
}
