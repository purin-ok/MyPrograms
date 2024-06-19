void dance()
{
	int i;

	for (i = 0; i < 3; i++) {
			srand((unsigned)time(NULL));
			rotAng[i] += rand() % 18;
	}
}
