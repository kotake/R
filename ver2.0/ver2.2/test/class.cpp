#include <iostream>

using namespace std;

class A {
	private:
		int a;
	public:
		void set_a(int aa) { a=aa; }
		int get_a() { return a; }
};

class B {
	private:
		int b;
	public:
		void set_b(int bb) { b=bb; }
		void print_b() {cout << "b=" << b << endl; }
};

int main(void) {
	A ca;
	B cb;

	cb.set_b(100);
	cb.print_b();
	ca.set_a(10);
	cb.set_b(ca.get_a());
	cb.print_b();
	return 0;
}
