int solution(int A[], int N) {
    unsigned long long int consecutiveSum = ((N + 1) * (N + 2)) / 2;
    unsigned long long int arrSum = 0;

    for (int i = 0; i < N; i++){
        arrSum += A[i];
    }

    return (int) consecutiveSum - arrSum;
}