bitset<MAX_N> isprime;
void eratosthenes_sieve()
{
	isprime.set();
	isprime[0] = isprime[1] = 0;
	for (int i = 4; i < MAX_N; i += 2)
		isprime[i] = 0;
	for (int i = 3; i * i < MAX_N; i += 2)
		if (isprime[i])
			for (int j = i * i; j < MAX_N; j += i * 2)
				isprime[j] = 0;
}