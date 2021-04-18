class pc_dynamic {
    private static final int NUM_END = 200000;

    public static void main(String[] args) {
        int counter = 0;

        for (int idx = 0; idx < NUM_END; idx++) {
            if (isPrime(idx))
                counter++;
        }
        System.println("counter: " + counter);
    }

    private static boolean isPrime(int x) {
        if (x <= 1)
            return false;
        for (int idx = 2; idx < x; idx++) {
            if ((x % idx == 0) && (idx != x))
                return false;
        }
        return true;
    }
}
