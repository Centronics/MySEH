static void Per(int)
{
	return;
}
static void Per(void*)
{
	return;
}
static void Per(double)
{
	return;
}
static void Per(float)
{
	return;
}
static int Per(char)
{
	return 0;
}
static int Per(wchar_t)
{
	return 0;
}
static char Per()
{
	return 1;
}

static char Per(int, int)
{
	return 2;
}

void OverloadStart()
{
	char t = Per();
	t = Per(1, 1);
	int i = Per((char)1);
	i = Per((wchar_t)1);
	Per(0);
	Per(nullptr);
	Per(0.0f);
	Per(0.0);
}