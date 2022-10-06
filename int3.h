typedef struct {
  int n1;
  int n2;
  int n3;
} Int3;

Int3 int_to_int3(int n) {
  Int3 c;
  c.n1 = n / 100;
  c.n2 = n / 10 % 10;
  c.n3 = n % 100 % 10;
  return c;
}

int int3_to_int(Int3 n) { return n.n1 * 100 + n.n2 * 10 + n.n3; }
