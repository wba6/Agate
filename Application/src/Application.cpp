

namespace Agate {
	__declspec(dllimport) void helloWorld();
}

int main() {
	
	Agate::helloWorld();

	while (1);
	return 0;
}